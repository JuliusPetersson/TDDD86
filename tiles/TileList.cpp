// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header


#include "TileList.h"

TileList::TileList()
    : TILE_SIZE_MULT(2),nrOfElements(0),sizeOfArray(10)
{
   tiles = new Tile[sizeOfArray];
}

TileList::~TileList()
{
     delete[] tiles;
}

void TileList::addTile(Tile tile)
{
    if(nrOfElements +1 < sizeOfArray){
        this->tiles[nrOfElements] = tile;
    }else{
        int newSize = sizeOfArray * TILE_SIZE_MULT;
        Tile *tmpTiles = new Tile [newSize];

        for(int i=0; i < nrOfElements; i++){
            tmpTiles[i] = tiles[i];
        }
        tmpTiles[nrOfElements] = tile;
        delete [] tiles;
        tiles = tmpTiles;
        sizeOfArray = newSize;
    }

    nrOfElements++;
}

void TileList::drawAll(QGraphicsScene* scene)
{
    for (int i = 0; i < nrOfElements; i++){
        tiles[i].draw(scene);
    } 
}

int TileList::indexOfTopTile(int x, int y)
{
    for(int i=nrOfElements-1; i>=0; i--){
        if(tiles[i].contains(x,y)){
            return i;
        }
    }

    return -1;
}

void TileList::raise(int x, int y)
{
    for(int i=nrOfElements-1; i>=0; i--){
        if(tiles[i].contains(x,y)){
            Tile tmp = tiles[i];
            for (int j=i; j<nrOfElements-1; j++){
                tiles[j] = tiles[j+1];
            }
            tiles[nrOfElements-1] = tmp;
            break;
        }
    }
}

void TileList::lower(int x, int y)
{
    for(int i=nrOfElements-1; i>=0; i--){
        if(tiles[i].contains(x,y)){
            Tile tmp = tiles[i];
            for (int j=i; j > 0; j--){
                tiles[j] = tiles[j-1];
            }
            tiles[0] = tmp;
            break;
        }
    }
}

void TileList::remove(int x, int y)
{
    for(int i=nrOfElements-1; i>=0; i--){
        if(tiles[i].contains(x,y)){
            nrOfElements--;
            for (int j=i; j<nrOfElements; j++){
                tiles[j] = tiles[j+1];
            }
            break;
        }
    }
}

void TileList::removeAll(int x, int y)
{
    for(int i=nrOfElements-1; i>=0; i--){
        if(tiles[i].contains(x,y)){
            nrOfElements--;
            for (int j=i; j<nrOfElements; j++){
                tiles[j] = tiles[j+1];
            }
        }
    }
}
