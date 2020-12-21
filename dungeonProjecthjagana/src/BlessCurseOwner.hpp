#ifndef BLESSCURSEOWNER_H_
#define BLESSCURSEOWNER_H_

#include <string>
#include <vector>

#include "ItemAction.hpp"

class Item;
class BlessCurseOwner: public ItemAction{
    private:

    public:
        BlessCurseOwner(Item *owner);
        
};

#endif /* BLESSCURSEOWNER_H_ */