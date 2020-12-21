#ifndef ENDGAME_H_
#define ENDGAME_H_

#include <string>
#include <vector>

#include "CreatureAction.hpp"
#include "ObjectDisplayGrid.hpp"
#include "KeyboardListener.hpp"

class Creature;
class EndGame: public CreatureAction{
    private:

    public:
        EndGame(std::string name, Creature *owner);
        virtual void performAction();
        // Creature *c = NULL;
        KeyboardListener *k = NULL;
};

#endif /* ENDGAME_H_ */