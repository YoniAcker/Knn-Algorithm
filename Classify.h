//
// Created by yonia on 21/01/2023.
//

#ifndef EX4_CLASSIFY_H
#define EX4_CLASSIFY_H
#include "Command.h"

class Classify: public Command {
public:
    explicit Classify(DefaultIO* dio);
    void execute(AlgorithmKnn& algorithmKnn) override;
};


#endif //EX4_CLASSIFY_H
