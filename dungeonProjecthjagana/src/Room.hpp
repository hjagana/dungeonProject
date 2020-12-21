#ifndef ROOM_H_
#define ROOM_H_

#include <string>
#include <vector>

#include "Structure.hpp"
#include "Creature.hpp"
#include "ObjectDisplayGrid.hpp"

class Room: public Structure{
    private:
        // int roomCount = 0;
        // std::vector<Room * > rooms;
        Creature * creature; 
        int roomId;

    public:
        Room(std::string room);

        virtual void setId(int room);
        virtual void setCreature(Creature *Monster);
        virtual Creature* getCreature();
        virtual int getId();
        virtual void Draw();
        // virtual void addRoom(Room *  room);
        // virtual void freeRooms();
        virtual bool checkMove(int x, int y);
};

#endif /* ROOM_H_ */