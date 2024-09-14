#include "least_squares.hpp"
#include <vector>

using namespace std;

int main() {
    vector<vector<double>> matrixA = {{2.0, 1.0}, {-3.0, 1.0}, {8.0, 1.0}}; // Example x coordinates (with bias term)
    vector<vector<double>> matrixB = {{2.0}, {4.0}, {6.0}};                // Example y coordinates

    least_squares(matrixA, matrixB);

    return 0;
}
