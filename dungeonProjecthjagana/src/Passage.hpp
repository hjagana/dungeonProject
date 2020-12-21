#ifndef PASSAGE_H_
#define PASSAGE_H_

#include <string>
#include <vector>

#include "Structure.hpp"
#include "ObjectDisplayGrid.hpp"

class Passage: public Structure{
    private:
        // int passageCount = 0;
	    

    public:
        std::vector<int > xx; 
        std::vector<int > yy; 
        Passage();
        virtual void setName(std::string name);
        virtual void setId(int room1, int room2);
        virtual void Draw();

        virtual void setXPos(int x);
        virtual void setYPos(int y);
        virtual bool checkMove(int x, int y);

        // void addPassage(Passage *  passage);
        // void freePassages();

};

#endif /* PASSAGE_H_ */