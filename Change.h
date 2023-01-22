//
// Created by yonia on 21/01/2023.
//

#ifndef EX4_CHANGE_H
#define EX4_CHANGE_H
#include "Command.h"

class Change: public Command {
public:
    void execute(AlgorithmKnn& algorithmKnn) override;
    explicit Change(DefaultIO* dio);
};


#endif //EX4_CHANGE_H
