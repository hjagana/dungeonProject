#include "Creature.hpp"
#include <string>
#include <iostream>

Creature::Creature(){
}

void Creature::setScoreVal(int s){
    scoreVal += s;
}

void Creature::setHpMoves(int hpm){
    hpMoves = hpm;
}

void Creature::addDeathAction(CreatureAction *da) {
    deathActionsVector.push_back(da);
    //deathActionMessage = da->getMessage();
}

void Creature::addHitAction(CreatureAction *ha) {
    hitActionsVector.push_back(ha);
    //hitActionMessage = ha->getMessage();
}

int Creature::getScoreVal() {
    return scoreVal;
}


int Creature::getHpMoves() {
    return hpMoves;
}

int Creature::getDeathActionVectorSize() {
    int size = deathActionsVector.size();
    return size;
}

void Creature::Draw(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    int x = this->getXPos();
    int y = this->getYPos();
    char c = 'C';
    grid->addObjectToDisplay(new GridChar(c), x, y);
    grid->update();
}

void Creature::runDeathAction() {
    for (CreatureAction* cA: deathActionsVector) {
        cA->performAction();
    }
}

void Creature::runHitAction() {
    for (CreatureAction* cA: hitActionsVector) {
        cA->performAction();
    }
}