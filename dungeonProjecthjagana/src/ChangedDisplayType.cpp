#include "ChangedDisplayType.hpp"
#include "Creature.hpp"

#include <string>
#include <iostream>

ChangedDisplayType::ChangedDisplayType(std::string name, Creature *owner): CreatureAction(owner){
    c = owner;
}

void ChangedDisplayType::performAction() {
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    grid->addObjectToDisplay(new GridChar(this->getChar()), c->getXPos(), c->getYPos());
    grid->update();
    // call getCharValue from Action and change what the dead player looks like
}