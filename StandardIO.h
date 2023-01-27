//
// Created by yonia on 21/01/2023.
//

#ifndef EX4_STANDARDIO_H
#define EX4_STANDARDIO_H
#include "DefaultIO.h"

class StandardIO: public DefaultIO {
public:
    string read() override;
    void write(string line) override;

};


#endif //EX4_STANDARDIO_H
