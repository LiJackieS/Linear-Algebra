#include "least_squares.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

// Function to transpose a matrix
vector<vector<double>> transposeMatrix(const vector<vector<double>>& matrix) {
    vector<vector<double>> transMatrix(matrix[0].size(), vector<double>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            transMatrix[j][i] = matrix[i][j];
        }
    }
    return transMatrix;
}

// Function to multiply two matrices
vector<vector<double>> multiplyMatrices(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2) {
    vector<vector<double>> result(matrix1.size(), vector<double>(matrix2[0].size(), 0));
    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix2[0].size(); ++j) {
            for (size_t k = 0; k < matrix1[0].size(); ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

// Function to perform Gaussian elimination
void gaussianElimination(vector<vector<double>>& matrix) {
    size_t rowCount = matrix.size();
    size_t colCount = matrix[0].size();

    for (size_t k = 0; k < rowCount; ++k) {
        double maxVal = abs(matrix[k][k]);
        size_t maxRow = k;
        for (size_t m = k + 1; m < rowCount; ++m) {
            if (abs(matrix[m][k]) > maxVal) {
                maxVal = abs(matrix[m][k]);
                maxRow = m;
            }
        }

        swap(matrix[maxRow], matrix[k]);

        for (size_t m = k + 1; m < rowCount; ++m) {
            double factor = matrix[m][k] / matrix[k][k];
            for (size_t n = k; n < colCount; ++n) {
                matrix[m][n] -= factor * matrix[k][n];
            }
        }
    }
}

// Function to perform backward substitution
vector<double> backwardSubstitution(const vector<vector<double>>& matrix) {
    size_t rowCount = matrix.size();
    size_t colCount = matrix[0].size();
    vector<double> result(rowCount);

    for (int i = rowCount - 1; i >= 0; --i) {
        result[i] = matrix[i][colCount - 1];
        for (size_t j = i + 1; j < rowCount; ++j) {
            result[i] -= matrix[i][j] * result[j];
        }
        result[i] /= matrix[i][i];
    }
    return result;
}

// Function to print the line of best fit
void printLineOfBestFit(double slope, double intercept) {
    cout << fixed << setprecision(4);
    cout << "The line of best fit for the data points provided is: y = " << slope << "x + " << intercept << endl;
}

// Main least squares function
void least_squares(const vector<vector<double>>& matrixA, const vector<vector<double>>& matrixB) {
    auto start = chrono::high_resolution_clock::now();

    vector<vector<double>> transMatrixA = transposeMatrix(matrixA);
    vector<vector<double>> multTransA_and_A = multiplyMatrices(transMatrixA, matrixA);
    vector<vector<double>> multTransA_and_B = multiplyMatrices(transMatrixA, matrixB);

    vector<vector<double>> matrixC(multTransA_and_A.size(), vector<double>(multTransA_and_A[0].size() + 1, 0));
    for (size_t i = 0; i < multTransA_and_A.size(); ++i) {
        for (size_t j = 0; j < multTransA_and_A[0].size(); ++j) {
            matrixC[i][j] = multTransA_and_A[i][j];
        }
        matrixC[i].back() = multTransA_and_B[i][0];
    }

    gaussianElimination(matrixC);
    vector<double> coefficients = backwardSubstitution(matrixC);

    double slope = coefficients[0];
    double intercept = coefficients[1];

    printLineOfBestFit(slope, intercept);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Code execution time: " << duration.count() << " seconds." << endl;
}
