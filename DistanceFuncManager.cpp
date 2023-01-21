#include "DistanceFuncManager.h"
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int MINKOWSKI_P = 2;

/**
 * Calculate the Euclidean distance between the two vectors.
 * @param first the first vector.
 * @param second the second vector.
 * @return the Euclidean distance between the two vectors.
 */
double euclidean (vector<double> first, vector<double> second){
    double distance = 0;
    /*
     Goes over both vectors at the same time and calculates the required distance.
    */
    auto itr1 = first.begin(), itr2 = second.begin();
    for (; itr1 != first.end(); itr1++, itr2++) {
        distance = distance + pow(*itr1 - *itr2,2);
    }
    return pow(distance,0.5);
}

/**
 * Calculate the Manhattan distance between the two vectors.
 * @param first the first vector.
 * @param second the second vector.
 * @return the Taxicab distance between the two vectors.
 */
double manhattan(vector<double> first, vector<double> second){
    double distance = 0;
    auto itr1 = first.begin(), itr2 = second.begin();
    for (; itr1 != first.end(); itr1++, itr2++) {
        distance = distance + abs(*itr1 - *itr2);
    }
    return distance;
}

/**
 * Calculate the Chebyshev distance between the two vectors.
 * @param first the first vector.
 * @param second the second vector.
 * @return the Chebyshev distance between the two vectors.
 */
double chebyshev(vector<double> first, vector<double> second) {
    double max = 0;
    auto itr1 = first.begin(), itr2 = second.begin();
    for (; itr1 != first.end(); itr1++, itr2++) {
        double result = abs(*itr1 - *itr2);
        if (result > max) {
            max = result;
        }
    }
    return max;
}

/**
 * Calculate the Canberra distance between the two vectors.
 * @param first the first vector.
 * @param second the second vector.
 * @return the Canberra distance between the two vectors.
 */
double canberra(vector<double> first, vector<double> second) {
    double sum = 0;
    auto itr1 = first.begin(), itr2 = second.begin();
    for (; itr1 != first.end(); itr1++, itr2++) {
        double result = abs(*itr1 - *itr2) / (abs(*itr1) + abs(*itr2));
        sum += result;
    }
    return sum;
}

/**
 * Calculate the Minkowski distance between the two vectors.
 * @param first the first vector.
 * @param second the second vector.
 * @return the Minkowski distance between the two vectors.
 */
 double minkowski(vector<double> first, vector<double> second) {
    double sum = 0;
    auto itr1 = first.begin(), itr2 = second.begin();
    for (; itr1 != first.end(); itr1++, itr2++) {
        double result = pow(abs(*itr1 - *itr2), MINKOWSKI_P);
        sum += result;
    }
    return pow(sum, 1.0 / MINKOWSKI_P);
}

/**
 * Calculate the distance between the two vectors according to the given
   key to one of the distance function.
 * @param funcKey the key to the requested distance function.
 * @param first the first vector.
 * @param second the second vector.
 * @return the distance between the two vectors.
 */
double DistanceFuncManager::distanceCalc(char *funcKey, const vector<double> &first,
                                         const vector<double>& second) {
     if (!strcmp(funcKey, "AUC")) {
         return euclidean(first, second);
     } else if (!strcmp(funcKey, "MAN")) {
         return manhattan(first, second);
     } else if (!strcmp(funcKey, "CHB")) {
         return chebyshev(first, second);
     } else if (!strcmp(funcKey, "CAN")) {
         return canberra(first, second);
     } else if (!strcmp(funcKey, "MIN")) {
         return minkowski(first, second);
     } else {
         throw invalid_argument("invalid input");
     }
 }

