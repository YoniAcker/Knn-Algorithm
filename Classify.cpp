//
// Created by yonia on 21/01/2023.
//

#include "Classify.h"

Classify::Classify(DefaultIO *dio): Command(dio) {
    description = "classify data";
}

void Classify::execute(AlgorithmKnn& algorithmKnn) {
    if (algorithmKnn.getTrain()->getNeighbors().empty()) {
        dio->write("please upload data");
        return;
    }
    algorithmKnn.classify();
    dio->write("classifying data complete");
}