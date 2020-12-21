#include "Player.hpp"

#include <string>
#include <iostream>
#include <vector>

Player::Player(){
}

void Player::endGameBoolCheck() {
    endGameBool = true;
}

void Player::updateHPmovesCounter() {
    hpMovesCounter += 1;
}

int Player::getHPmovesCounter() {
    return hpMovesCounter;
}

void Player::updateHallucinateCounter(){
    hallucinateCounter +=1;
}

int Player::getHallucinateValue(){
    return hallucinateCounter;
}

void Player::setHallucinateMaxCount(int _count){
    count = _count;
}

int Player::getHallucinateMaxCount(){
    return count;
}

void Player::setWeapon(Item* sword){
    weapon = sword;
}

Item* Player::getWeapon(){
    return weapon;
}

void Player::setArmor(Item* armor){
    creatureArmor = armor;
}

Item* Player::getArmor(){
    return creatureArmor;
}

void Player::setName(std::string _name){
    name = _name;
}

std::string Player::getName(){
    return name;
}

void Player::addItemToPack(Item *item){
    itemsPack.push_back(item);
}

std::vector<Item *> Player::getItemPack() {
    return itemsPack;
}

void Player::removeItemFromPack(int itemNum){
    itemsPack.erase(itemsPack.begin() + itemNum);
    return;
}

void Player::Draw(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    int xPos = this->getXPos();
    int yPos = this->getYPos();
    char c = '@';
    grid->addObjectToDisplay(new GridChar(c), xPos, yPos);
    grid->update();
}

void Player::movePlayerLeft(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    int xPos = this->getXPos();
    int yPos = this->getYPos();
    GridChar c = grid->gridStack[xPos][yPos].back();
    grid->removeFromVector(xPos, yPos);


    this->setXPos(xPos - 1);
    int newX = this->getXPos();
    // char c = '@';
    grid->addObjectToDisplay(new GridChar(c), newX, yPos);
    grid->update();
}

void Player::movePlayerRight(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    int xPos = this->getXPos();
    int yPos = this->getYPos();
    GridChar c = grid->gridStack[xPos][yPos].back();
    grid->removeFromVector(xPos, yPos);


    this->setXPos(xPos + 1);
    int newX = this->getXPos();
    // char c = '@';
    grid->addObjectToDisplay(new GridChar(c), newX, yPos);
    grid->update();
}

void Player::movePlayerUp(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    int xPos = this->getXPos();
    int yPos = this->getYPos();
    GridChar c = grid->gridStack[xPos][yPos].back();
    grid->removeFromVector(xPos, yPos);


    this->setYPos(yPos - 1);
    int newY = this->getYPos();
    // char c = '@';
    grid->addObjectToDisplay(new GridChar(c), xPos, newY);
    grid->update();
}

void Player::movePlayerDown(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    int xPos = this->getXPos();
    int yPos = this->getYPos();
    GridChar c = grid->gridStack[xPos][yPos].back();
    grid->removeFromVector(xPos, yPos);


    this->setYPos(yPos + 1);
    int newY = this->getYPos();
    // char c = '@';
    grid->addObjectToDisplay(new GridChar(c), xPos, newY);
    grid->update();
}