//
// Created by yonia on 21/01/2023.
//

#include "Classify.h"

/**
 * Constructor.
 @param dio the io system to use.
*/
Classify::Classify(DefaultIO *dio): Command(dio) {
    description = "classify data";
}

/**
 * Execute the command on the given algorithm.
 @param algorithmKnn the algorithm.
*/
void Classify::execute(AlgorithmKnn& algorithmKnn) {
    if (algorithmKnn.getTrain()->getNeighbors().empty()) {
        try {
            dio->write("please upload data");
        }
        catch (invalid_argument& ia) {
            cout << "error sending message" << endl;
        }
        return;
    }
    algorithmKnn.classify();
    try {
        dio->write("classifying data complete");
    }
    catch (invalid_argument& ia) {
        cout << "error sending message" << endl;
    }
}