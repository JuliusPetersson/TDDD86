/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Hero.h"
#include "constants.h"

Hero::Hero() : Unit() {}
Hero::Hero(Unit& u) : unit(u){}

void Hero::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addRect(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                          UNIT_WIDTH, UNIT_HEIGHT), Qt::NoPen, QBrush(HERO_COLOR));
}

bool attacks(const Unit& u) const{
    return false;
}

Hero* Hero::clone() const{
    return new Hero(this);
}

void moveTowards(const Unit& u){
    Unit::moveTowards(u);
}
