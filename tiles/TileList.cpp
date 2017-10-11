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
    if(nrOfElements +1 < sizeOfArray){
        tiles[nrOfElements] = tile;
    }else{
        int newSize = sizeOfArray + TILE_SIZE_MULT;
        Tile tmpTiles[newSize];

        for(auto i=0; i < nrOfElements; i++){
            tmpTiles[i] = tiles[i];
        }
        tmpTiles[nrOfElements + 1] = tile;
        //kommer den verkligen ta bort tiles då pekarbyten på raden under? (tmpTIles försvinner ty stacken men de gamla elementen som ligger på tiles)
        this->tiles = tmpTiles;
        sizeOfArray = newSize;
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
    for(int i=nrOfElements-1; i>0; i--){
        if((tiles->x < x < x+ tiles->width) & (tiles->y < y < y + tiles->height)){
            for (int j=i; i<nrOfElements; j++){
                tiles[j] = tiles[j+1];
            }
        }
    }
}

void TileList::removeAll(int x, int y)
{
    // TODO: write this member
}
