// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header


#include "TileList.h"

TileList::TileList()
    : TILE_SIZE_MULT(10),nrOfElements(0),sizeOfArray(TILE_SIZE_MULT)
{
    // TODO: write this member
    tiles = new Tile[TILE_SIZE_MULT];
}

TileList::~TileList()
{
    // TODO: write this member
    delete[] tiles;
}

void TileList::addTile(Tile tile)
{
    // TODO: write this member
    if(nrOfElements<sizeOfArray){
        tiles[nrOfElements + 1] = tile;
    }else{
        int newSize = sizeOfArray + TILE_SIZE_MULT;
        Tile tmpTiles[newSize];

        for(auto i=0; i< sizeOfArray; i++){
            tmpTiles[i] = tiles[i];
        }
        tmpTiles[sizeOfArray + 1] = tile;
        this->tiles = tmpTiles;
    }

    nrOfElements++;
}

void TileList::drawAll(QGraphicsScene* scene)
{
    // TODO: write this member
    for (int i = 0; i < nrOfElements; i++){
        tiles[i].draw(scene);
    }

}

int TileList::indexOfTopTile(int x, int y)
{
    // TODO: write this member
}

void TileList::raise(int x, int y)
{
    // TODO: write this member
}

void TileList::lower(int x, int y)
{
    // TODO: write this member
}

void TileList::remove(int x, int y)
{
    // TODO: write this member
}

void TileList::removeAll(int x, int y)
{
    // TODO: write this member
}
