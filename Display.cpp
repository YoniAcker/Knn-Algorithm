//
// Created by yonia on 21/01/2023.
//

#include "Display.h"

Display::Display(DefaultIO *dio): Command(dio) {
    description = "display results";
}
void Display::execute(AlgorithmKnn& algorithmKnn) {
    if (algorithmKnn.getTest()->getNeighbors().empty()) {
        dio->write("please upload data");
        return;
    }
    if (algorithmKnn.getTest()->getNeighbors().front()->getTypeName().empty()) {
        dio->write("please classify the data");
        return;
    }
    int i = 1;
    for (auto& itr : algorithmKnn.getTest()->getNeighbors()) {
        string line = to_string(i);
        line += "   ";
        line += itr->getTypeName();
        dio->write(line);
    }
    dio->write("Done.");
}