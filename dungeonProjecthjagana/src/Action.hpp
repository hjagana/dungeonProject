#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <vector>


class Action{
    private:

    public:
        Action();
        virtual void setMessage(std::string msg);
        virtual std::string getMessage();
        virtual void setIntValue(int v);
        virtual int getInt();
        virtual void setCharValue(char c);
        virtual char getChar();

        // CreatureAction and ItemAction will override performAction() kind of like draw() in Dungeon
        virtual void performAction(); 

        std::string message;
        char charVal;
        int intVal;
};

#endif /* ACTION_H_ */