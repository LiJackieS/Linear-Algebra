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
std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2) {
    std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(matrix2[0].size(), 0));
    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix2[0].size(); ++j) {
            for (size_t k = 0; k < matrix1[0].size(); ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

// Function to perform Gaussian elimination with partial pivoting
void gaussianElimination(std::vector<std::vector<double>>& matrix) {
    size_t rowCount = matrix.size();
    size_t colCount = matrix[0].size();

    for (size_t k = 0; k < rowCount; ++k) {
        // Find the row with the maximum element in the current column
        double maxVal = std::abs(matrix[k][k]);
        size_t maxRow = k;
        for (size_t m = k + 1; m < rowCount; ++m) {
            if (std::abs(matrix[m][k]) > maxVal) {
                maxVal = std::abs(matrix[m][k]);
                maxRow = m;
            }
        }

        // Swap the maximum row with the current row
        std::swap(matrix[maxRow], matrix[k]);

        // Make all rows below this one 0 in current column
        for (size_t m = k + 1; m < rowCount; ++m) {
            double factor = matrix[m][k] / matrix[k][k];
            for (size_t n = k; n < colCount; ++n) {
                matrix[m][n] -= factor * matrix[k][n];
            }
        }
    }
}

// Function to perform backward substitution
std::vector<double> backwardSubstitution(const std::vector<std::vector<double>>& matrix) {
    size_t rowCount = matrix.size();
    size_t colCount = matrix[0].size();
    std::vector<double> result(rowCount);

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
    std::cout << std::fixed << std::setprecision(4); // Set precision for better readability
    std::cout << "The line of best fit for the data points provided is: y = " << slope << "x + " << intercept << std::endl;
}
