#include <iostream>
#include <iomanip> 
using namespace std;

void ReducedRowEchelonForm() {
    int row, column;
    unsigned int i, j;

    cout << "Enter the number of rows." << endl;
    cin >> row;
    cout << "Enter the number of columns." << endl;
    cin >> column;

    double matrix[row][column];

    for (i = 0; i < row; i++) {
        cout << "Enter the values for row " << (i + 1) << endl;
        for (j = 0; j < column; j++) {
            cin >> matrix[i][j];
        }
    }

    int lead = 0;
    for (int r = 0; r < row; r++) {
        if (lead >= column) {
            break;
        }
        int i = r;
        while (matrix[i][lead] == 0) {
            i++;
            if (i == row) {
                i = r;
                lead++;
                if (lead == column) {
                    break;
                }
            }
        }
        for (int j = 0; j < column; j++) {
            double temp = matrix[r][j];
            matrix[r][j] = matrix[i][j];
            matrix[i][j] = temp;
        }

        double lv = matrix[r][lead];
        for (int j = 0; j < column; j++) {
            matrix[r][j] /= lv;
        }

        for (int i = 0; i < row; i++) {
            if (i != r) {
                double lv = matrix[i][lead];
                for (int j = 0; j < column; j++) {
                    matrix[i][j] -= lv * matrix[r][j];
                }
            }
        }
        lead++;
    }

    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            if ((matrix[i][j] < 0.00001) && (matrix[i][j] > 0)) {
                matrix[i][j] = 0;
            } else if (((matrix[i][j] > -0.00001) && (matrix[i][j] < 0)) || (matrix[i][j] == -0)) {
                matrix[i][j] = 0;
            }
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    ReducedRowEchelonForm();
    return 0;
}
