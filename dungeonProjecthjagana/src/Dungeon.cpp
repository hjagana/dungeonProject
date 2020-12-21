#include "Dungeon.hpp"
#include "Hallucinate.hpp"
#include "BlessCurseOwner.hpp"
#include <string>
#include <iostream>

Dungeon::Dungeon(){
}

Dungeon* Dungeon::dungeonCreated = nullptr;

Dungeon* Dungeon::getDungeon(){
    if (dungeonCreated == NULL){
        dungeonCreated = new Dungeon();
    }
    return dungeonCreated;
}

void Dungeon::addRoom(Room *room) {
    rooms.push_back(room);
}

std::vector<Room *> Dungeon::getRooms() {
    return rooms;
}

void Dungeon::addPlayer(Player *_player){
    player = _player;
}

Player* Dungeon::getPlayer(){
    return player;
}

void Dungeon::addCreatue(Monster *creature) {
    creatures.push_back(creature);
}

std::vector<Monster *> Dungeon::getCreatures() {
    return creatures;
}

void Dungeon::addPassage(Passage *passage) {
    passages.push_back(passage);
}
std::vector<Passage *> Dungeon::getPassages() {
    return passages;
}

void Dungeon::addItem(Item *item) {
    items.push_back(item);
}

std::vector<Item *> Dungeon::getItems() {
    return items;
}

void Dungeon::setwidth(int _width){
    width = _width;
}

int Dungeon::getwidth(){
    return width;
}

void Dungeon::setTopHeight(int _topHeight){
    topHeight = _topHeight;
}

int Dungeon::getTopHeight(){
    return topHeight;
}

void Dungeon::setGameHeight(int _gameHeight){
    gameHeight = _gameHeight;
}

int Dungeon::getGameHeight(){
    return gameHeight;
}

void Dungeon::setBottomHeight(int _bottomHeight){
    bottomHeight = _bottomHeight;
}

int Dungeon::getBottomHeight(){
    return bottomHeight;
}

void Dungeon::setItemCount(int x) {
    itemCountK = x;
}

int Dungeon::getItemCount(){
    return itemCountK;
}

bool Dungeon::checkMove(int x, int y){
    std::vector<Room *> roomVector = this->getRooms();
    std::vector<Monster *> creatureVector = this->getCreatures();
    std::vector<Item *> itemVector = this->getItems();
    std::vector<Passage *> passageVector = this->getPassages();
    bool pass = false;

    for (Room* room : roomVector) {
        pass = room->checkMove(x, y);
        if (pass == true){
            break;
        }
    }
    
    for(Passage* passage: passageVector){
        pass = passage->checkMove(x,y);
        if (pass == true){
            break;
        }
    }    
    return pass;
}

bool Dungeon::checkCollision(int x, int y){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    Player *player = this->getPlayer();
    std::vector<Monster *> creatureVector = this->getCreatures();
    bool pass = false;
    for(Monster* creature: creatureVector){
        pass = creature->checkCollision(x, y);
        if (pass == true){
            grid->writeLine(1, " ");
            int hit = creature->getMaxHit();
            grid->writeLine(2, "Info: " + creature->getName() + " did " + std::to_string(hit) + " damage!");
            grid->writeLine(3, " ");
            grid->writeLine(4, " ");
            int playerHealth = player->getHp();
            if (player->getArmor()) {
                playerHealth += player->getArmor()->getIntValue();
            }
            player->setHp(playerHealth-hit);
            player->runHitAction();
    

            int playerhit = player->getMaxHit();
            if (player->getWeapon()) {
                playerhit += player->getWeapon()->getIntValue();
            }
            grid->writeLine(2, "Info: " + (std::string) "Player" + " did " + std::to_string(playerhit) + " damage!");
            grid->writeLine(3, " ");
            grid->writeLine(4, " ");
            int monsterHealth = creature->getHp();
            creature->setHp(monsterHealth - playerhit);
            creature->runHitAction();
            if (creature->getHp() <= 0 ){
                if(creature->getDeathActionVectorSize() > 0){
                    creature->runDeathAction(); // <- run things like Remove and You Win
                }
                else{
                    grid->removeFromVector(x, y);
                }
                
            }
            if(player->getHp() <= 0) {
                player->runDeathAction(); 
            }
            return pass;
        }
    }
    return pass;
}

bool Dungeon::addItemToPack(int x, int y){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    Player *player = this->getPlayer();
    std::vector<Item *> itemVector = this->getItems();

    Item *itemHighCount = nullptr;
    for(Item* item: itemVector){
        int itemX = item->getXPos();
        int itemY = item->getYPos();
        if(x == itemX && y == itemY ){//&& item->getOwner() == nullptr){
            if(itemHighCount == nullptr){
                itemHighCount = item;
            }
            else{
                int highCount = itemHighCount->getCount();
                int itemCount = item->getCount();
                if (itemCount > highCount){
                    itemHighCount = item;
                }
            }
        }
    }

    if (itemHighCount != nullptr){
        itemHighCount->setOwner(nullptr);
        player->addItemToPack(itemHighCount);
        itemHighCount->setXPos(-1);
        itemHighCount->setYPos(-1);
        grid->gridStack[x][y].pop_back();
        grid->gridStack[x][y].pop_back();
        grid->gridStack[x][y].push_back('@');
        //reset count when added to the pack
        // grid->writeLine(2, "Info: item picked up and put into pack");
        grid->writeLine(3, " ");
        grid->writeLine(4, " ");
        if(itemHighCount->getName() == "Scroll"){
            grid->writeLine(2, "Info: " + itemHighCount->getName() + " picked up and put into pack");
        }
        else if(itemHighCount->getIntValue() > 0){
            grid->writeLine(2, "Info: +" + std::to_string(itemHighCount->getIntValue()) + " " + itemHighCount->getName() + " picked up and put into pack");
        }
        else if(itemHighCount->getIntValue() < 0){
            grid->writeLine(2, "Info: -" + std::to_string(itemHighCount->getIntValue()) + " " + itemHighCount->getName() + " picked up and put into pack");
        }
        itemHighCount->setCount(0);
        return true;
    }
    return false;
}

bool Dungeon::dropItemFromPack(int itemNum, int count){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    Player *player = this->getPlayer();
    std::vector<Item *> itemPack = player->getItemPack();

    if ((itemNum - 48 - 1) >= itemPack.size()){
        return false;
    }
    //check if the player owns the item and if it does then clear it)
    Item *item = itemPack[itemNum - 48 - 1];
    if(item->getOwner()){
        if(item->getName() == "Armor"){
            player->setArmor(NULL);
        }
        else if (item->getName() == "Sword"){
            player->setWeapon(NULL);
        }
    }
    if (item){
        int playerX = player->getXPos();
        int playerY = player->getYPos();
        std::string name = item->getName();
        item->setXPos(playerX);
        item->setYPos(playerY);
        item->setCount(count);
        item->setOwner(nullptr);

        char ch = '\0';
        if (name == "Sword"){
            ch = ')';
        }
        else if(name == "Armor"){
            ch = ']';
        }
        else if (name == "Scroll"){
            ch = '?';
        }
        grid->gridStack[playerX][playerY].pop_back();
        grid->gridStack[playerX][playerY].push_back(ch);
        grid->gridStack[playerX][playerY].push_back('@');
        grid->update();
        player->removeItemFromPack(itemNum - 49);
        return true;
    }
    return false;
}

void Dungeon::displayItemsInPack(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    Player *player = this->getPlayer();
    std::vector<Item *> itemPack = player->getItemPack();
    int counter = 1;
    std::string itemString;
    for (Item* item: itemPack){
        //check if the player owns it
        if(item->getOwner() == nullptr){
            if(item->getName() == "Scroll"){
                itemString += std::to_string(counter) + ": " + item->getName() + "   ";
            }
            else if(item->getIntValue() >= 0){
                itemString += std::to_string(counter) + ": +" + std::to_string(item->getIntValue()) + " " + item->getName() + "   ";
            }
            else if(item->getIntValue() < 0){
                itemString += std::to_string(counter) + ": -" + std::to_string(item->getIntValue()) + " " + item->getName() + "   ";
            }
        }
        //the player owns the item
        else{
            if(item->getName() == "Armor"){
                if(item->getIntValue() >= 0){
                    itemString += std::to_string(counter) + ": +" + std::to_string(item->getIntValue()) + " " + item->getName() + "(a)   ";
                }
                else if(item->getIntValue() < 0){
                    itemString += std::to_string(counter) + ": -" + std::to_string(item->getIntValue()) + " " + item->getName() + "(a)   ";
                }
            }
            else if (item->getName() == "Sword"){
                if(item->getIntValue() >= 0){
                    itemString += std::to_string(counter) + ": +" + std::to_string(item->getIntValue()) + " " + item->getName() + "(w)   ";
                }
                else if(item->getIntValue() < 0){
                    itemString += std::to_string(counter) + ": -" + std::to_string(item->getIntValue()) + " " + item->getName() + "(w)   ";
                }
            }

        }
        counter++;
    }


    grid->writeLine(1, "Pack: " + itemString);
    grid->writeLine(2, "Info: ");
    grid->writeLine(3, " ");
    grid->writeLine(4, " ");
}

bool Dungeon::checkArmor(){
    Player *player = this->getPlayer();
    if(player->getArmor()){
        Item* armor = player->getArmor();
        player->setArmor(NULL);
        armor->setOwner(nullptr); //change the owner of the item
        return true;
    }
    return false;
}

bool Dungeon::checkArmorInPack(int armorNum){
    Player *player = this->getPlayer();
    std::vector<Item *> itemPack = player->getItemPack();

    Item *item = itemPack[armorNum - 48 - 1];
    if (item->getName() == "Armor"){
        player->setArmor(item);
        item->setOwner(player);
        return true;
    }
    return false;

}

bool Dungeon::checkScrollInPack(int scrollNum){
    Player *player = this->getPlayer();
    std::vector<Item *> itemPack = player->getItemPack();

    Item *item = itemPack[scrollNum - 48 - 1];
    if(item->getName() == "Scroll"){
        return true;
    }
    return false;
}

int Dungeon::performAction(int scrollNum, bool hallucinate, bool blessCurse){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    Player *player = this->getPlayer();
    std::vector<Item *> itemPack = player->getItemPack();
    Item *item = itemPack[scrollNum - 48 - 1];
    ItemAction *itemaction = item->getItemAction();
    
    Hallucinate *hallucinateAction = dynamic_cast<Hallucinate*> (itemaction);
    if(hallucinateAction){
        std::string message = hallucinateAction->getMessage();
        int halluCount = itemaction->getInt();
        player->setHallucinateMaxCount(halluCount);
        player->removeItemFromPack(scrollNum - 49);
        grid->writeLine(3, "    " + message);
        grid->writeLine(4, " ");
        return 2;
    }

    BlessCurseOwner *blesscurse = dynamic_cast <BlessCurseOwner*> (itemaction);
    if(blesscurse){
        return 3;
    }
    return 0;
}

bool Dungeon::blessCurse(int scrollNum){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    Player *player = this->getPlayer();
    std::vector<Item *> itemPack = player->getItemPack();
    Item *item = itemPack[scrollNum - 48 - 1];

    Action* action = dynamic_cast<Action*> (item->getItemAction());
    if(action){
        std::string message = action->getMessage();
        int actionVal = action->getInt();
        char character = action->getChar();

        if (character == 'a'){
            Item *armor = player->getArmor();
            if(armor){
                int itemNum = armor->getIntValue();
                armor->setIntValue(itemNum + actionVal);
                grid->writeLine(1, " ");
                grid->writeLine(3, "    scroll affected armor by " + std::to_string(itemNum));
                grid->writeLine(4, "    " + message);
                return true;
            }
            else{
                grid->writeLine(1, " ");
                grid->writeLine(3, "    scroll of cursing does nothing because player is not wearing armor");
                grid->writeLine(4, "    " + message);
                return false;
            }
        }
        else if (character == 'w'){
            Item *sword = player->getWeapon();
            if(sword){
                int itemNum = sword->getIntValue();
                sword->setIntValue(itemNum + actionVal);
                grid->writeLine(1, " ");
                grid->writeLine(3, "    scroll affected sword by " + std::to_string(itemNum));
                grid->writeLine(4, "    " + message);
                return true;
            }
            else{
                grid->writeLine(1, " ");
                grid->writeLine(3, "    scroll of cursing does nothing because player is not using sword");
                grid->writeLine(4, " ");
                return false;
            }
        }
        return true;
    }
    return false;
}

void Dungeon::hallucinate(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    std::vector<Item *> itemVector = this->getItems();
    std::vector<Room *> roomVector = this->getRooms();
    std::vector<Monster *> creatureVector = this->getCreatures();

    for (Room* room : roomVector) {
        int width = room->getWidth();
        int height = room->getHeight();
        int offsetx = room->getXPos();
        int offsetY = room->getYPos();

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int random = room->getRandNum();
                char c = room->getRandomCharacter(random);
                grid->addObjectToDisplay(new GridChar(c), i + offsetx, j + offsetY);
            }
        }
        grid->update();
    }
    
    for(Monster* creature: creatureVector){
        std::string type = creature->getName(); //type of monster
        int x = creature->getXPos();
        int y = creature->getYPos();
        int random = creature->getRandNum();
        char c = creature->getRandomCharacter(random);
        grid->removeFromVector(x,y);
        grid->addObjectToDisplay(new GridChar(c), x, y);
        grid->update();
    }

    for(Item* item: itemVector){
        if (item->getOwner() == nullptr){
            int random = item->getRandNum();
            int x = item->getXPos();
            int y = item->getXPos();
            char c = item->getRandomCharacter(random);
            grid->removeFromVector(x,y);
            grid->addObjectToDisplay(new GridChar(c), x, y);
            grid->update();
        }
    }

    Player *player = this->getPlayer();
    int xPos = player->getXPos();
    int yPos = player->getYPos();
    int random = player->getRandNum();
    char c = player->getRandomCharacter(random);
    grid->removeFromVector(xPos,yPos);
    grid->addObjectToDisplay(new GridChar(c), xPos, yPos);
    grid->update();
}

void Dungeon::drawNormal(){
    ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
    std::vector<Item *> itemVector = this->getItems();
    std::vector<Room *> roomVector = this->getRooms();
    std::vector<Monster *> creatureVector = this->getCreatures();

    for(Room* room: roomVector){
        ObjectDisplayGrid *grid = ObjectDisplayGrid::getGrid();
        int width = room->getWidth();
        int height = room->getHeight();
        int offsetx = room->getXPos();
        int offsetY = room->getYPos();

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

    for (Monster *creature: creatureVector){
        std::string type = creature->getName();

        if (type == "Troll"){
            int x = creature->getXPos();
            int y = creature->getYPos();
            char c = 'T';
            grid->removeFromVector(x,y);
            grid->addObjectToDisplay(new GridChar(c), x, y);
        }
        else if (type == "Snake"){
            int x = creature->getXPos();
            int y = creature->getYPos();
            char c = 'S';
            grid->removeFromVector(x,y);
            grid->addObjectToDisplay(new GridChar(c), x, y);
        }
        else if (type == "Hobgoblin"){
            int x = creature->getXPos();
            int y = creature->getYPos();
            char c = 'H';
            grid->removeFromVector(x,y);
            grid->addObjectToDisplay(new GridChar(c), x, y);
        }
        grid->update();
    }
    

    for(Item* item: itemVector){
        std::string name = item->getName();
        int x = item->getXPos();
        int y = item->getXPos();

        char ch = '\0';
        if (name == "Sword"){
            ch = ')';
        }
        else if(name == "Armor"){
            ch = ']';
        }
        else if (name == "Scroll"){
            ch = '?';
        }
        grid->removeFromVector(x,y);
        grid->addObjectToDisplay(new GridChar(ch), x, y);
        grid->update();
    }

    Player *player = this->getPlayer();
    int xPos = player->getXPos();
    int yPos = player->getYPos();
    char c = '@';
    // grid->removeFromVector(xPos,yPos);
    grid->addObjectToDisplay(new GridChar(c), xPos, yPos);
    grid->update();

}

bool Dungeon::checkSwordInPack(int swordNum){
    Player *player = this->getPlayer();
    std::vector<Item *> itemPack = player->getItemPack();

    Item *item = itemPack[swordNum - 48 - 1];
    if(item->getName() == "Sword"){
        return true;
    }
    return false;
}

void Dungeon::swapSword(int swordNum){
    Player *player = this->getPlayer();
    std::vector<Item *> itemPack = player->getItemPack();

    Item *item = itemPack[swordNum - 48 - 1];
    Item *swapItem = player->getWeapon();
    if(swapItem){
        player->setWeapon(item);
        swapItem->setOwner(nullptr);
        item->setOwner(player);
    }
    //the player does not already have a weapon
    else{
        player->setWeapon(item);
        item->setOwner(player);
    }
    return;
}

void Dungeon::Draw() {
    std::vector<Room *> roomVector = this->getRooms();
    std::vector<Monster *> creatureVector = this->getCreatures();
    std::vector<Item *> itemVector = this->getItems();
    std::vector<Passage *> passageVector = this->getPassages();
    
    for (Room* room : roomVector) {
        room->Draw();
    }

    for(Item* item: itemVector){
        if (item->getOwner() == nullptr){
            item->Draw();
        }
        else{
            item->setOwner(nullptr);
        }
        item->setCount(0);
    }
    
    for(Passage* passage: passageVector){
        passage->Draw();
    }

    for(Monster* creature: creatureVector){
        creature->Draw();
    }
    Player *player = this->getPlayer();
    player->Draw();
}
