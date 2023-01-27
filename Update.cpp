//
// Created by yonia on 21/01/2023.
//

#include "Update.h"

/**
 * Constructor.
 @param dio the io system to use.
*/
Update::Update(DefaultIO *dio): Command(dio) {
    description = "upload an unclassified csv data file";
}

/**
 * Execute the command on the given algorithm.
 @param algorithmKnn the algorithm.
*/
void Update::execute(AlgorithmKnn &algorithmKnn) {
    if (!algorithmKnn.getTrain()->getNeighbors().empty()) {
        algorithmKnn.getTrain()->deleteDB();
        algorithmKnn.getTest()->deleteDB();
    }
    try {
        dio->write("Please upload your local train CSV file.");
    }
    catch (invalid_argument& ia) {
        cout << "error sending message" << endl;
        return;
    }
    try {
        if(dio->read() == "start") {
            return;
        }
    }
    catch (invalid_argument& ia) {
        cout << "error getting message" << endl;
    }
    string line;
    try {
        line = dio->read();
    }
    catch (invalid_argument& ia) {
        cout << "error getting message" << endl;
        return;
    }
    while (line != "Upload complete.") {
        try {
            algorithmKnn.getTrain()->addLine(line, true);
        }
        catch (invalid_argument& ia) {
            try {
                dio->write("invalid file");
            }
            catch (invalid_argument& ia) {
                cout << "error sending message" << endl;
            }
            return;
        }
        try {
            dio->write("V");
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
    }
    try {
        dio->write(line);
    }
    catch (invalid_argument& ia) {
        cout << "error sending message" << endl;
    }
    try {
        dio->write("Please upload your local test CSV file.");
    }
    catch (invalid_argument& ia) {
        cout << "error sending message" << endl;
        return;
    }
    if (dio->read() == "start") {
        return;
    }
    try {
        line = dio->read();
    }
    catch (invalid_argument& ia) {
        cout << "error getting message" << endl;
        return;
    }
    while (line != "Upload complete.") {
        try {
            algorithmKnn.getTest()->addLine(line, false);
        }
        catch (invalid_argument& ia) {
            try {
                dio->write("invalid file");
            }
            catch (invalid_argument& ia) {
                cout << "error sending message" << endl;
            }
            return;
        }
        try {
            dio->write("V");
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
    }
    try {
        dio->write(line);
    }
    catch (invalid_argument& ia) {
        cout << "error sending message" << endl;
    }
}