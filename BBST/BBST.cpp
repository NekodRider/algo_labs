#include <iostream>
#define MAXN 100
using namespace std;

void construct_optimal_bst(int start, int end, int root[MAXN][MAXN])
{
    int node = root[start][end];

    if (node - 2 < start)
        cout << "d" << node - 1 << "是k" << node << "的左孩子" << endl;
    else
    {
        cout << "k" << root[start][node - 2] << "是k" << node << "的左孩子" << endl;
        construct_optimal_bst(start, node - 2, root);
    }

    if (end < node)
        cout << "d" << end + 1 << "是k" << node << "的右孩子" << endl;
    else
    {
        cout << "k" << root[node][end] << "是k" << node << "的右孩子" << endl;
        construct_optimal_bst(node, end, root);
    }
}

int main()
{
    int i, j, n, root[MAXN][MAXN];
    freopen("in.dat", "r", stdin);
    freopen("out.dat", "w", stdout);
    cin >> n;
    for (i = 0; i < n; ++i)
        for (j = i; j < n; ++j)
            cin >> root[i][j];

    cout << "k" << root[0][n - 1] << "是根" << endl;
    construct_optimal_bst(0, n - 1, root);
    return 0;
}
