//
// Created by yonia on 21/01/2023.
//

#ifndef EX4_CHANGE_H
#define EX4_CHANGE_H
#include "Command.h"

/**
 * This class represents command 2 - to change the algorithm's settings.
*/
class Change: public Command {
public:
    void execute(AlgorithmKnn& algorithmKnn) override;
    explicit Change(DefaultIO* dio);
};


#endif //EX4_CHANGE_H
