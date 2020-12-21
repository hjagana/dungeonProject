#include "Room.hpp"

#include <string>
#include <iostream>

Room::Room(std::string room){
}

void Room::setId(int room) {
    roomId = room;
}

int Room::getId(){
    return roomId;
}

void Room::setCreature(Creature *Monster){
    creature = Monster;
}

Creature* Room::getCreature(){
    return creature;
}

bool Room::checkMove(int x, int y){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    int width = this->getWidth();
    int height = this->getHeight();
    int offsetx = this->getXPos();
    int offsety = this->getYPos();
    bool pass = false;
    //determine what room they are in
    if (x > offsetx && x < offsetx + width && y > offsety && y < offsety + height){
        for (int i = offsetx; i < (width + offsetx); i ++){
            for(int j = offsety; j < (height + offsety); j++){
                GridChar ch = grid->gridStack[x][y].back();
                if(ch.getChar() == 'T' || ch.getChar() == 'H' || ch.getChar() == 'S'){
                    //don't move if there is a creature there
                    return false;
                }
                if(x == offsetx || (x == width - 1 + offsetx) || (y == offsety) || (y == height - 1 + offsety)){
                    //this would be on the border of a room
                    return false;
                }
                else{
                    pass = true;
                }
            }
        }
    }
    return pass;
}

void Room::Draw(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    int width = this->getWidth();
    int height = this->getHeight();
    int offsetx = this->getXPos();
    int offsetY = this->getYPos();

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            char c;
            if(i == 0 || (i == width - 1) || j == 0 || (j == height - 1)){
                c = 'X';
            }
            else{
                c = '.';
            }
            grid->addObjectToDisplay(new GridChar(c), i + offsetx, j + offsetY);
        }
    }
    grid->update();
}
