#ifndef ARMOR_H_
#define ARMOR_H_

#include <string>
#include <vector>

#include "Item.hpp"

class Armor: public Item{
    private:
    std::string itemName;
    std::string armorName;

    public:
        Armor(std::string name);
        virtual void setName(std::string _itemName);
        virtual std::string getName();
        virtual void setId(int room, int serial);
        virtual void Draw();
};

#endif /* ARMOR_H_ */