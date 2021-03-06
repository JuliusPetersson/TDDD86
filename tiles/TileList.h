#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

class TileList {
public:
    /**
     * @brief Init an empty list with the size of 10
     */
    TileList();

    /**
     * TileList
     * @brief Destructor
     */
    ~TileList();

    /**
     * Adds a tile to the end of the list , complexity Ordo(1)
     * @brief Adds a tile to the listTileList
     */
    void addTile(Tile tile);

    /**
     * Draws all Tiles in TileList in order first to last in list, comlexity Ordo(n)
     * @brief draws all tiles
     * @param scene pointer to draw object
     */
    void drawAll(QGraphicsScene* scene) const;

    /**
     * @brief return the highest object at coord x and y. Complexity Ordo(n)
     * @return tiles or -1
     */
    int indexOfTopTile(int x, int y) const;

    /**
     * @brief lower puts the tile clicked to the start.If no object at coordinates, do nothing. Complexity worst case Ordo(n)
     * @param x coordinate
     * @param y coordinate
     */
    void lower(int x, int y);

    /**
     * @brief raise puts the tile clicked to the end. If no object at coordinates, do nothing .Comlexity worst case Ordo(n)
     * @param x coordinate
     * @param y coordinate
     */
    void raise(int x, int y);

    /**
     *  @brief remove element clicked at the highest position. If no object at coordinates, do nothing. Complexity worst case Ordo(n)
     * @param x coordinate
     * @param y coordinate
     */
    void remove(int x, int y);

    /**
     * @brief remove all obejcts being that covers those coordinates
     * @param x coordinate
     * @param y coordinate
     */
    void removeAll(int x, int y);

private:
    const int TILE_SIZE_MULT;
    int nrOfElements;
    int sizeOfArray;
    Tile* tiles;

};

#endif // TILELIST_H
