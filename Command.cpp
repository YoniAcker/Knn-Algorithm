//
// Created by yonia on 21/01/2023.
//
#include "Command.h"

Command::Command(DefaultIO* dio) {
    this->dio = dio;
}

string Command::getDescription() {
    return description;
}

