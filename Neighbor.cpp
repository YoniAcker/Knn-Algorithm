//
// Created by user on 12/11/2022.
//
#include <string>
#include "Neighbor.h"
#include <vector>
using namespace std;

/**
 * The constructor of Neighbor. He get the info vector and his classification.
 * @param info vector<double>.
 * @param typeName string.
*/
Neighbor::Neighbor(const vector<double>& info, const string& typeName) {
    this->info = info;
    this->typeName = typeName;
}

/**
 * Returns a read-only copy of the information vector.
 * @return const vector<double>&.
*/
vector<double>& Neighbor::getInfo() {
    return info;
}

/**
 * Returns the classification of the neighbor.
 * @return string.
*/
string Neighbor::getTypeName() {
    return typeName;
}

/**
 * Returns the distance from the last vector that given.
 * @return double.
*/
double Neighbor::getDistance() {
    return disFromInput;
}

/**
 * Set the typeName (classification) field to the given name.
 * @param name string.
*/
void Neighbor::setTypeName(string& name) {
    typeName = name;
}
/**
 * Set the disFromInput field to the given distance.
 * @param newDis double.
*/
void Neighbor::setDistance(double newDis) {
    disFromInput = newDis;
}

