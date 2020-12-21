#include "Passage.hpp"

#include <string>
#include <iostream>


Passage::Passage(){
}

void Passage::setName(std::string name) {
}

void Passage::setId(int room1, int room2){
}

void Passage::setXPos(int x){
    xx.push_back(x);
}

void Passage::setYPos(int y){
    yy.push_back(y);
}

bool Passage::checkMove(int x, int y){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    if (!(grid->gridStack[x][y].empty())){
        GridChar ch = grid->gridStack[x][y].back();
        bool pass = false;
        if(ch.getChar() == '#' || ch.getChar() == '+' || ch.getChar() == '.'){
            return pass = true;
        }
        return pass;
    }

    return false;
}

void Passage::Draw(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    // grid->writeLine(1, std::to_string(xx.size()));
    // grid->writeLine(2, std::to_string(yy.size()));

    for (int i = 1; i < xx.size(); i++){
        int x = xx[i -1];
        int y = yy[i - 1];
        int x1 = xx[i];
        int y1 = yy[i];

        if (x1 != x){
            int xsmall = 0;
            int xbig = 0;
            if (x - x1 > 0){
                xsmall = x1;
                xbig = x;
            }
            else if (x - x1 < 0){
                xsmall = x;
                xbig = x1;
            }
            for (int first = xsmall; first <= xbig; first++){
                char c = '#';
                grid->addObjectToDisplay(new GridChar(c), first, y);
            }
        }
        else if (y1 != y){
            int ysmall = 0;
            int ybig = 0;
            if (y - y1 > 0){
                ysmall = y1;
                ybig = y;
            }
            else if (y - y1 < 0){
                ysmall = y;
                ybig = y1;
            }
            for (int first = ysmall; first <= ybig; first++){
                char c = '#';
                grid->addObjectToDisplay(new GridChar(c), x, first);
            }
        }
    }

    int x1 = xx[0];
    int y1 = yy[0];
    char c = '+';
    grid->addObjectToDisplay(new GridChar(c), x1, y1);
    int xLast = xx[xx.size() - 1];
    int yLast = yy[yy.size() - 1];
    c = '+';
    grid->addObjectToDisplay(new GridChar(c), xLast, yLast);

    grid->update();

    // // object display grid contains all the displayable things and their positions
    // // interface between displayable objects and terminal
    // //keeps track of where things are
    // //
    // //room should have a list of displayables
    // //dungeon goes through list of rooms and passages
    //     //they should draw themselves
    //     //draw function should then iterate through creature vector and item vector and call draw on those
    //     //check character so you can't walk through walls
    
    // //push the thing to the position that it is at
    // //then add object should reflect it to ncurses
}