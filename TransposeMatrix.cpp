#include <iostream>

using namespace std;

void Transpose() {
    int row, column;
    unsigned int i, j;
    
    cout << "Enter the number of rows." << endl;
    cin >> row;
    
    cout << endl << "Enter the number of columns." << endl;
    cin >> column;
    
    double matrix[row][column];

    for (i = 0; i < row; i++) {
        cout << "Enter the numbers for row " << (i + 1) << endl;
        for (j = 0; j < column; j++) {
            cin >> matrix[i][j];
        }
    }
    double transMatrix[column][row];
    
    for (j = 0; j < column; j++) {
        cout << endl;
        for (i = 0; i < row; i++) {
            transMatrix[column][row] = matrix[i][j];
            cout << transMatrix[column][row] << " ";
        }
    }
    
}

int main() {
    
    Transpose();

    return 0;
}