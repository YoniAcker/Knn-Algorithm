#ifndef ASS1PART2_DISTANCE_FUNCTIONS_H
#define ASS1PART2_DISTANCE_FUNCTIONS_H

#include <vector>
#include <string>
using namespace std;

/**
 * This class responsible for calculate distance according to the given function key.
*/
class DistanceFuncManager {
public:
    static double distanceCalc(string& funcKey, const vector<double>& first,
                        const vector<double>& second);
};

#endif //ASS1PART2_DISTANCE_FUNCTIONS_H
