#include <iostream>
#define INF 32767
#define MAXN 100
using namespace std;

void print_path(int i, int j, int p_matrix[MAXN][MAXN])
{
    if (i == j)
        cout << (i + 1) << " ";
    else{
        print_path(i, p_matrix[i][j], p_matrix);
        cout << (j + 1) << " ";
    }
}

void modified_floyd_warshall(int n, int (&matrix)[MAXN][MAXN], int (&p_matrix)[MAXN][MAXN])
{
    int i, j, k;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (matrix[i][j] <= matrix[i][k] + matrix[k][j])
                    p_matrix[i][j] = p_matrix[i][j];
                else
                    p_matrix[i][j] = p_matrix[k][j];

                if (matrix[i][j] > matrix[i][k] + matrix[k][j])
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }
}

int main()
{
    freopen("in.dat", "r", stdin);
    freopen("out.dat", "w", stdout);
    int m, index;
    int matrix[MAXN][MAXN], p_matrix[MAXN][MAXN];
    cin >> m;
    cout << m << endl;
    for (index = 0; index < m; index++)
    {
        int i, j, k, n;
        cin >> n;
        cout << n << endl;

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                cin >> matrix[i][j];
                if (matrix[i][j] >= 100)
                    matrix[i][j] = INF;
            }
        }

        //get pi_0
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (i == j || matrix[i][j] >= 100)
                    p_matrix[i][j] = -1;
                else if (i != j || matrix[i][j] < 100)
                    p_matrix[i][j] = i;
            }
        }

        modified_floyd_warshall(n, matrix, p_matrix);

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
            {
                if(matrix[i][j]<INF)
                    print_path(i, j, p_matrix);
                else
                    cout<<"NULL";
                cout << endl;
            }
    }

    return 0;
}
