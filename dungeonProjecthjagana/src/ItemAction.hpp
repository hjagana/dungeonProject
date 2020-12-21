#ifndef ITEMACTION_H_
#define ITEMACTION_H_

#include <string>
#include <vector>

// #include "Creature.hpp"
#include "Action.hpp"

class Item;
class ItemAction: public Action{
    private:

    public:
        ItemAction(Item *owner);
        virtual void performAction();
};

#endif /* ITEMACTION_H_ */