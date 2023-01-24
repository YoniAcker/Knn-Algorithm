//
// Created by yonia on 21/01/2023.
//

#include "CLI.h"

CLI::CLI(DefaultIO *dio): update(dio), change(dio), classify(dio), display(dio), download(dio) {
    this->dio = dio;
    commands[0] = &update;
    commands[1] = &change;
    commands[2] = &classify;
    commands[3] = &display;
    commands[4] = &download;
}

void CLI::printMenu() {
    int i;
    for(i = 1;i < 6;i++) {
        dio->write(to_string(i) + ". " + commands[i - 1]->getDescription());
    }
    dio->write("8. exit");
}

void CLI::start() {
    printMenu();
    int choice = stoi(dio->read());
    while (choice != 8) {
        commands[choice - 1]->execute(algorithmKnn);
        printMenu();
        choice = stoi(dio->read());
    }
}
