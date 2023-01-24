//
// Created by yonia on 21/01/2023.
//

#ifndef EX4_CLASSIFY_H
#define EX4_CLASSIFY_H
#include "Command.h"

/**
 * This class represents command 3 - to classify the vectors that in the test db.
*/
class Classify: public Command {
public:
    explicit Classify(DefaultIO* dio);
    void execute(AlgorithmKnn& algorithmKnn) override;
};


#endif //EX4_CLASSIFY_H
