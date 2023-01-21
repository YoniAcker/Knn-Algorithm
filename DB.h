//
// Created by yonia on 12/12/2022.
//

#ifndef ASS2KNN_DB_H
#define ASS2KNN_DB_H

#include "Neighbor.h"
#include "InputManager.h"
#include <vector>
using namespace std;
/**
 * This class represents the database of the classified vectors that appear
   in the file provided by the user.
*/
class DB {
private:
    vector<Neighbor*> neighbors;
    // The size of all the vectors in the database.
    unsigned int vectorSize = 0;
public:
    explicit DB(const string& file);
    ~DB();
    vector<Neighbor*>& getNeighbors();
    void updateDistance(const vector<double>& input, char* distanceFunc);
};


#endif //ASS2KNN_DB_H
