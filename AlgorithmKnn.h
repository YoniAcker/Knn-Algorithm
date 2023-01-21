//
// Created by user on 12/13/2022.
//

#ifndef ASS2KNN_ALGORITHMKNN_H
#define ASS2KNN_ALGORITHMKNN_H
#include "DB.h"
#include "Neighbor.h"
#include "InputManager.h"
#include <vector>
#include <iostream>

/**
 * This class represents the KNN algorithm. We will use him to classify vectors.
*/
class AlgorithmKnn {
    DB* db;
    /* The user gives us the number K, which means -
       we need to perform the calculation based on
       the K members closest to the vector. */
    int K = 0;
    char* distanceFunc = nullptr;
public:
    explicit AlgorithmKnn(DB* db);
    string vectorClassification(const vector<double>& input,
                                char* distanceFunct, int k);
};


#endif //ASS2KNN_ALGORITHMKNN_H
