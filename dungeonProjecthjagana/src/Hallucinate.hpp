#ifndef HALLUCINATE_H_
#define HALLUCINATE_H_

#include <string>
#include <vector>

#include "ItemAction.hpp"

class Item;
class Hallucinate: public ItemAction{
    private:

    public:
        Hallucinate(Item* owner);
        virtual void performHallucinate(int hallucinateCount);
};

#endif /* HALLUCINATE_H_ */