#include "Remove.hpp"
#include "Creature.hpp"

#include <string>
#include <iostream>

Remove::Remove(std::string name, Creature *owner): CreatureAction(owner){
    c = owner;
    // std::cout <<"Remove:" << std::endl;
}

void Remove::performAction() {
    ObjectDisplayGrid* grid = ObjectDisplayGrid::getGrid();
    grid->removeFromVector(c->getXPos(), c->getYPos());
    // remove Creature from display after death
}