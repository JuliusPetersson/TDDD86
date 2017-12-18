/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef UNIT_H
#define UNIT_H

#include "utilities.h"
#include <QGraphicsScene>

/* Root class for all pieces on the board.
 * Subclasses are Robot, Hero and Junk.
 */
class Unit {
public:
    Unit() {teleport();}

    Unit(const Unit& u) {
        x = u.x;
        y = u.y;
    }

    Unit(const Point& p) {
        x = p.x;
        y = p.y;
    }

    virtual ~Unit() = 0;
    /*
    * Return Point representation of Unit
    */
    Point asPoint() const{
        return Point{x, y};
    }

    /*
    * Am I in the same square as u?
    */
    bool at(const Unit& u) const{
        return (x == u.x && y == u.y);
    }

    /*
    * Can I catch u in one move?
    */
    virtual bool attacks(const Unit& u) const = 0;

    /*
    * Take one step closer to u
    */
    virtual void moveTowards(const Unit& u) = 0;

    /*
    * Teleport. Does not check for collision
    */
    void teleport(){
        x = rand_int (MIN_X, MAX_X);
        y = rand_int (MIN_Y, MAX_Y);
    }

    /*
    * Euclidean distance to u
    */
    double distanceTo(const Unit& u) const{
        double dx = u.x - x;
        double dy = u.y - y;
        return sqrt(dx * dx + dy * dy);
    }

    /*
    * Draws self
    */
    virtual void draw(QGraphicsScene* scene) const = 0;

    virtual Unit* clone() const = 0;

private:
    int x;  // x position of this unit
    int y;  // y position of this unit

    // private helpers
    void checkBounds();
};

#endif // UNIT_H
