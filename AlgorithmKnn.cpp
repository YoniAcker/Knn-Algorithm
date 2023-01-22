//
// Created by tal on 12/13/2022.
//
#include "AlgorithmKnn.h"
#include <algorithm>
#include <map>
using namespace std;

AlgorithmKnn::AlgorithmKnn() = default;

DB *AlgorithmKnn::getTrain() {
    return &train;
}

DB *AlgorithmKnn::getTest() {
    return &test;
}

int  AlgorithmKnn::getK() {
    return K;
}

string AlgorithmKnn::getDistanceFunc() {
    return distanceFunc;
}

void AlgorithmKnn::setK(int k) {
    this->K = k;
}

void AlgorithmKnn::setDistanceFunc(string& distanceFunct) {
    distanceFunc = distanceFunct;
}

/**
 * The function returns true if the first neighbor need to be before the second,
   false otherwise (for sorting).
 * @param n1 the first neighbor.
 * @param n2 the second neighbor.
*/
bool compNeighbor(Neighbor* n1, Neighbor* n2) {
    return n1->getDistance() < n2->getDistance();
}

/**
 * The function get the k closet neighbors to the user's vector and find
   the classification appears the most times.
 * @param closeNeigh the k closet neighbors to the user's vector.
 * @return the classification appears the most times.
*/
string getClassification(const vector<Neighbor*>& closeNeigh) {
    /*
     * This map will contain the type-name as KEY and the number of
       appearances as VAL.
     */
    map<string, int> classifications;
    // Build the map.
    for (Neighbor* neighbor : closeNeigh) {
        if (classifications.count(neighbor->getTypeName()) > 0) {
            classifications[neighbor->getTypeName()] += 1;
        } else {
            classifications[neighbor->getTypeName()] = 1;
        }
    }
    // Find which classification appears the most times.
    string classification;
    int mostAppearances = -1;
    for (auto& i: classifications) {
        if (mostAppearances < i.second) {
            classification = i.first;
            mostAppearances = i.second;
        }
    }
    return classification;
}

/**
 * The function get vector, the 'k' and key for the distance function he will use
   and return his classification according to the database, the k and the distance
   function of the algorithm.
 * @param input vector from the user.
 * @param k the 'k'.
 * @param distanceFunc key to distance function.
 * @return the classification of the vector.
*/
string AlgorithmKnn::vectorClassification(const vector<double>& input) {
    try {
        train.updateDistance(input, distanceFunc);
    }
    catch(invalid_argument& ia) {
        throw invalid_argument("invalid input");
    }
    sort(train.getNeighbors().begin(), train.getNeighbors().end(), compNeighbor);
    return getClassification({train.getNeighbors().begin(),
                              train.getNeighbors().begin() + K});
}

void AlgorithmKnn::classify() {
    for (auto itr : test.getNeighbors()) {
        string cla = vectorClassification(itr->getInfo());
        itr->setTypeName(cla);
    }
}

