/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Junk.h"
#include "constants.h"

Junk::Junk() : Robot() {}
Junk::Junk(Unit c) : Robot(c) {}

void Junk::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(JUNK_COLOR));
}

bool Junk::isJunk() const{
    return true;
}

/*
 *kolla upp korrekt ärvningsdefinition så den kan manipulera egna variabler
 */
bool Junk::attacks(const Unit& u) const{
    Point p1 = u.asPoint();
    Point p2 = this->asPoint();
    return p1.x == p2.x && p1.y == p2.y;
}

void Junk::moveTowards(const Unit &u){

}

Junk* Junk::clone() const{
    return new Junk(*this);
}
