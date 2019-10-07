/*
MATRIX-TREE定理 O(n^3)
无向图:
G=(V,E) |V|=n |E|=m.
度数矩阵为DG 对于所有 1<=i<=n 第 i 行 i 列的项 D(i,i) 为点 i 的度数，其余项为 0
邻接矩阵为AG 对于所有 1<=i,j<=n，第 i 行第 j 列的项 A(i,j) = 点 i 到 j 的连边数 可以有重边
基尔霍夫矩阵为LG=DG−AG 即主对角线上是每个点的度数 其它地方 L(i,j)=−A(i,j) i≠j
无向图中所有不同的生成树的个数等于其基尔霍夫矩阵LG任意一个n-1阶主子式(删除行列编号相同的余子式)绝对值
有向图:
有向图的度数矩阵:对于有向图的边(u,v) D[v][v]++(入度矩阵)/D[u][u]++(出度矩阵)
有向图的邻接矩阵:对于有向图的边(u,v) A[u][v]++
求外向树:将无向图中的度数矩阵改为入度矩阵
求内向树:将无向图中的度数矩阵改为出度矩阵
有向图的基尔霍夫矩阵构造方法与无向图相同 LG=DG-AG
去掉第i行第i列得到主子式的绝对值 即为以i为根的树形图的个数
*/
/*SPOJ HIGH*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long JQK;
const int MAXN = 20;
const int mod=1e9+7;
//存储矩阵,下标都从0开始
JQK G[MAXN][MAXN], C[MAXN][MAXN];  //G邻接矩阵 C度数矩阵
bool isFreeX[MAXN];
JQK A[MAXN][MAXN];      //A基尔霍夫矩阵
JQK ab(ll x) {
        return x > 0 ? x : -x;
}
JQK gauss(int detn) {//求行列式
        for (int i = 0; i < detn; ++i) {
                isFreeX[i] = false;
        }
        JQK ret = 1, neg = 0;
        int r = 1, c = 1;//求n-1阶的行列式，去掉第一阶，所以从1开始
        for (; r < detn && c < detn; ++r, ++c) {
                int p = r;
                for (; p < detn; ++p)
                        if (A[p][c]) {
                                break;
                        }
                if (p == detn) {
                        --r;
                        isFreeX[c] = true;
                        continue;
                }
                if (p != r) {
                        neg ^= 1;
                        for (int i = c; i <= detn; ++i) {
                                swap(A[p][i], A[r][i]);
                        }
                }
                //eliminate coefficient
                for (int i = r + 1; i < detn; ++i) {
                        while (A[i][c]) {
                                JQK delta = A[i][c] / A[r][c];
                                for (int j = c; j <= detn; ++j) {
                                        A[i][j] += - delta * A[r][j];
                                }
                                if (!A[i][c]) {
                                        break;
                                }
                                neg ^= 1;
                                for (int j = c; j <= detn; ++j) {
                                        swap(A[r][j], A[i][j]);
                                }
                        }
                }
        }
        if (r != detn) {
                return 0;
        }
        //0-r-1求n阶行列式，1-r-1求n-1阶行列式
        for (int i = 1; i < r; ++i) {
                ret = ret * A[i][i];
        }
        return ab(ret);
}
JQK det(int detn) {
        int i, j, k, f = 1;
        JQK res = 1, x, y, tmp;
        for (i = 1; i <= detn; ++i)
                for (j = 1; j <= detn; ++j) {
                        A[i][j] = (A[i][j] + mod) % mod;
                }
        for (i = 1; i <= detn; ++i) {
                for (j = i + 1; j <= detn; ++j) {
                        x = A[i][i], y = A[j][i];
                        while (y) {
                                tmp = x / y;
                                x %= y;
                                swap(x, y);
                                for (k = i; k <= detn; ++k) {
                                        A[i][k] = ((A[i][k] - 1ll * tmp * A[j][k]) % mod + mod) % mod;
                                }
                                for (k = i; k <= detn; ++k) {
                                        swap(A[i][k], A[j][k]);
                                }
                                f = -f;
                        }
                }
                if (!A[i][i]) {
                        return 0;
                }
                res = 1ll * res * A[i][i] % mod;
        }
        if (f == -1) {
                res = mod - res;
        }
        return (res % mod + mod) % mod;
}
int main() {
        int cas;
        scanf("%d", &cas);
        while (cas--) {
                int n, m;
                scanf("%d%d", &n, &m);
                memset(G, 0, sizeof(G));
                memset(C, 0, sizeof(C));
                while (m--) {
                        int u, v;
                        scanf("%d%d", &u, &v);
                        u--, v--;
                        G[u][v] = G[v][u] = 1;
                        C[u][u]++, C[v][v]++;
                }
                for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++) {
                                A[i][j] = C[i][j] - G[i][j];
                        }
                ll ans = gauss(n);
                printf("%lld\n", ans);
        }
        return 0;
}

