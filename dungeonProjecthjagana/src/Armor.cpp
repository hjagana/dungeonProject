#include "Armor.hpp"

#include <string>
#include <iostream>

Armor::Armor(std::string name){
}


void Armor::setName(std::string _itemName){
    itemName = _itemName;
}

std::string Armor::getName(){
    return itemName;
}

void Armor::setId(int room, int serial){
}

void Armor::Draw(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    int x = this->getXPos();
    int y = this->getYPos();
    char c = ']';
    grid->addObjectToDisplay(new GridChar(c), x, y);

    grid->update();
}