//
// Created by yonia on 21/01/2023.
//

#ifndef EX4_DOWNLOAD_H
#define EX4_DOWNLOAD_H
#include "Command.h"
#include "AlgorithmKnn.h"

class Download: public Command {
public:
    explicit Download(DefaultIO* dio);
    void execute(AlgorithmKnn &algorithmKnn) override;
};


#endif //EX4_DOWNLOAD_H
