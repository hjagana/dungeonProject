#ifndef CREATUREACTION_H_
#define CREATUREACTION_H_

#include <string>
#include <vector>

#include "Action.hpp"

// #include "Creature.hpp"

class Creature;
class CreatureAction: public Action{
    private:

    public:
        CreatureAction(Creature *owner);
        virtual void performAction();
    protected:
        Creature* c = NULL;
};

#endif /* CREATUREACTION_H_ */