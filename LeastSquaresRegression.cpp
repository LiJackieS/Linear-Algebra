#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
    int columnA = 2; 
    int columnB = 1; 
    int row;
    cout << "How many points will you be plotting." << endl;
    cin >> row;

    double matrixA[row][columnA];
    double matrixB[row][columnB];

    for (int i = 0; i < row; i++) { //Initializes the matrix
        cout << "Enter the x coordinate for #" << i + 1 << endl;
        cin >> matrixA[i][0];
        matrixA[i][1] = 1;
        cout << "Enter the y coordinate for #" << i + 1 << endl;
        cin >> matrixB[i][0];
    }

    int transRow = columnA;
    int transColumn = row;
    double transMatrixA[transRow][transColumn];

    //Calculates for the transpose of matrix A
    for (int i = 0; i < transRow; i++) {
        for (int j = 0; j < transColumn; j++) {
            transMatrixA[i][j] = matrixA[j][i];
        }
    }

    int row1 = transRow;
    int column1 = transColumn;
    int column2 = columnA;

    
    double multTransA_and_A[row1][column2] = {}; //Ensures that the elements are 0
    //multiplying the transpose of A with matrix A
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < column2; j++) {
            for (int k = 0; k < column1; k++) {
                multTransA_and_A[i][j] += transMatrixA[i][k] * matrixA[k][j];
            }
        }
    }
    // multiplying the transpose of A with matrix B
    double multTransA_and_B[row1][1] = {}; //Ensures that the elements are 0
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < column1; j++) {
            multTransA_and_B[i][0] += transMatrixA[i][j] * matrixB[j][0];
        }
    }
    // combining the two matricies to prepare for Gaussian elimination
    double matrixC[row1][column2 + 1] = {}; //Ensures the elements are 0
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < column2; j++) {
            matrixC[i][j] = multTransA_and_A[i][j];
        }
        matrixC[i][column2] = multTransA_and_B[i][0];
    }

    // Perform Gaussian elimination with partial pivoting
    for (int k = 0; k < row1; k++) {
        // Find the row with the maximum element in the current column
        double maxVal = abs(matrixC[k][k]);
        int maxRow = k;
        for (int m = k + 1; m < row1; m++) {
            if (abs(matrixC[m][k]) > maxVal) { 
                maxVal = abs(matrixC[m][k]);
                maxRow = m;
            }
        }

        // Swap the maximum row with the current row
        for (int n = k; n < column2 + 1; n++) {
            double tmp = matrixC[maxRow][n];
            matrixC[maxRow][n] = matrixC[k][n];
            matrixC[k][n] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int m = k + 1; m < row1; m++) {
            double factor = matrixC[m][k] / matrixC[k][k];
            for (int n = k; n < column2 + 1; n++) {
                matrixC[m][n] -= factor * matrixC[k][n];
            }
        }
    }

    // Backward substitution
    for (int i = row1 - 1; i >= 0; i--) {
        for (int j = i + 1; j < column2; j++) {
            matrixC[i][column2] -= matrixC[i][j] * matrixC[j][column2];
        }
        matrixC[i][column2] /= matrixC[i][i];
    }
    // creating the line of best fit
    double x = matrixC[0][column2];
    double b = matrixC[1][column2];

    cout << fixed << setprecision(4); // Set precision for better readability
    cout << "The line of best fit for the data points provided is : y = " << x << "x + " << b << endl;

    return 0;
}
