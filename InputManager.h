//
// Created by yonia on 12/12/2022.
//

#ifndef ASS2KNN_INPUTMANAGER_H
#define ASS2KNN_INPUTMANAGER_H

#include "Neighbor.h"
#include <vector>
using namespace std;

/**
 * This class responsible for checking the input received from the user.
*/
class InputManager {
public:
    static Neighbor* neighborCheck(const string& line);
    static Neighbor* vectorCheck(const string& line);
};


#endif
