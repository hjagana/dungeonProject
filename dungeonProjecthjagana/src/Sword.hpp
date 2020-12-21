#ifndef SWORD_H_
#define SWORD_H_

#include <string>
#include <vector>

#include "Item.hpp"

class Sword: public Item{
    private:
    std::string itemName;
    std::string scrollName;

    public:
        Sword(std::string name);
        virtual void setName(std::string _itemName);
        virtual std::string getName();
        virtual void setId(int room, int serial);
        virtual void Draw();
};

#endif /* SWORD_H_ */