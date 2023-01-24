//
// Created by yonia on 21/01/2023.
//
#include "Command.h"

/**
 * Constructor.
 @param dio the io system to use.
*/
Command::Command(DefaultIO* dio) {
    this->dio = dio;
}

/**
 @return the description of the command.
*/
string Command::getDescription() {
    return description;
}

