#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "XMLHandler.hpp"

#include <iostream>
#include <string>
#include <exception>
#include <atomic> 
#include <thread>
#include <sstream>

#include "ObjectDisplayGrid.hpp"
#include "GridChar.hpp"
#include "KeyboardListener.hpp"

// set to false when done running
std::atomic_bool isRunning(true);

// grid properties
// int WIDTH = 150;
// int HEIGHT = 50;
int MESSAGES = 5;

void runDisplay(ObjectDisplayGrid* grid, Dungeon *dungeonGrid) {
    dungeonGrid->Draw();
}

int main(int argc, char* argv[]) {
    std::string fileName;
    try{
        xercesc::XMLPlatformUtils::Initialize();
    }
    catch (const xercesc::XMLException& toCatch) {
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cout << "Error during initialization! :\n";
        std::cout << "Exception message is: \n"
             << message << "\n";
        xercesc::XMLString::release(&message);
        return 1;
    }
    // std::string filenames[7] = {"badScroll.xml", "death.xml", "dropPack.xml", "dungeon.xml", "hallucinate.xml", "testDrawing.xml", "wear.xml"};
    // fileName = "../xmlFiles/" + filenames[4];
    fileName = argv[1];
    xercesc::SAX2XMLReader* parser = xercesc::XMLReaderFactory::createXMLReader();
    Dungeon* dungeon;
    try {
        XMLHandler* handler = new XMLHandler();
        parser->setContentHandler(handler);
        parser->setErrorHandler(handler);
        parser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
        parser->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);
        XMLCh * fileNameXMLEnc = xercesc::XMLString::transcode(fileName.c_str()); //Encode string as UTF-16, but transcode needs casting as const char * (not std::string)
        parser->parse(fileNameXMLEnc);
        xercesc::XMLString::release(&fileNameXMLEnc);
        dungeon = handler->returnDungeon();
        delete parser;
        delete handler;
    } catch (const xercesc::XMLException& toCatch) {
            char* message = xercesc::XMLString::transcode(toCatch.getMessage());
            std::cout << "Exception message is: \n"
                << message << "\n";
            xercesc::XMLString::release(&message);
            return -1;
    }
    catch (const xercesc::SAXParseException& toCatch) {
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
            << message << "\n";
        xercesc::XMLString::release(&message);
        return -1;
    }
    catch(std::exception& e){
        std::cout << e.what() << '\n';
    }
    catch(...){
        std::cout << "Unexpected Exception \n" ;
        return -1;
    }
    
    xercesc::XMLPlatformUtils::Terminate();


    int width = dungeon->getwidth();
    int height = dungeon->getGameHeight();// + dungeon->getBottomHeight() + dungeon->getTopHeight();
    ObjectDisplayGrid* pGrid = ObjectDisplayGrid::getGrid(width, height, MESSAGES);
    pGrid->setTopMessageHeight(dungeon->getTopHeight());
    Player *player = dungeon->getPlayer();
    // thread to wait for key press
    KeyboardListener listener(pGrid, player, dungeon);
    std::thread keyboardThread(&KeyboardListener::run, &listener);

    // thread to update display
    std::thread displayThread(runDisplay, pGrid, dungeon);

    // wait for the keyboard thread to finish, then notify the display to stop
    keyboardThread.join();
    isRunning = false;

    // wait for the display thread to finish
    displayThread.join();

    delete(pGrid);
    // delete(dungeon);
    //delete dungeon and other things

	return 0;
}