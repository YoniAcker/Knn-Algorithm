//
// Created by yonia on 21/01/2023.
//

#include "CLI.h"

/**
 * Constructor. Add all the commands to the array.
 @param dio the io system to use.
*/
CLI::CLI(DefaultIO *dio): update(dio), change(dio), classify(dio), display(dio), download(dio) {
    this->dio = dio;
    commands[0] = &update;
    commands[1] = &change;
    commands[2] = &classify;
    commands[3] = &display;
    commands[4] = &download;
}

/**
 * Print the menu af commands to the user.
*/
void CLI::printMenu() {
    int i;
    for(i = 1;i < 6;i++) {
        try {
            dio->write(to_string(i) + ". " + commands[i - 1]->getDescription());
        }
        catch (invalid_argument& ia) {
            throw invalid_argument("invalid input");
        }
    }
    try {
        dio->write("8. exit");
    }
    catch (invalid_argument& ia) {
        throw invalid_argument("invalid input");
    }
}

/**
 * Start the contact with the user.
*/
void CLI::start() {
    try {
        printMenu();
    }
    catch (invalid_argument& ia) {
        cout << "error sending message" << endl;
        start();
    }
    string line;
    try {
        line = dio->read();
    }
    catch (invalid_argument& ia) {
        cout << "error getting message" << endl;
        return;
    }
    int choice;
    try {
        choice = stoi(line);
    }
    catch (invalid_argument& ia) {
        try {
            dio->write("Invalid command");
        }
        catch (invalid_argument& ia) {
            cout << "error sending message" << endl;
            start();
        }
    }
    if (choice < 1 || choice > 8 || choice == 6 || choice == 7) {
        try {
            dio->write("Invalid command");
        }
        catch (invalid_argument& ia) {
            cout << "error sending message" << endl;
            start();
        }
    }
    while (choice != 8) {
        commands[choice - 1]->execute(algorithmKnn);
        try {
            printMenu();
        }
        catch (invalid_argument& ia) {
            cout << "error sending message" << endl;
            start();
        }
        choice = stoi(dio->read());
    }
}
