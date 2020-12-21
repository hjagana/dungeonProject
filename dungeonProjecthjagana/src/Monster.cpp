#include "Monster.hpp"

#include <string>
#include <iostream>

Monster::Monster(){
}

void Monster::setName(std::string name) {
    nameId = name;
}

std::string Monster::getName(){
    return nameId;
}

void Monster::setId(int room, int serial){
}

bool Monster::checkCollision(int x, int y){
    int monsterX = this->getXPos();
    int monsterY = this->getYPos();

    if(x == monsterX && y == monsterY){
        return true;
    }
    return false;
}

void Monster::Draw(){
    std::string type = this->getName(); //type of monster
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();

    if (type == "Troll"){
        int x = this->getXPos();
        int y = this->getYPos();
        char c = 'T';
        grid->addObjectToDisplay(new GridChar(c), x, y);
    }
    else if (type == "Snake"){
        int x = this->getXPos();
        int y = this->getYPos();
        char c = 'S';
        grid->addObjectToDisplay(new GridChar(c), x, y);
    }
    else if (type == "Hobgoblin"){
        int x = this->getXPos();
        int y = this->getYPos();
        char c = 'H';
        grid->addObjectToDisplay(new GridChar(c), x, y);
    }
    grid->update();
}