#pragma once
#include "ObjectDisplayGrid.hpp"
#include "Player.hpp"
#include "Dungeon.hpp"

class KeyboardListener {
private:
    /** Object display grid reference to write errors */
    ObjectDisplayGrid* grid;
    Player *player;
    Dungeon *dungeon;

    /** set to false to stop running the keyboard listener */
    bool running = false;
    // bool endGame = false;

public:
    /**
     * Creates a new keyboard listener, you can pass in extra objects here to interact with them during the game if you wish
     * @param grid  Object display grid reference
     */
    KeyboardListener(ObjectDisplayGrid* grid, Player *player, Dungeon *dungeon);

    /**
     * Runs the keyboard listener in a thread
     */
    void run();
    // int getCount();
    // void setEndGameBool();
};

