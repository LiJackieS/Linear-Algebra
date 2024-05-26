#include <iostream>
#include <stdexcept>
using namespace std;

void MatrixMultiplication() {
    int row1, column1, row2, column2;
    unsigned int i, j, k;
    
    cout << "Enter the number of rows for the first matrix: ";
    cin >> row1;

    cout << "Enter the number of columns for the first matrix: ";
    cin >> column1;

    cout << "Enter the number of rows for the second matrix: ";
    cin >> row2;

    cout << "Enter the number of columns for the second matrix: ";
    cin >> column2;

    try {
        if (column1 != row2) {
            throw runtime_error("Invalid matrices");
        }
    }
    catch (runtime_error &excpt) {
        cout << endl << "ERROR: " << excpt.what() << endl;
        cout << "The columns of matrix 1 must be the same as the rows of matrix 2" << endl;
        exit(0);
    }

    double a[row1][column1], b[row2][column2], mult[row1][column2] = {};

    cout << endl << "Enter the elements of matrix 1" << endl;
    for (i = 0; i < row1; ++i) {
        for (j = 0; j < column1; ++j) {
            cout << "Enter element [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> a[i][j];
        }
    }

    cout << endl << "Enter the elements of matrix 2" << endl;
    for (i = 0; i < row2; ++i) {
        for (j = 0; j < column2; ++j) {
            cout << "Enter element [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> b[i][j];
        }
    }

    for (i = 0; i < row1; ++i) {
        for (j = 0; j < column2; ++j) {
            for (k = 0; k < column1; ++k) {
                mult[i][j] += a[i][k] * b[k][j];
            }
        }
    }


    cout << endl << "Resultant matrix:" << endl;
    for (i = 0; i < row1; ++i) {
        for (j = 0; j < column2; ++j) {
            cout << mult[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    MatrixMultiplication();
    return 0;
}
