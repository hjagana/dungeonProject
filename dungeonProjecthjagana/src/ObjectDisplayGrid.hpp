#ifndef OBJECTDISPLAYGRID_H_
#define OBJECTDISPLAYGRID_H_

#include <string>
#include <vector>
#include "GridChar.hpp"
#include "Displayable.hpp"

class ObjectDisplayGrid{
    private:
    int height, width;
    int messages;
    int topMessageHeight;
    // Dungeon * dungeonGrid;
    // ObjectDisplayGrid *grid;
    // static GridChar*** objectGrid;
    // Displayable *display;


    // GridChar*** objectGrid;
    
    
    // std::vector <Displayable > ** gridStack; //displayable would add to get a character
    //2 D array of vectors
    
    // int displayCount = 0;
    // std::vector<ObjectDisplayGrid * > displays; 

    public:
        
        // ObjectDisplayGrid(); 
        std::vector <GridChar > ** gridStack; //displayable
        static ObjectDisplayGrid* objGrid;
        static ObjectDisplayGrid* getGrid(int _width, int _height, int _messages);
        static ObjectDisplayGrid* getGrid();
        ObjectDisplayGrid(int _width, int _height, int _messages);
        // ObjectDisplayGrid(int width, int height, int messages);
        virtual ~ObjectDisplayGrid();
        virtual void update();
        virtual void addObjectToDisplay(GridChar* ch, int x, int y);
        virtual void writeLine(int line, std::string message);
        virtual void writeTopLine(int line, std::string message);
        // virtual void writeBotLine(int line, std::string message);

        virtual void getObjectDisplayGrid(int gameHeight, int width, int topHeight);
        virtual void setTopMessageHeight(int topHeight);

        virtual void removeFromVector(int x, int y);
        // virtual void runDisplay(Dungeon *dungeonGrid); 
        // virtual void addDisplay(ObjectDisplayGrid *  display);
        // virtual void freeDisplays();
};

#endif /* OBJECTDISPLAYGRID_H_ */