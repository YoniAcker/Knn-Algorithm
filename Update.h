//
// Created by yonia on 21/01/2023.
//

#ifndef EX4_UPDATE_H
#define EX4_UPDATE_H
#include "Command.h"
#include "AlgorithmKnn.h"

class Update: public Command {
public:
    explicit Update(DefaultIO* dio);
    void execute(AlgorithmKnn &algorithmKnn) override;
};


#endif //EX4_UPDATE_H
