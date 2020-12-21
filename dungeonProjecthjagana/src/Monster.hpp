#ifndef MONSTER_H_
#define MONSTER_H_

#include <string>
#include <vector>

#include "Creature.hpp"
#include "ObjectDisplayGrid.hpp"

class Monster: public Creature{
    private:
    std::string nameId;

    public:
        Monster();
        virtual void setName(std::string name);
        virtual void setId(int room, int serial);   
        virtual std::string getName();  
        virtual void Draw();  
        virtual bool checkCollision(int x, int y);
};

#endif /* MONSTER_H_ */