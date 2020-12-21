#include "YouWin.hpp"
#include "Creature.hpp"
#include <string>
#include <iostream>

YouWin::YouWin(std::string name, Creature *owner): CreatureAction(owner){
    c = owner;
}

void YouWin::performAction() {
    ObjectDisplayGrid* grid = ObjectDisplayGrid::getGrid();
    grid->writeLine(2, "Info: " + this->getMessage()); // executed by creature that is killed prints message from actionMessage
    c->setScoreVal(this->getInt()); // updates score of player after killing creature by actionIntValue
}