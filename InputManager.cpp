//
// Created by yonia on 12/12/2022.
//

#include "InputManager.h"
#include "Neighbor.h"
#include <cstring>
#include <stdexcept>
#include <vector>

/**
 * This function gets line of input and check if it can be converted to a neighbor. if
   it is - return a pointer to that neighbor, otherwise exit from the program.
 * @param line string.
 * @return Neighbor*.
*/
Neighbor* InputManager::neighborCheck(const string& line) {
    vector<double> info;
    // Convert the string line to array of chars - lineArray.
    char lineArray[line.size() + 1];
    strcpy(lineArray, line.data());
    lineArray[line.size()] = '\0';
    // Get the first number of info.
    char* part = strtok(lineArray, ",");
    /* Checks that it is indeed a number (otherwise exits the program because
       there must be at least one number in the information vector). */
    try {
        double num = stod(part);
        info.push_back(num);
    }
    catch (invalid_argument &ia) {
        throw invalid_argument("invalid input");
    }
    // Continue to the next parts
    part = strtok(nullptr, ",");
    while (part != nullptr) {
        try {
            double num = stod(part);
            info.push_back(num);
            part = strtok(nullptr, ",");
        }
        catch (invalid_argument &ia) {
            // If the part is not a number than it must be the last part.
            if (!strtok(nullptr, ",")) {
                return new Neighbor(info, part);
            }
            throw invalid_argument("invalid input");
        }
    }
    /* If we got here then there was no classification in the input and
       therefore the file is incorrect. */
    throw invalid_argument("invalid input");
}

/**
 * This function gets line of input and check if it can be converted to a (unclassified)
   vector. if it is - return that vector and change.
 * @param line the input.
 * @return vector<double>.
*/
Neighbor* InputManager::vectorCheck(const string& line) {
    vector<double> newVector;
    // Convert the string line to array of chars - lineArray.
    char lineArray[line.size() + 1];
    strcpy(lineArray, line.data());
    lineArray[line.size()] = '\0';
    // Read the line part by part.
    char* part = strtok(lineArray, ",");
    // Get all the numbers of the vector.
    while (part != nullptr) {
        // Checks that it is a number.
        try {
            double num = stod(part);
            newVector.push_back(num);
            part = strtok(nullptr, ",");
        }
        // If it's not then we are done with the vector.
        catch (invalid_argument &ia) {
            throw invalid_argument("invalid input");
        }
    }
    return new Neighbor(newVector, "");
}
