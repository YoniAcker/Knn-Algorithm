//
// Created by yonia on 12/12/2022.
//

#include "DB.h"
#include "DistanceFuncManager.h"
#include <fstream>
#include <iostream>

/**
 * Default constructor.
*/
DB::DB() = default;

/**
 * Delete all the information in the db.
*/
void DB::deleteDB() {
    // Delete all the neighbors that in the vector.
    auto itr = neighbors.begin();
    for (;itr != neighbors.end();itr++) {
        delete(*itr);
    }
    // Delete the vector.
    vector<Neighbor*>().swap(neighbors);
}

/**
 * Get line of input that contains vector and optionally classification, make from it a
   neighbor and add hom to the db.
 @param line of input.
 @param isClass does the vector is classified or not.
*/
void DB::addLine(string& line, bool isClass) {
    Neighbor *newNeighbor;
    if (isClass) {
        try {
            newNeighbor = InputManager::neighborCheck(line);
        }
        catch (invalid_argument& ia) {
            throw invalid_argument("invalid input");
        }
    } else {
        try {
            newNeighbor = InputManager::vectorCheck(line);
        }
        catch (invalid_argument& ia) {
            throw invalid_argument("invalid input");
        }
    }
    if (!vectorSize) {
        vectorSize = newNeighbor->getInfo().size();
    } else if (vectorSize != newNeighbor->getInfo().size()) {
        throw invalid_argument("invalid input");
    }
    neighbors.push_back(newNeighbor);
}

/**
 * Returns a read-only copy of the information.
 * @return const vector<Neighbor*>&.
*/
vector<Neighbor*>& DB::getNeighbors() {
    return neighbors;
}

/**
 * The destructor of DB. It delete all the data that in him.
*/
DB::~DB() {
    // Delete all the neighbors that in the vector.
    auto itr = neighbors.begin();
    for (;itr != neighbors.end();itr++) {
        vector<double>().swap((*itr)->getInfo());
        delete(*itr);
    }
    // Delete the vector.
    vector<Neighbor*>().swap(neighbors);
}

/**
 * Get input vector and distance function and update all the neighbor's disFromInput
   field to be the distance between each neighbor to that vector.
 * @param input vector<double>.
 * @param distanceFunc string&.
*/
void DB::updateDistance(const vector<double>& input, string& distanceFunc) {
    // If the info vector not in the same size as the data vector - throw exception.
    if (input.size() != vectorSize) {
        throw invalid_argument("invalid input");
    }
    for (Neighbor *neighbor: neighbors) {
        // Calculate the distance.
        double newDis;
        newDis = DistanceFuncManager::distanceCalc(distanceFunc,
                                                   input, neighbor->getInfo());
        // Update the neighbor.
        neighbor->setDistance(newDis);
    }
}