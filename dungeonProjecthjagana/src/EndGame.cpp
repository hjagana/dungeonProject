#include "EndGame.hpp"
#include "Creature.hpp"
#include "KeyboardListener.hpp"
#include <string>
#include <iostream>

EndGame::EndGame(std::string name, Creature *owner): CreatureAction(owner){
    // std::cout <<"EndGame:" << std::endl;
    c = owner;
}

void EndGame::performAction() {
    ObjectDisplayGrid * grid = ObjectDisplayGrid::getGrid();
    grid->writeLine(2, "Info: " + this->getMessage());
    // k->setEndGameBool(); instead of this just create the boolean in player since its accessible by the Keyboard listener
    // prints Death message for player
}