#include "Teleport.hpp"
#include "Creature.hpp"

#include <string>
#include <iostream>

Teleport::Teleport(std::string name, Creature *owner): CreatureAction(owner){
    // std::cout <<"Teleport:" << std::endl;
    c = owner;
}


void Teleport::performAction() {
    ObjectDisplayGrid* grid = ObjectDisplayGrid::getGrid();
    grid->removeFromVector(c->getXPos(), c->getYPos());
    c->setXPos(30);
    c->setYPos(16);
    grid->addObjectToDisplay(new GridChar('T'), 30, 16);
    grid->writeLine(2, "Info: " + this->getMessage()); // executed by creature that is killed prints message from actionMessage
    c->setScoreVal(this->getInt()); // updates score of player after killing creature by actionIntValue

    // std::vector<Point*> teleportLocations;

    // c->setXPos(c->getXpos())
    // moves creature  to random place in the dungeon or passages
}

// bool Dungeon::checkMove(int x, int y){
//     std::vector<Room *> roomVector = this->getRooms();
//     std::vector<Monster *> creatureVector = this->getCreatures();
//     std::vector<Item *> itemVector = this->getItems();
//     std::vector<Passage *> passageVector = this->getPassages();
//     bool pass = false;

//     for (Room* room : roomVector) {
//         pass = room->checkMove(x, y);
//         if (pass == true){
//             break;
//         }
//     }
    
//     for(Passage* passage: passageVector){
//         pass = passage->checkMove(x,y);
//         if (pass == true){
//             break;
//         }
//     }    
//     return pass;
// }

// bool Room::checkMove(int x, int y){
//     ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
//     int width = this->getWidth();
//     int height = this->getHeight();
//     int offsetx = this->getXPos();
//     int offsety = this->getYPos();
//     bool pass = false;
//     //determine what room they are in
//     if (x > offsetx && x < offsetx + width && y > offsety && y < offsety + height){
//         for (int i = offsetx; i < (width + offsetx); i ++){
//             for(int j = offsety; j < (height + offsety); j++){
//                 GridChar ch = grid->gridStack[x][y].back();
//                 if(ch.getChar() == 'T' || ch.getChar() == 'H' || ch.getChar() == 'S'){
//                     //don't move if there is a creature there
//                     return false;
//                 }
//                 if(x == offsetx || (x == width - 1 + offsetx) || (y == offsety) || (y == height - 1 + offsety)){
//                     //this would be on the border of a room
//                     return false;
//                 }
//                 else{
//                     pass = true;
//                 }
//             }
//         }
//     }
//     return pass;
// }

// bool Passage::checkMove(int x, int y){
//     ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
//     if (!(grid->gridStack[x][y].empty())){
//         GridChar ch = grid->gridStack[x][y].back();
//         bool pass = false;
//         if(ch.getChar() == '#' || ch.getChar() == '+' || ch.getChar() == '.'){
//             return pass = true;
//         }
//         return pass;
//     }

//     return false;
// }