//
// Created by yonia on 21/01/2023.
//

#ifndef EX4_DEFAULTIO_H
#define EX4_DEFAULTIO_H
#include <string>
using namespace std;

/**
 * This class represents IO system.
*/
class DefaultIO {
public:
    virtual string read() = 0;
    virtual void write(string line) = 0;
    ~DefaultIO() = default;
};


#endif //EX4_DEFAULTIO_H
