//
// Created by yonia on 21/01/2023.
//

#include "Change.h"
#include "cstring"

Change::Change(DefaultIO *dio): Command(dio) {
    description = "algorithm settings";
}

void Change::execute(AlgorithmKnn& algorithmKnn) {
    string line;
    line = "The current KNN parameters are: K = ";
    line += to_string(algorithmKnn.getK());
    line += ", distance metric = ";
    line += algorithmKnn.getDistanceFunc();
    dio->write(line);
    line = dio->read();
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
            dio->write("invalid value for K");
            isValid = false;
        }
        part = strtok(nullptr, "\n");
        if (strcmp(part, "AUC") && strcmp(part, "MAN") && strcmp(part, "CHB") &&
                strcmp(part, "CAN") && strcmp(part, "MIN")) {
            dio->write("invalid value for metric");
            isValid = false;
        }
        if (isValid) {
            distanceFunc = part;
            algorithmKnn.setK(k);
            algorithmKnn.setDistanceFunc(distanceFunc);
        }
    }
}