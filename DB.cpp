//
// Created by yonia on 12/12/2022.
//

#include "DB.h"
#include "DistanceFuncManager.h"
#include <fstream>
#include <iostream>

DB::DB() = default;
/**
 * The constructor of DB. He get the name of the file that provided by the user,
   and build the database from the data that written in it.
 * @param file String.

DB::DB(const string& file) {
    string line;
    fstream readStream(file, ios::in);
    // Checks if the file is found.
    if (!readStream.is_open()) {
        cout << "Could not open the file" << endl;
        exit(1);
    }
    // Read the file line by line.
    while (getline(readStream, line)) {
         Check if the line written correctly and can be converted to vector,
           and if it is put the vector in the database.
        Neighbor* newNeighbor = InputManager::neighborCheck(line);
        if (!vectorSize) {
            vectorSize = newNeighbor->getInfo().size();
        } else if (vectorSize != newNeighbor->getInfo().size()) {
            cout << "Not all vectors in the same size" << endl;
            exit(1);
        }
        neighbors.push_back(newNeighbor);
    }
    readStream.close();
}
*/

void DB::uploadData(const string &file) {

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
        delete(*itr);
    }
    // Delete the vector.
    vector<Neighbor*>().swap(neighbors);
}

/**
 * Get input vector and distance function and update all the neighbor's disFromInput
   field to be the distance between each neighbor to that vector.
 * @param input vector<double>.
 * @param distanceFunc char*.
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