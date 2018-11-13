#include <iostream>
#define MAXN 100
#define INF 9999.0
using namespace std;

double optimal_bst(double p[MAXN+1],double q[MAXN+1],int (&root)[MAXN][MAXN],int n){
    int i,j,l,r;
    double e[n+2][n+1],w[n+2][n+1];
    for(i=1;i<=n+1;i++){
        e[i][i-1]=w[i][i-1]=q[i-1];
    }
    for(l=1;l<=n;l++){
        for(i=1;i<=n-l+1;i++){
            j=i+l-1;
            e[i][j]=INF;
            w[i][j]=w[i][j-1]+p[j]+q[j];
            for(r=i;r<=j;r++){
                double t = e[i][r-1]+e[r+1][j]+w[i][j];
                if(t+1e-6<e[i][j]){
                    // cout << i<<"-"<<j<<":"<<e[i][j]<<"-"<<e[i][r-1]+e[r+1][j]+w[i][j]<<"--"<<r<<endl;
                    e[i][j] = e[i][r-1]+e[r+1][j]+w[i][j];
                    
                    root[i-1][j-1] = r;
                }
            }
        }
    }
    return e[1][n];
}

void construct_optimal_bst(int start, int end, int root[MAXN][MAXN])
{
    int node = root[start][end];

    if (node - 2 < start)
        cout << "d" << node - 1 << "为k" << node << "的左孩子" << endl;
    else
    {
        cout << "k" << root[start][node - 2] << "为k" << node << "的左孩子" << endl;
        construct_optimal_bst(start, node - 2, root);
    }

    if (end < node)
        cout << "d" << end + 1 << "为k" << node << "的右孩子" << endl;
    else
    {
        cout << "k" << root[node][end] << "为k" << node << "的右孩子" << endl;
        construct_optimal_bst(node, end, root);
    }
}

int main()
{
    int i, j, n, root[MAXN][MAXN];
    double p[MAXN+1], q[MAXN+1];
    freopen("in.dat", "r", stdin);
    freopen("out.dat", "w", stdout);
    cin >> n;
    for (i = 1; i <= n; i++)
        cin >> p[i];
    for (i = 0; i <= n; i++)
        cin >> q[i];
    cout << optimal_bst(p,q,root,n) << endl;
    // for(i=0;i<n;i++)
    //     for(j=i;j<n;j++)
    //         cout<<root[i][j]<<" ";

    cout << "k" << root[0][n - 1] << "为根" << endl;
    construct_optimal_bst(0, n - 1, root);
    return 0;
}
