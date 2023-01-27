//
// Created by yonia on 21/01/2023.
//

#include "CLI.h"
#include <thread>
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
    string menu;
    int i;
    for(i = 1;i < 6;i++) {
        menu += to_string(i) + ". " + commands[i - 1]->getDescription() + "\n";
    }
    menu += "8. exit";
    try {
        dio->write(menu);
    }
    catch (invalid_argument& ia) {
        cout << "error sending message" << endl;
        start();
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
    // if choise == 8 so need to exit
    while (choice != 8) {
        if (choice < 1 || choice > 8 || choice == 6 || choice == 7) {
            try {
                dio->write("Invalid command");
                start();
            }
            catch (invalid_argument& ia) {
                cout << "error sending message" << endl;
                start();
            }
        }

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
