#ifndef CREATURE_H_
#define CREATURE_H_

#include <string>
#include <vector>

#include "Displayable.hpp"
#include "CreatureAction.hpp"
#include "ObjectDisplayGrid.hpp"

class Creature: public Displayable{
    private:
        // ObjectDisplayGrid * grid;
        // std::string deathActionMessage;
        // std::string hitActionMessage;
        int hpMoves;
        // int hpMovesCounter;
        int scoreVal = 0;

    public:
        Creature();
        virtual void setHpMoves(int hpm);
        virtual void addDeathAction(CreatureAction *da);
        virtual void addHitAction(CreatureAction *ha);
        virtual void Draw();
        virtual void runDeathAction();
        virtual void runHitAction();
        virtual void setScoreVal(int s);
        virtual int getScoreVal();
        virtual int getHpMoves();
        virtual int getDeathActionVectorSize();

        std::vector<CreatureAction*> deathActionsVector;
        std::vector<CreatureAction*> hitActionsVector;
        
};

#endif /* STRUCTURE_H_ */