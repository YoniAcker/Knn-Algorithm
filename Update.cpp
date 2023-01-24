//
// Created by yonia on 21/01/2023.
//

#include "Update.h"

Update::Update(DefaultIO *dio): Command(dio) {
    description = "upload an unclassified csv data file";
}

void Update::execute(AlgorithmKnn &algorithmKnn) {
    if (!algorithmKnn.getTrain()->getNeighbors().empty()) {
        algorithmKnn.getTrain()->deleteDB();
        algorithmKnn.getTest()->deleteDB();
    }
    string line = dio->read();
    while (line != "Upload complete.") {
        try {
            algorithmKnn.getTrain()->addLine(line, false);
        }
        catch (invalid_argument& ia) {
            dio->write("invalid file");
            return;
        }
        line = dio->read();
    }
    dio->write(line);
    line = dio->read();
    while (line != "Upload complete.") {
        try {
            algorithmKnn.getTest()->addLine(line, true);
        }
        catch (invalid_argument& ia) {
            dio->write("invalid file");
            return;
        }
        line = dio->read();
    }
    dio->write(line);
}