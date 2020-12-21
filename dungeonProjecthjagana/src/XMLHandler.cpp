#include "XMLHandler.hpp"

//From https://www.tutorialspoint.com/case-insensitive-string-comparison-in-cplusplus
int case_insensitive_match(std::string s1, std::string s2) {
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if(s1.compare(s2) == 0)
        return 1;
    return 0;
}

inline std::string boolToString(bool booleanValue){
    return booleanValue ? "true": "false";
}

XMLHandler::XMLHandler() {
}

std::string xmlChToString(const XMLCh* xmlChName, int length = -1){
    char * chStarName = xercesc::XMLString::transcode(xmlChName); 
    if(length == -1){
        std::string StrName(chStarName);
        xercesc::XMLString::release(&chStarName);
        return StrName;
    }
    else{
        std::string StrName(chStarName,0,length);
        xercesc::XMLString::release(&chStarName);
        return StrName;
    }
}

const XMLCh* getXMLChAttributeFromString(const xercesc::Attributes& attributes, const char * strGet){
    XMLCh * xmlChGet = xercesc::XMLString::transcode(strGet);
    const XMLCh * xmlChAttr = attributes.getValue(xmlChGet);
    xercesc::XMLString::release((&xmlChGet));
    return xmlChAttr;
}

Dungeon* XMLHandler::returnDungeon() {
    return dungeon;
}

void XMLHandler::startElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName, const xercesc::Attributes& attributes){

        char * qNameStr = xercesc::XMLString::transcode(qName);
        if (DEBUG > 1) {
            std::cout << CLASSID << ".startElement qName: " << qNameStr << std::endl;
        }

        if (case_insensitive_match(qNameStr,"Dungeon")) {
			std::string itemName = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            std::string dungeonWidth = xmlChToString(getXMLChAttributeFromString(attributes,"width"));
            int width = std::stoi(dungeonWidth);
            std::string topHeightString = xmlChToString(getXMLChAttributeFromString(attributes,"topHeight"));
            int topHeight = std::stoi(topHeightString);
            std::string gameHeightString = xmlChToString(getXMLChAttributeFromString(attributes,"gameHeight"));
            int gameHeight = std::stoi(gameHeightString);
            std::string bottomHeightString = xmlChToString(getXMLChAttributeFromString(attributes,"bottomHeight"));
            int bottomHeight = std::stoi(bottomHeightString);

            dungeon = Dungeon::getDungeon();

            dungeon->setwidth(width);
            dungeon->setTopHeight(topHeight);
            dungeon->setGameHeight(gameHeight);
            dungeon->setBottomHeight(bottomHeight);

        } else if (case_insensitive_match(qNameStr,"Rooms")) {

        }else if (case_insensitive_match(qNameStr,"Room")) {
            std::string roomCountString = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
            // int roomCount = std::stoi(roomCountString);
            Room * room;
            room = new Room(roomCountString);

            displaysVector.push_back(room);

            dungeon->addRoom((Room *) room);

        } else if (case_insensitive_match(qNameStr,"visible")) {
            bVisible = true;

        } else if (case_insensitive_match(qNameStr,"posX")) {
            bPosX = true;

        } else if (case_insensitive_match(qNameStr,"posY")) {
            bPosY = true;

        } else if (case_insensitive_match(qNameStr,"width")) {
            bWidth = true;

        } else if (case_insensitive_match(qNameStr,"height")) {
            bHeight = true;

        } else if (case_insensitive_match(qNameStr,"type")) {
            bType = true;

        } else if (case_insensitive_match(qNameStr,"Scroll")) {
			std::string scrollNameString = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            std::string roomCountString = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
            int roomCount = std::stoi(roomCountString);
            std::string serialString = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
            int serial = std::stoi(serialString);

            Scroll * scroll;
            scroll = new Scroll(scrollNameString);
            scroll->setId(roomCount, serial);
            scroll->setName("Scroll");
            scroll->setSpecialName(scrollNameString);

            displaysVector.push_back(scroll);

        } else if (case_insensitive_match(qNameStr,"ItemAction")) {
            std::string itemActionNameString = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            std::string itemActionTypeString = xmlChToString(getXMLChAttributeFromString(attributes,"type"));

            ItemAction *itemaction = nullptr;
            Item *item = dynamic_cast<Item*> (displaysVector.back());
            if(item){
                if (itemActionNameString == "BlessArmor"){
                    // BlessCurseOwner* blessOwner;
                    itemaction = new BlessCurseOwner(item);
                } else if (itemActionNameString == "Hallucinate"){
                    // Hallucinate* hallucinate;
                    itemaction = new Hallucinate(item);
                } else {
                    throw std::runtime_error("ERROR invalid item action name " + itemActionNameString);
                }
            }
            actionVector.push_back(itemaction);

        } else if (case_insensitive_match(qNameStr,"actionMessage")) {
            bActionMessage = true;

        } else if (case_insensitive_match(qNameStr,"actionIntValue")) {
            bActionIntValue = true;

        } else if (case_insensitive_match(qNameStr,"actionCharValue")) {
            bActionCharValue = true;

        } else if (case_insensitive_match(qNameStr,"Player")) {
            std::string playerNameString = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            std::string playerRoomString = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
            // int playerRoomNum = std::stoi(playerRoomString);
            std::string playerSerialString = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
            // int playerSerialNum = std::stoi(playerSerialString);

            Player *player;
            player = new Player();

            player->setName(playerNameString);

            displaysVector.push_back(player);
            dungeon->addPlayer(player);

        } else if (case_insensitive_match(qNameStr,"hp")) {
            bHp = true;

        } else if (case_insensitive_match(qNameStr,"hpMoves")) {
            bHpMoves = true;

        } else if (case_insensitive_match(qNameStr,"maxHit")) {
            bMaxHit = true;

        } else if (case_insensitive_match(qNameStr,"CreatureAction")) {
            std::string creatureActionName = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            std::string creatureActionType = xmlChToString(getXMLChAttributeFromString(attributes,"type"));
            
            // Creature * creature;
            // creature = new Creature;
            CreatureAction *creatureAction = nullptr;

            Creature * elementCreature = dynamic_cast<Creature*> (displaysVector.back());
            
            if (elementCreature) {
                if (creatureActionName == "ChangeDisplayedType") {
                    creatureAction = new ChangedDisplayType(creatureActionName, elementCreature);
                } else if (creatureActionName == "Remove") {
                    creatureAction = new Remove(creatureActionName, elementCreature);
                } else if (creatureActionName ==  "Teleport") {
                    creatureAction = new Teleport(creatureActionName, elementCreature);
                } else if (creatureActionName == "UpdateDisplay") {
                    creatureAction = new UpdateDisplay(creatureActionName, elementCreature);
                } else if (creatureActionName == "YouWin") {
                    creatureAction = new YouWin(creatureActionName, elementCreature);
                } else if (creatureActionName == "DropPack") {
                    creatureAction = new DropPack(creatureActionName, elementCreature);
                } else if (creatureActionName == "EndGame") {
                    creatureAction = new EndGame(creatureActionName, elementCreature);
                } else {
                    throw std::runtime_error("ERROR invalid creature action name " + creatureActionName);
                    //invalid creature action name
                }
                // else if (creatureActionName == "EmptyPack") {
                //     creatureAction = new EmptyPack(creatureActionName, creature);
                // } 

                if (creatureActionType == "death") {
                    elementCreature->addDeathAction(creatureAction);
                } else if (creatureActionType == "hit") {
                    elementCreature->addHitAction(creatureAction);
                }
            }
            actionVector.push_back(creatureAction);

        } else if (case_insensitive_match(qNameStr, "Sword")){
            std::string swordName = xmlChToString(getXMLChAttributeFromString(attributes, "name"));
            std::string swordRoom = xmlChToString(getXMLChAttributeFromString(attributes, "room"));
            int swordRoomNum = std::stoi(swordRoom);
            std::string swordSerial = xmlChToString(getXMLChAttributeFromString(attributes, "serial"));
            int swordSerialNum = std::stoi(swordSerial);

            Sword * sword;
            sword = new Sword(swordName);
            sword->setId(swordRoomNum, swordSerialNum);
            sword->setName("Sword");
            sword->setSpecialName(swordName);

            displaysVector.push_back(sword);

        } else if (case_insensitive_match(qNameStr,"ItemIntValue")) {
            bItemIntValue = true;

        } else if (case_insensitive_match(qNameStr,"Monster")) {
            std::string monsterNameString = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            std::string monsterRoomString = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
            int monsterRoomNum = std::stoi(monsterRoomString);
            std::string monsterSerialString = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
            int monsterSerialNum = std::stoi(monsterSerialString);

            Monster *monster;
            monster = new Monster();
            monster->setName(monsterNameString);
            monster->setId(monsterRoomNum, monsterSerialNum);

            displaysVector.push_back(monster);
            dungeon->addCreatue(monster);

        } else if (case_insensitive_match(qNameStr,"Armor")) {
            std::string armorNameString = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
            std::string armorRoomString = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
            int armorRoomNum = std::stoi(armorRoomString);
            std::string armorSerialString = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
            int armorSerialNum = std::stoi(armorSerialString);
            Armor *armor;
            armor = new Armor(armorNameString);
            armor->setName("Armor");
            armor->setId(armorRoomNum, armorSerialNum);
            armor->setSpecialName(armorNameString);

            displaysVector.push_back(armor);

        } else if(case_insensitive_match(qNameStr, "Passages")){

        } else if (case_insensitive_match(qNameStr,"Passage")) {
            std::string passageRoom1String = xmlChToString(getXMLChAttributeFromString(attributes,"room1"));
            int passageRoom1 = std::stoi(passageRoom1String);
            std::string passageRoom2String = xmlChToString(getXMLChAttributeFromString(attributes,"room2"));
            int passageRoom2 = std::stoi(passageRoom2String);
            
            Passage * passage;
            passage = new Passage();
            passage->setId(passageRoom1, passageRoom2);

            displaysVector.push_back(passage);
            dungeon->addPassage(passage);
        } else {
            std::cout <<"Unknown qname: " << qNameStr << std::endl;
        }
        xercesc::XMLString::release(&qNameStr);
}

void XMLHandler::endElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName)  {
    char * qNameStr = xercesc::XMLString::transcode(qName);

    if (bVisible) {
        Displayable *elementName = displaysVector.back();
        if (std::stoi(data) == 1){
            elementName->setVisible();
        }
        else{
            elementName->setInvisible();
        }
        bVisible = false;

    } else if (bPosX) {
        Displayable *elementName = displaysVector.back();
        elementName->setXPos(std::stoi(data));
        bPosX = false;

    } else if (bPosY) {
        Displayable *elementName = displaysVector.back();
        elementName->setYPos(std::stoi(data));
        bPosY = false;

    } else if (bWidth) {
        Displayable *elementName = displaysVector.back();
        elementName->setWidht(std::stoi(data));
        bWidth = false;

    } else if (bHeight) {
        Displayable *elementName = displaysVector.back();
        elementName->setHeight(std::stoi(data));
        bHeight = false;

    } else if (bType) {
        Displayable *elementName = displaysVector.back();
        elementName->setType(*data.c_str());
        bType = false;

    } else if (bActionMessage) {
        Action *action = actionVector.back();
        action->setMessage(data);
        bActionMessage = false;

    } else if (bActionIntValue) {
        Action *action = actionVector.back();
        action->setIntValue(std::stoi(data));
        bActionIntValue = false;

    } else if (bActionCharValue) {
        Action *action = actionVector.back();
        action->setCharValue(data[0]);
        bActionCharValue = false;

    } else if (bHp) {
        Displayable *elementName = displaysVector.back();
        elementName->setHp(std::stoi(data));
        bHp = false;

    } else if (bHpMoves) {
        Creature* c = dynamic_cast<Creature*>(displaysVector.back());
        if (c) {    
            c->setHpMoves(std::stoi(data));
        }
        bHpMoves = false;

    } else if (bMaxHit) {
        Displayable *elementName = displaysVector.back();
        elementName->setMaxHit(std::stoi(data));
        bMaxHit = false;

    } else if (bItemIntValue) {
        Displayable *elementName = displaysVector.back();
        elementName->setIntValue(std::stoi(data));
        bItemIntValue = false;
    }

    //check if stack is empty?? maybe if you want
    if (case_insensitive_match(qNameStr,"Room")){
        displaysVector.pop_back();

    } else if (case_insensitive_match(qNameStr, "Scroll")){
        Item* item = (Item*) displaysVector.back();
        ItemAction *itemaction = (ItemAction*) actionVector.back();
        if(itemaction){
            item->setItemAction(itemaction);
        }

        displaysVector.pop_back();

        Room * room = dynamic_cast<Room*> (displaysVector.back());
        if(room){
            item->setXPos(room->getXPos() + item->getXPos());
            item->setYPos(room->getYPos() + item->getYPos());
            item->setOwner(nullptr);
            dungeon->addItem(item);
        }
        else{
            Player * player = dynamic_cast<Player*> (displaysVector.back());
            if(player){
                player->addItemToPack(item);
                // item->setOwner(player);
                // player->setWeapon(item);
                dungeon->addItem(item);
            }
        }
        actionVector.pop_back();

        
    } else if (case_insensitive_match(qNameStr, "ItemAction")){
        // ItemAction *elementName = dynamic_cast<ItemAction*> (actionVector.back());
        // if(elementName){
        //     elementName->setMessage(data);
        //     Item * itemCreature = dynamic_cast<Item*> (displaysVector.back());
        //     if(itemCreature){
        //         itemCreature.setItem
        //     }
        // }
        // actionVector.pop_back();

    } else if (case_insensitive_match(qNameStr, "Player")){
        Player* player = (Player*) displaysVector.back();

        displaysVector.pop_back();
        Room * room = (Room*) displaysVector.back();
        room->setCreature(player);
        player->setXPos(room->getXPos() + player->getXPos());
        player->setYPos(room->getYPos() + player->getYPos());

    } else if (case_insensitive_match(qNameStr, "CreatureAction")){
        actionVector.pop_back();

    } else if (case_insensitive_match(qNameStr, "Sword")){
        Item* item = (Item*) displaysVector.back();
        ItemAction *itemaction = (ItemAction*) actionVector.back();
        if(itemaction){
            item->setItemAction(itemaction);
        }

        displaysVector.pop_back();

        Room * room = dynamic_cast<Room*> (displaysVector.back());
        if(room){
            item->setXPos(room->getXPos() + item->getXPos());
            item->setYPos(room->getYPos() + item->getYPos());
            item->setOwner(nullptr);
            dungeon->addItem(item);
        }
        else{
            Player * player = dynamic_cast<Player*> (displaysVector.back());
            if(player){
                // item->setOwner(player);
                // player->setWeapon(item);
                // player->addItemToPack(item);
                item->setOwner(player);
                // item->setOwner(player);
                // player->setArmor(item);
                player->addItemToPack(item);
                dungeon->addItem(item);
            }
        }

    } else if (case_insensitive_match(qNameStr, "Monster")){
        Monster* monster = (Monster*) displaysVector.back();

        displaysVector.pop_back();
        Room * room = (Room*) displaysVector.back();
        room->setCreature(monster);
        monster->setXPos(room->getXPos() + monster->getXPos());
        monster->setYPos(room->getYPos() + monster->getYPos());

    } else if (case_insensitive_match(qNameStr, "Armor")){
        Item* item = (Item*) displaysVector.back();
        ItemAction *itemaction = (ItemAction*) actionVector.back();
        if(itemaction){
            item->setItemAction(itemaction);
        }

        displaysVector.pop_back();

        Room * room = dynamic_cast<Room*> (displaysVector.back());
        if(room){
            item->setXPos(room->getXPos() + item->getXPos());
            item->setYPos(room->getYPos() + item->getYPos());
            item->setOwner(nullptr);
            dungeon->addItem(item);
        }
        else{
            Player * player = dynamic_cast<Player*> (displaysVector.back());
            if(player){
                item->setOwner(player);
                // item->setOwner(player);
                // player->setArmor(item);
                player->addItemToPack(item);
                dungeon->addItem(item);
            }
        }
    } else if (case_insensitive_match(qNameStr, "Passage")){
        displaysVector.pop_back();
    }
    xercesc::XMLString::release(&qNameStr);
}

void XMLHandler::characters(const XMLCh * const ch, const XMLSize_t length) {
        data = xmlChToString(ch,(int)length) ;   
        if (DEBUG > 1) {
			std::cout << CLASSID + ".characters: " << data << std::endl;
            std::cout.flush();
        }
}

void XMLHandler::fatalError(const xercesc::SAXParseException& exception)
{
    char* message = xercesc::XMLString::transcode(exception.getMessage());
    std::cout << "Fatal Error: " << message
         << " at line: " << exception.getLineNumber()
         << std::endl;
    xercesc::XMLString::release(&message);
}
