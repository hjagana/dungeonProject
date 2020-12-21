#ifndef XMLHANDLER_H_
#define XMLHANDLER_H_

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/Attributes.hpp>

#include "Room.hpp"
#include "Scroll.hpp"
#include"Dungeon.hpp"
#include "Player.hpp"
#include "Sword.hpp"
#include "Creature.hpp"
#include "CreatureAction.hpp"
#include "Displayable.hpp"
#include "Hallucinate.hpp"
#include "Item.hpp"
#include "ItemAction.hpp"
#include "Magic.hpp"
#include "Monster.hpp"
#include "ObjectDisplayGrid.hpp"
#include "Passage.hpp"
#include "Structure.hpp"
#include "BlessCurseOwner.hpp"
#include "Action.hpp"
#include "Armor.hpp"
#include "ChangedDisplayType.hpp"
#include "Remove.hpp"
#include "Teleport.hpp"
#include "UpdateDisplay.hpp"
#include "YouWin.hpp"
#include "DropPack.hpp"
// #include "EmptyPack.hpp"
#include "EndGame.hpp"

class XMLHandler : public xercesc::DefaultHandler{
private:
    int DEBUG = 1;
    std::string data ;
    std::string CLASSID = "badScrollXMLHandler";
    std::vector<Displayable *> displaysVector;
    std::vector<Action *> actionVector;

    Dungeon *dungeon;
    bool bVisible = false;
    bool bPosX = false;
    bool bPosY = false;
    bool bWidth = false;
    bool bHeight = false;
    bool bType = false;
    bool bActionMessage = false;
    bool bActionIntValue = false;
    bool bActionCharValue = false;
    bool bHp = false;
    bool bHpMoves = false;
    bool bMaxHit = false;
    bool bItemIntValue = false;

public:
    XMLHandler();
    void startElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName, const xercesc::Attributes& attributes);
    void endElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName);
    void fatalError(const xercesc::SAXParseException&);
    void characters(const XMLCh * const ch, const XMLSize_t length );
    Dungeon* returnDungeon();
    // void addDisplay(Dungeon *dungeon);
    // std::string toString();
};

#endif /* XMLHANDLER_H_ */