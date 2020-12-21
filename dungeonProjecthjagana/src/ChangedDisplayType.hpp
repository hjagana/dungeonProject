#ifndef CHANGEDDISPLAYTYPE_H_
#define CHANGEDDISPLAYTYPE_H_

#include <string>
#include <vector>

#include "CreatureAction.hpp"
#include "ObjectDisplayGrid.hpp"

class Creature;
class ChangedDisplayType: public CreatureAction{
    private:

    public:
        ChangedDisplayType(std::string name, Creature *owner);

        virtual void performAction();
        // Creature *c;
};

#endif /* CHANGEDDISPLAYTYPE_H_ */