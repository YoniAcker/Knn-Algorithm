//
// Created by yonia on 21/01/2023.
//

#ifndef EX4_DISPLAY_H
#define EX4_DISPLAY_H
#include "Command.h"
#include "AlgorithmKnn.h"

class Display: public Command {
public:
    explicit Display(DefaultIO* dio);
    void execute(AlgorithmKnn& algorithmKnn) override;
};


#endif //EX4_DISPLAY_H
