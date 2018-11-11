#include <iostream>
#define MAXN 100
using namespace std;

int matrix[MAXN][MAXN];
int precursor_matrix[MAXN][MAXN];

void print_path_recursion(int i, int j) {
    if (i == j) {
        cout << (i + 1) << " ";
    } else {
        print_path_recursion(i, precursor_matrix[i][j]);
        cout << (j + 1) << " ";
    }
}

int main(void) {
    freopen("in.dat", "r", stdin);
    freopen("out.dat", "w", stdout);
    int testcase;
    cin >> testcase;

    for (int index = 0; index < testcase; ++index) {
        int n;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> matrix[i][j];
                if (matrix[i][j] >= 100) { matrix[i][j] = 32767; }
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j || matrix[i][j] >= 100) {
                    precursor_matrix[i][j] = -1;
                } else if (i != j || matrix[i][j] < 100) {
                    precursor_matrix[i][j] = i;
                }
            }
        }

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (matrix[i][j] <= matrix[i][k] + matrix[k][j]) {
                        precursor_matrix[i][j] = precursor_matrix[i][j];
                    } else {
                        precursor_matrix[i][j] = precursor_matrix[k][j];
                    }
                    if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                }
            }
        }

        cout << testcase << endl;

        cout << n << endl;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) { cout << matrix[i][j] << " "; }
            cout << endl;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                print_path_recursion(i, j);
                if (i == j) { cout << (i + 1); }
                cout << endl;
            }
        }
    }

    return 0;
}
