//  class file for Cell

#ifndef Conways
#include "Conways.h"
using namespace Conways;
#endif


Cell::Cell()    {
    alive = false;
}

void Cell::setAlive()   {
    alive = true;
}

void Cell::setDead()    {
    alive = false;
}

bool Cell::getState() {
    return alive;
}