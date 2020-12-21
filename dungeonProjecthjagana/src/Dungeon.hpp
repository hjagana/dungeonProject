#ifndef DUNGEON_H_
#define DUNGEON_H_

#include <string>
#include <vector>

#include "Room.hpp"
#include "Monster.hpp"
#include "Item.hpp"
#include "Passage.hpp"
#include "Player.hpp"
#include "Armor.hpp"
#include "Scroll.hpp"
#include "Sword.hpp"

class Dungeon{
    private:
        Dungeon();
        static Dungeon * dungeonCreated;
        std::vector<Room * > rooms; 
        std::vector<Monster * > creatures; 
        std::vector<Passage * > passages; 
        std::vector<Item * > items;
        std::vector<Item *> itemAtSameSpot;

        Player *player;


        int width;
        int topHeight;
        int gameHeight;
        int bottomHeight;
        int itemCountK;


    public:
        virtual void addRoom(Room *room);
        virtual void addCreatue(Monster *creature);
        virtual void addPassage(Passage *passage);
        virtual void addPlayer(Player *_player);
        virtual void addItem(Item *item);

        static Dungeon* getDungeon();
        virtual std::vector<Room *> getRooms();
        virtual std::vector<Monster *> getCreatures();
        virtual std::vector<Passage *> getPassages();
        virtual std::vector<Item *> getItems();
        virtual Player* getPlayer();

        virtual void Draw();

        virtual void setItemCount(int x);
        virtual int getItemCount();

        virtual void setwidth(int _width);
        virtual int getwidth();
        virtual void setTopHeight(int _topheight);
        virtual int getTopHeight();
        virtual void setGameHeight(int _gameHeight);
        virtual int getGameHeight();
        virtual void setBottomHeight(int _bottomHeight);
        virtual int getBottomHeight();

        virtual bool checkMove(int x, int y);
        virtual bool checkCollision(int x, int y);
        virtual bool addItemToPack(int x, int y);
        virtual bool dropItemFromPack(int itemNum, int count);

        virtual void displayItemsInPack();

        virtual bool checkArmor();
        virtual bool checkArmorInPack(int armorNum);
        virtual bool checkScrollInPack(int scrollNum);
        virtual int performAction(int scrollNum, bool hallucinate, bool blessCurse);
        virtual bool checkSwordInPack(int swordNum);
        virtual void swapSword(int swordNum);
        virtual void hallucinate();
        virtual void drawNormal();
        virtual bool blessCurse(int scrullNum);
};

#endif /* DUNGEON_H_ */