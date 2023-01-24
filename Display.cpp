//
// Created by yonia on 21/01/2023.
//

#include "Display.h"

/**
 * Constructor.
 @param dio the io system to use.
*/
Display::Display(DefaultIO *dio): Command(dio) {
    description = "display results";
}

/**
 * Execute the command on the given algorithm.
 @param algorithmKnn the algorithm.
*/
void Display::execute(AlgorithmKnn& algorithmKnn) {
    if (algorithmKnn.getTest()->getNeighbors().empty()) {
        try {
            dio->write("please upload data");
        }
        catch (invalid_argument& ia) {
            cout << "error sending message" << endl;
        }
        return;
    }
    if (algorithmKnn.getTest()->getNeighbors().front()->getTypeName().empty()) {
        try {
            dio->write("please classify the data");
        }
        catch (invalid_argument& ia) {
            cout << "error sending message" << endl;
        }
        return;
    }
    int i = 1;
    for (auto& itr : algorithmKnn.getTest()->getNeighbors()) {
        string line = to_string(i);
        line += "   ";
        line += itr->getTypeName();
        try {
            dio->write(line);
        }
        catch (invalid_argument& ia) {
            cout << "error sending message" << endl;
            return;
        }
    }
    try {
        dio->write("Done.");
    }
    catch (invalid_argument& ia) {
        cout << "error sending message" << endl;
    }
}