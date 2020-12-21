#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <vector>

#include "Displayable.hpp"
#include "ObjectDisplayGrid.hpp"

class Creature;
class ItemAction;
class Item: public Displayable{
    private:
        int count = 0;
        ItemAction *action;
        // char randomItemChars [10] = {'#', '.', '+', 'X', ']', '?', ')' , 'T', 'H', 'S'};
        
    public:
        Item();
        virtual void setOwner(Creature* _owner);
        // virtual void Draw();
        
        virtual Creature* getOwner();
        virtual void setCount(int _count);
        virtual int getCount();
        // virtual void performHallucinate();
        virtual void setItemAction(ItemAction * ia);
        virtual ItemAction* getItemAction();
        // virtual int draw();
        // virtual char getRandomCharacter(int i);
        // virtual int getRandNum();
    protected:
        Creature * owner;
        
};

#endif /* ITEM_H_ */