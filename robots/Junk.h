/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Robot.h"
#include "Unit.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk();
    Junk(Unit c);

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;
    bool isJunk() const override;
    void moveTowards(const Unit& u) override;
    bool attacks(const Unit& u) const override;
    virtual Junk* clone() const override;
};

#endif // JUNK_H
