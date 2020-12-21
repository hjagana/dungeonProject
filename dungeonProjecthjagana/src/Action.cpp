#include "Action.hpp"

#include <string>
#include <iostream>

Action::Action(){
}

void Action::setMessage(std::string msg){
    message = msg;
}
std::string Action::getMessage(){
    return message;
}

void Action::setIntValue(int v){
    intVal = v;
}

int Action::getInt() {
    return intVal;
}

void Action::setCharValue(char c){
    charVal = c;
}

char Action::getChar() {
    return charVal;
}

void Action::performAction() {
}