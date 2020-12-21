#include "Item.hpp"
#include "ItemAction.hpp"

#include <string>
#include <iostream>

Item::Item(){
}

void Item::setOwner(Creature* _owner){
    owner = _owner;
}

Creature* Item::getOwner(){
    return owner;
}

void Item::setItemAction(ItemAction *ia){
    action = ia;
}

ItemAction* Item::getItemAction(){
    return action;
}

void Item::setCount(int _count){
    count = _count;
}

int Item::getCount(){
    return count;
}

// void Item::performHallucinate(){
//     ItemAction * itemAction = this->getItemAction();
//     //perform hallucinate
// }

// int Item::getRandNum(){
//     int randNum = rand() % (9 + 1) + 0;
//     return randNum;
// }

// char Item::getRandomCharacter(int i){
//     return randomItemChars[i];
// }
