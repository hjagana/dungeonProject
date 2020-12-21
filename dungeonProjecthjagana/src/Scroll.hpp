#ifndef SCROLL_H_
#define SCROLL_H_

#include <string>
#include <vector>

#include "Item.hpp"

class Scroll: public Item{
    private:
    std::string itemName;
    std::string scrollName;

    public:
        Scroll(std::string name);
        virtual void setName(std::string _itemName);
        virtual std::string getName();
        virtual void setId(int room, int serial);
        virtual void Draw();
};

#endif /* SCROLL_H_ */