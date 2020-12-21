#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <vector>

#include "Creature.hpp"
#include "ObjectDisplayGrid.hpp"


class Item;
class Player: public Creature{
    private:
        std::string name;
        // Item * creatureSword;
        Item *creatureArmor = NULL;
        Item *weapon = NULL;
        std::vector<Item * > itemsPack;
        int count;

    public:
        Player();
        virtual void setWeapon(Item* sword);
        virtual Item* getWeapon();
        virtual void setArmor(Item* armor);
        virtual Item* getArmor();  
        virtual void setName(std::string _name);
        virtual std::string getName();   
        virtual void Draw(); 
        virtual void movePlayerLeft();
        virtual void movePlayerRight();
        virtual void movePlayerUp();
        virtual void movePlayerDown();
        virtual void addItemToPack(Item *item);
        virtual void removeItemFromPack(int itemNum);
        virtual std::vector<Item *> getItemPack();
        virtual void updateHPmovesCounter();
        virtual int getHPmovesCounter();
        virtual void updateHallucinateCounter();
        virtual int getHallucinateValue();
        virtual void setHallucinateMaxCount(int _count);
        virtual int getHallucinateMaxCount();
        virtual void endGameBoolCheck();
        int hpMovesCounter = 0;
        int hallucinateCounter = 0;
        bool endGameBool = false;
        // int startHP = 0;
};

#endif /* PLAYER_H_ */