#include "Scroll.hpp"

#include <string>
#include <iostream>

Scroll::Scroll(std::string name){
}

void Scroll::setId(int room, int serial){

}

void Scroll::setName(std::string _itemName){
    itemName = _itemName;
}

std::string Scroll::getName(){
    return itemName;
}

void Scroll::Draw(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    // int width = this->getWidth();
    // int height = this->getHeight();
    int x = this->getXPos();
    int y = this->getYPos();
    // Creature * owner = this->getOwner();
    // std::cout << "item" << std::endl;
    // owner.get
    char c = '?';
    grid->addObjectToDisplay(new GridChar(c), x, y);

    grid->update();
}