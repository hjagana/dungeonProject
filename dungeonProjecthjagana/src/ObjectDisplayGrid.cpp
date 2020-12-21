#include <curses.h>
#include "ObjectDisplayGrid.hpp"

#include <string>
#include <iostream>


ObjectDisplayGrid* ObjectDisplayGrid::objGrid = NULL;
ObjectDisplayGrid* ObjectDisplayGrid::getGrid(int _width, int _height, int _messages){
    if (objGrid == NULL){
        objGrid = new ObjectDisplayGrid(_width, _height, _messages);
    }
    return objGrid;
}
ObjectDisplayGrid* ObjectDisplayGrid::getGrid(){
	if (objGrid == NULL){
		std::cout << "The object grid is empty" << std::endl;
	}
    return objGrid;
}

ObjectDisplayGrid::ObjectDisplayGrid(int _width, int _height, int _messages) : width(_width), height(_height), messages(_messages) {	
	gridStack = new std::vector<GridChar>*[width];
	for (int i = 0; i < width; i++) {
		gridStack[i] = new std::vector<GridChar>[height];
	}
	
	initscr();
	cbreak(); 
	noecho();
	clear();
}

void ObjectDisplayGrid::getObjectDisplayGrid(int gameHeight, int width, int topHeight){
}

void ObjectDisplayGrid::setTopMessageHeight(int topHeight){
	topMessageHeight = topHeight;
}

ObjectDisplayGrid::~ObjectDisplayGrid() {
	for (int i = 0; i < width; i++) {
		delete[] gridStack[i];
	}
	delete[] gridStack;
	gridStack = NULL;

	endwin();
}

void ObjectDisplayGrid::removeFromVector(int x, int y){
	if ((0 <= x) && (x < width)) {
		if ((0 <= y) && (y < height)) {
			if (!(gridStack[x][y].empty())){
				gridStack[x][y].pop_back();
				if (!(gridStack[x][y].empty()))
				{
					GridChar ch = gridStack[x][y].back();
					mvaddch(y + topMessageHeight, x, ch.getChar());
				}
				else{
					mvaddch(y + topMessageHeight, x, ' ');
				}
			}
		}
	}
}

void ObjectDisplayGrid::addObjectToDisplay(GridChar* ch, int x, int y) {
	if ((0 <= x) && (x < width)) {
		if ((0 <= y) && (y < height)) {
            gridStack[x][y].push_back(*ch);
			mvaddch(y + topMessageHeight, x, ch->getChar());
		}
	}
}

void ObjectDisplayGrid::update() {
	refresh();
}

void ObjectDisplayGrid::writeLine(int line, std::string message) {
	mvaddstr(height + line + topMessageHeight, 0, message.c_str());
	clrtoeol();
	update();
}

void ObjectDisplayGrid::writeTopLine(int line, std::string message) {
	mvaddstr(0 + line, 0, message.c_str());
	clrtoeol();
	update();
}
