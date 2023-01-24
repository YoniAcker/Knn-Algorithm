//
// Created by yonia on 21/01/2023.
//

#ifndef EX4_CLI_H
#define EX4_CLI_H
#include "Command.h"
#include "AlgorithmKnn.h"
#include "Update.h"
#include "Change.h"
#include "Classify.h"
#include "Display.h"
#include "Download.h"

class CLI {
private:
    DefaultIO* dio;
    Command* commands[5];
    Update update;
    Change change;
    Classify classify;
    Display display;
    Download download;
    AlgorithmKnn algorithmKnn;
    void printMenu();
public:
    explicit CLI(DefaultIO* dio);
    void start();
};


#endif //EX4_CLI_H
