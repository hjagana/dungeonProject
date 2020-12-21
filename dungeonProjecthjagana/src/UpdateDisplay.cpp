#include "UpdateDisplay.hpp"
#include "Creature.hpp"

#include <string>
#include <iostream>

UpdateDisplay::UpdateDisplay(std::string name, Creature *owner): CreatureAction(owner){
    c = owner;
}

void UpdateDisplay::performAction() {
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    c->setHp(0);
    grid->writeTopLine(0, "HP: " + std::to_string(c->getHp()));
    grid->update();
    // update display of creature
}