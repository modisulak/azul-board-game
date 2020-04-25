#include "Factory.h"

Factory::Factory() { 
     for(int i=0; i < MAX_FACTORY_TILES; i++) { 
       this->tiles[i] = NULL; 
     }
}

Factory::Factory(const Factory &other) { 
    for(int i=0; i < MAX_FACTORY_TILES; i++) { 
     tiles[i] = other.tiles[i];
    }
}

Factory::~Factory()  {
      for(int i=0; i < MAX_FACTORY_TILES; i++) {
            this->tiles[i] = NULL; 
      }
}

Tile Factory::getTile(int index) { 
      return tiles[index];
}

int Factory::getTilesOfSameColour(Tile tile) { 
      int noOfTiles = 0;
      for (int i=0; i < MAX_FACTORY_TILES ; i++) { 
            if (tiles[i] == tile) { 
                  noOfTiles++;
            }
      }
      return noOfTiles; 
}

void Factory::addTile(Tile tile) {
      for (int i=0; i < MAX_FACTORY_TILES ; i++) {
            if (tiles[i] == NULL) {
                  tiles[i] = tile;
            }
      }
      
}