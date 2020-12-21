#include "DropPack.hpp"
#include "Dungeon.hpp"

#include <string>
#include <iostream>

DropPack::DropPack(std::string name, Creature *owner): CreatureAction(owner){
    // std::cout <<"DropPack:" << std::endl;
}

void DropPack::performAction() {
    ObjectDisplayGrid* grid = ObjectDisplayGrid::getGrid();
    Dungeon* d = Dungeon::getDungeon();
    bool pass = false;
    pass = d->dropItemFromPack(49, d->getItemCount());
    if (pass) {
        grid->writeLine(3, "      " + this->getMessage());
    } else {
        grid->writeLine(3, "Info: Pack is empty!");
    }
    // drop the item in spot 0 of the pack
    // pack empty dont do anything
}