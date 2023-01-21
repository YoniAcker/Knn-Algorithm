//
// Created by yonia on 12/12/2022.
//

#include "InputManager.h"
#include "Neighbor.h"
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>

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
    strcpy(lineArray, line.c_str());
    lineArray[line.size() + 1] = '\0';
    // Get the first number of info.
    char* part = strtok(lineArray, ",");
    /* Checks that it is indeed a number (otherwise exits the program because
       there must be at least one number in the information vector). */
    try {
        double num = stod(part);
        info.push_back(num);
    }
    catch (invalid_argument &ia) {
        cout << "Invalid file" << endl;
        exit(1);
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
            cout << "Invalid file" << endl;
            exit(1);
        }
    }
    /* If we got here then there was no classification in the input and
       therefore the file is incorrect. */
    cout << "Invalid file" << endl;
    exit(1);
}

/**
 * This function gets line of input and check if it can be converted to a (unclassified)
   vector, distance function and 'k'. if it is - return that vector and change the
   pointers to point to the function key and 'k', otherwise exit from the program.
 * @param line the input.
 * @param distanceFunc pointer to array of chars.
 * @param k pointer to int.
 * @return vector<double>.
*/
vector<double> InputManager::vectorCheck(char* line, char* distanceFunc, int* k) {
    vector<double> newVector;
    // Read the line part by part.
    char* part = strtok(line, " ");
    // Check if the first part is a number.
    try {
        double num = stod(part);
        newVector.push_back(num);
        part = strtok(nullptr, " ");
    }
    // If not, we get an empty vector and therefore throw exception.
    catch (invalid_argument &ia) {
        throw invalid_argument("invalid input");
    }
    // Get all the numbers of the vector.
    while (part != nullptr) {
        // Checks that it is a number.
        try {
            double num = stod(part);
            newVector.push_back(num);
            part = strtok(nullptr, " ");
        }
        // If it's not then we are done with the vector.
        catch (invalid_argument &ia) {
            break;
        }
    }
    // Check if there is key to function.
    if (part == nullptr) {
        throw invalid_argument("invalid input");
    }
    // Check if the function key is in the correct size.
    if (strlen(part) != 3) {
        throw invalid_argument("invalid input");
    }
    strncpy(distanceFunc, part, 3);
    part = strtok(nullptr, " ");
    // Check if there is k.
    if (part == nullptr) {
        throw invalid_argument("invalid input");
    }
    // Check if the k is valid.
    try {
        *k = stoi(part);
    }
    catch(invalid_argument& ia) {
        throw invalid_argument("invalid input");
    }
    return newVector;
}
