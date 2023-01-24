#ifndef ASS2KNN_NEIGHBOR_H
#define ASS2KNN_NEIGHBOR_H

#include <string>
#include <vector>

using namespace std;

/**
 * This class represents neighbor, that is, a vector of information with its classification.
*/
class Neighbor {
private:
    vector<double> info;
    string typeName;
    // Field that represent the distance from the vector that the user give.
    double disFromInput = 0;
public:
    Neighbor(const vector<double>& info, const string& typeName);
    const vector<double>& getInfo();
    void setTypeName(string& name);
    string getTypeName();
    void setDistance(double newDis);
    double getDistance();
};

#endif //ASS2KNN_NEIGHBOR_H
