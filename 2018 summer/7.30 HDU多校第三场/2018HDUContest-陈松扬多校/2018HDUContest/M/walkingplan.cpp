#include<cstdio>
#define rep(i) for(int i=0;i<n;i++)
const int N = 55, M = 105, inf = 1000000000;
int T, n, m, x, y, q, K, A, B, z, g[N][N], d[N][N], f[N][N], a[M][N][N], b[M][N][N];
inline void up(int&a, int b)
{
        if (a > b)
        {
                a = b;
        }
}
inline void mul(int a[][N], int b[][N], int c[][N])
{
        static int f[N][N];
        for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                        f[i][j] = inf;
                        for (int k = 0; k < n; k++)
                        {
                                up(f[i][j], a[i][k] + b[k][j]);
                        }
                }
        for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                        c[i][j] = f[i][j];
                }
}
int main()
{
        scanf("%d", &T);
        while (T--)
        {
                scanf("%d%d", &n, &m);
                for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                        {
                                g[i][j] = inf;   //g[i][j]表示从i到j的最短路
                        }
                while (m--)
                {
                        scanf("%d%d%d", &x, &y, &z);
                        x--, y--;
                        up(g[x][y], z);  //如果有重边的话取小的
                }
                for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                        {
                                a[0][i][j] = b[0][i][j] = i == j ? 0 : inf;
                                //b[k][i][j]表示从i开始到j经过k*100条路的最短路
                                //a[k][i][j]表示从i开始到j经过k条路的最短路
                        }
                for (int i = 1; i < M; i++)
                {
                        mul(a[i - 1], g, a[i]);
                }
                for (int i = 1; i < M; i++)
                {
                        mul(b[i - 1], a[100], b[i]);
                }
                for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                        {
                                d[i][j] = i == j ? 0 : g[i][j]; //d为弗洛伊德距离
                        }
                for (int k = 0; k < n; k++)
                        for (int i = 0; i < n; i++)
                                for (int j = 0; j < n; j++)
                                {
                                        up(d[i][j], d[i][k] + d[k][j]);
                                }
                for (x = 0; x < M; x++)
                {
                        for (int i = 0; i < n; i++)
                                for (int j = 0; j < n; j++)
                                {
                                        f[i][j] = inf;
                                }
                        for (int i = 0; i < n; i++)
                                for (int j = 0; j < n; j++)
                                        for (int k = 0; k < n; k++)
                                        {
                                                up(f[i][j], b[x][i][k] + d[k][j]);
                                        }
                        for (int i = 0; i < n; i++)
                                for (int j = 0; j < n; j++)
                                {
                                        b[x][i][j] = f[i][j];
                                }
                }
                scanf("%d", &q);
                while (q--)
                {
                        scanf("%d%d%d", &x, &y, &K);
                        x--, y--;
                        A = K % 100, B = K / 100;
                        z = inf;
                        for (int i = 0; i < n; i++)
                        {
                                up(z, a[A][x][i] + b[B][i][y]);
                        }
                        if (z >= inf)
                        {
                                z = -1;
                        }
                        printf("%d\n", z);
                }
        }
}
