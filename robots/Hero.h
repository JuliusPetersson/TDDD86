/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef HERO_H
#define HERO_H

#include "Unit.h"
#include <QGraphicsScene>

class Hero : public Unit {
public:
    Hero();
    Hero(Unit& u);

    /*
    * Draws this hero onto the given QGraphicsScene.
    */
    bool attacks(const Unit& u) const override;
    void draw(QGraphicsScene *scene) const override;
    Hero* clone() const override;
    void moveTowards(const Point& u);
};

#endif // HERO_H
