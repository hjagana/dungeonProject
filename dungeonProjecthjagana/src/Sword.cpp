#include "Sword.hpp"

#include <string>
#include <iostream>

Sword::Sword(std::string name){
}

void Sword::setId(int room, int serial){
}

void Sword::setName(std::string _itemName){
    itemName = _itemName;
}

std::string Sword::getName(){
    return itemName;
}

void Sword::Draw(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    int x = this->getXPos();
    int y = this->getYPos();

    char c = ')';
    grid->addObjectToDisplay(new GridChar(c), x, y);

    grid->update();
}