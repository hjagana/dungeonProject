#ifndef UPDATEDISPLAY_H_
#define UPDATEDISPLAY_H_

#include <string>
#include <vector>

#include "CreatureAction.hpp"
#include "ObjectDisplayGrid.hpp"

class Creature;
class UpdateDisplay: public CreatureAction{
    private:

    public:
        UpdateDisplay(std::string name, Creature *owner);
        virtual void performAction();
        // Creature *c; //= new Creature();
};

#endif /* UPDATEDISPLAY_H_ */