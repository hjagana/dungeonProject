#ifndef REMOVE_H_
#define REMOVE_H_

#include <string>
#include <vector>

#include "CreatureAction.hpp"
#include "ObjectDisplayGrid.hpp"

class Creature;
class Remove: public CreatureAction{
    private:

    public:
        Remove(std::string name, Creature *owner);
        virtual void performAction();
        // Creature *c;
};

#endif /* REMOVE_H_ */