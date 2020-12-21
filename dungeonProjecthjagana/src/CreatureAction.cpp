#include "CreatureAction.hpp"
// #include "Creature.hpp"

#include <string>
#include <iostream>

CreatureAction::CreatureAction(Creature* owner){
    c = owner;
    // std::cout <<"CreatureAction:" << std::endl;
}

void CreatureAction::performAction() {
}