#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <cmath>

// Function declarations
void getInputData(int& row, std::vector<std::vector<double>>& matrixA, std::vector<std::vector<double>>& matrixB);
std::vector<std::vector<double>> transposeMatrix(const std::vector<std::vector<double>>& matrix);
std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2);
void gaussianElimination(std::vector<std::vector<double>>& matrix);
std::vector<double> backwardSubstitution(const std::vector<std::vector<double>>& matrix);
void printLineOfBestFit(double slope, double intercept);

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    int row;
    std::vector<std::vector<double>> matrixA, matrixB;

    getInputData(row, matrixA, matrixB);

    std::vector<std::vector<double>> transMatrixA = transposeMatrix(matrixA);
    std::vector<std::vector<double>> multTransA_and_A = multiplyMatrices(transMatrixA, matrixA);
    std::vector<std::vector<double>> multTransA_and_B = multiplyMatrices(transMatrixA, matrixB);

    // Combine matrices to prepare for Gaussian elimination
    std::vector<std::vector<double>> matrixC(multTransA_and_A.size(), std::vector<double>(multTransA_and_A[0].size() + 1, 0));
    for (size_t i = 0; i < multTransA_and_A.size(); ++i) {
        for (size_t j = 0; j < multTransA_and_A[0].size(); ++j) {
            matrixC[i][j] = multTransA_and_A[i][j];
        }
        matrixC[i].back() = multTransA_and_B[i][0];
    }

    gaussianElimination(matrixC);
    std::vector<double> coefficients = backwardSubstitution(matrixC);

    double slope = coefficients[0];
    double intercept = coefficients[1];

    printLineOfBestFit(slope, intercept);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "New code execution time: " << duration.count() << " seconds." << std::endl;

    return 0;
}

// Function to get input data
void getInputData(int& row, std::vector<std::vector<double>>& matrixA, std::vector<std::vector<double>>& matrixB) {
    std::cout << "How many points will you be plotting." << std::endl;
    std::cin >> row;

    matrixA.resize(row, std::vector<double>(2));
    matrixB.resize(row, std::vector<double>(1));

    for (int i = 0; i < row; ++i) {
        std::cout << "Enter the x coordinate for #" << i + 1 << std::endl;
        std::cin >> matrixA[i][0];
        matrixA[i][1] = 1;
        std::cout << "Enter the y coordinate for #" << i + 1 << std::endl;
        std::cin >> matrixB[i][0];
    }
}

// Function to transpose a matrix
std::vector<std::vector<double>> transposeMatrix(const std::vector<std::vector<double>>& matrix) {
    std::vector<std::vector<double>> transMatrix(matrix[0].size(), std::vector<double>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            transMatrix[j][i] = matrix[i][j];
        }
    }
    return transMatrix;
}

// Function to multiply two matrices
std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double
