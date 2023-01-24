
// Created by yonia on 21/01/2023.
//

#ifndef EX4_COMMAND_H
#define EX4_COMMAND_H
#include <string>
#include "DefaultIO.h"
#include "AlgorithmKnn.h"
using namespace std;

/**
 * This class represents action that can be done on the algorithm or by him.
*/
class Command {
protected:
    string description;
    DefaultIO* dio;
public:
    explicit Command(DefaultIO* dio);
    string getDescription();
    virtual void execute(AlgorithmKnn& algorithmKnn) = 0;
};


#endif //EX4_COMMAND_H
