#include "level.h"
#include "graphics.h"
#include "globals.h"
#include "tinyxml2.h"

#include <SDL2/SDL.h>
#include <sstream> //for string stream
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace tinyxml2;

Level::Level(){}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics& graphics) :
    _mapName(mapName),
    _spawnPoint(spawnPoint),
    _size(Vector2(0,0))
{
    this->loadMap(mapName, graphics);
}

Level::~Level(){}

void Level::loadMap(std::string mapName, Graphics& graphics){
    //parse the .tmx file
    XMLDocument doc;
    std::stringstream ss;
    ss << "content/maps/" << mapName << ".tmx"; // Pass in Map 1, we get content/maps/Map 1.tmx
    doc.LoadFile(ss.str().c_str());

    XMLElement* mapNode = doc.FirstChildElement("map");

    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    this->_size = Vector2(width, height);

    //get the width and the height of the tiles and store them into the _tileSize
    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);
    this->_tileSize = Vector2(tileWidth, tileHeight);

    //loading the tilesets
    XMLElement* pTileset = mapNode->FirstChildElement("tileset");
    if (pTileset != NULL) {
        while (pTileset) {
             int firstgid;
             const char* source = pTileset->FirstChildElement("image")->Attribute("source");
             char* path;
             std::stringstream ss;
             ss << "content/tilesets/" << source;
             pTileset->QueryIntAttribute("firstgid", &firstgid);
             SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
             this->_tilesets.push_back(Tileset(tex, firstgid));

             pTileset = pTileset->NextSiblingElement("tileset");
        }
    }
     //loading the layers
     XMLElement* pLayer = mapNode->FirstChildElement("layer");
     if (pLayer != NULL){
         while (pLayer){
             //loading the data element
             XMLElement* pData = pLayer->FirstChildElement("data");
             if (pData != NULL){
                 while (pData){
                     //loading the tile element
                     XMLElement* pTile = pData->FirstChildElement("tile");
                     if (pTile != NULL) {
                         int tileCounter = 0;
                         while (pTile) {
                             //build each individual tile here
                             //if gid is 0, no tile should be drawn. Continue loop
                             if (pTile->IntAttribute("gid") == 0){
                                 tileCounter++;
                                 if (pTile->NextSiblingElement("tile")){
                                     pTile = pTile->NextSiblingElement("tile");
                                     continue;
                                 } else {
                                     break;
                                 }
                             }
                            //get the tileset for this specific gid
                             int gid = pTile->IntAttribute("gid");
                             Tileset tls;

                             for (int i = 0; i < this->_tilesets.size(); i++){
                                 if (this->_tilesets[i].FirstGid <= gid) {
                                     //This is the tileset we want
                                     tls = this->_tilesets.at(i);
                                     break;
                                 }
                             }
                             if (tls.FirstGid == -1){
                                 //no tileset is found for this gid... poor gid :(
                                 tileCounter++;
                                 if (pTile->NextSiblingElement("tile")){
                                     pTile = pTile->NextSiblingElement("tile");
                                     continue;
                                 } else
                                     break;
                             }
                            //Get the position of the tile in the level
                             int xx = 0;
                             int yy = 0;
                             xx = tileCounter % width;
                             xx *= tileWidth;
                             yy += tileHeight * (tileCounter / width);
                             Vector2 finalTilePosition = Vector2(xx, yy);

                            //Calculate the position of the tile in the tileset
                             int tilesetWidth, tilesetHeight;
                             SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);

                             int tsxx = gid % (tilesetWidth / tileWidth) - 1;
                             tsxx *= tileWidth;
                             int tsyy = 0;
                             int amt = (gid / (tilesetWidth / tileWidth));
                             tsyy = tileHeight * amt;
                             Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);

                             //Build the actual tile and add it to the level's  tile list
                             Tile tile(tls.Texture, Vector2(tileWidth, tileHeight),
                                           finalTilesetPosition, finalTilePosition);
                             this->_tileList.push_back(tile);
                             tileCounter++;

                             pTile = pTile->NextSiblingElement("tile");
                         }
                     }

                     pData = pData->NextSiblingElement("data");
                 }
             }
             pLayer = pLayer->NextSiblingElement("layer");
         }
     }

    //parse out the collision
    XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
    if (pObjectGroup != NULL) {
        while (pObjectGroup) {
            const char* name = pObjectGroup->Attribute("name");
            std::stringstream ss;
            ss << name;
            if (ss.str() == "collisions") {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        float x = std::stof(pObject->Attribute("x"));
                        float y = std::stof(pObject->Attribute("y"));
                        float width = std::stof(pObject->Attribute("width"));
                        float height = std::stof(pObject->Attribute("height"));

                        _collisionRects.push_back(Rectangle(
                            static_cast<int>(std::floor(x)),
                            static_cast<int>(std::floor(y)),
                            static_cast<int>(std::ceil(width)),
                            static_cast<int>(std::ceil(height))
                        ));

                        pObject = pObject->NextSiblingElement("object");

                    }
                }
            }
            //other object groups go here with an else if (ss.str() == "whatever")
            else if (ss.str() == "spawn points"){
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        float x = std::stof(pObject->Attribute("x"));
                        float y = std::stof(pObject->Attribute("y"));
                        const char* name = pObject->Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if (ss.str() == "player") {
                            this->_spawnPoint = Vector2(std::ceil(x),
                                                        std::ceil(y));
                        }
                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }

            pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
        }
    }
}

void Level::update(int elapsedTime){}

void Level::draw(Graphics& graphics){
    for (int i = 0; i < this->_tileList.size(); i++){
        this->_tileList.at(i).draw(graphics);
    }
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle &other) {
    std::vector<Rectangle> others;
    for (int i = 0; i < this->_collisionRects.size(); i++) {
        if (this->_collisionRects.at(i).collidesWith(other)) {
            others.push_back(this->_collisionRects.at(i));
        }
    }
    return others;
}
 Vector2 Level::getPlayerSpawnPoint() const {
    return this->_spawnPoint;
}
