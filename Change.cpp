//
// Created by yonia on 21/01/2023.
//

#include "Change.h"
#include "cstring"

/**
 * Constructor.
 @param dio the io system to use.
*/
Change::Change(DefaultIO *dio): Command(dio) {
    description = "algorithm settings";
}

/**
 * Execute the command on the given algorithm.
 @param algorithmKnn the algorithm.
*/
void Change::execute(AlgorithmKnn& algorithmKnn) {
    string line;
    line = "The current KNN parameters are: K = ";
    line += to_string(algorithmKnn.getK());
    line += ", distance metric = ";
    line += algorithmKnn.getDistanceFunc();
    try {
        dio->write(line);
    }
    catch (invalid_argument& ia) {
        cout << "error sending message" << endl;
        return;
    }
    try {
        line = dio->read();
    }
    catch (invalid_argument& ia) {
        cout << "error getting message" << endl;
        return;
    }
    if (!line.empty()) {
        int k;
        string distanceFunc;
        char charLine[line.size()];
        strcpy(charLine, line.data());
        bool isValid = true;
        char* part = strtok(charLine, " ");
        try {
            k = stoi(part);
        }
        catch (invalid_argument& ia) {
            try {
                dio->write("invalid value for K");
            }
            catch (invalid_argument& ia) {
                cout << "error sending message" << endl;
                return;
            }
            isValid = false;
        }
        part = strtok(nullptr, "\n");
        if (strcmp(part, "AUC") && strcmp(part, "MAN") && strcmp(part, "CHB") &&
                strcmp(part, "CAN") && strcmp(part, "MIN")) {
            try {
                dio->write("invalid value for metric");
            }
            catch (invalid_argument& ia) {
                cout << "error sending message" << endl;
                return;
            }
            isValid = false;
        }
        if (isValid) {
            distanceFunc = part;
            algorithmKnn.setK(k);
            algorithmKnn.setDistanceFunc(distanceFunc);
        }
    }
}