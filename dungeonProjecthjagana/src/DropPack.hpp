#ifndef DROPPACK_H_
#define DROPPACK_H_

#include <string>
#include <vector>

#include "CreatureAction.hpp"
#include "ObjectDisplayGrid.hpp"
#include "Dungeon.hpp"
#include "KeyboardListener.hpp"

class DropPack: public CreatureAction{
    private:

    public:
        DropPack(std::string name, Creature *owner);
        virtual void performAction();
        // Dungeon* d = NULL;
        KeyboardListener * k = NULL;
};

#endif /* DROPPACK_H_ */