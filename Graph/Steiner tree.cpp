/*
 *  Steiner Tree：求，使得指定K个点连通的生成树的最小总权值 复杂度O(n*3^k+cE*2^k) c为SPFA复杂度中的常数，E为边的数量
 *  st[i] 表示顶点i的标记值，如果i是指定集合内第m(0<=m<K)个点，则st[i]=1<<m
 *  endSt=1<<K
 *  dptree[i][state] 表示以i为根，连通状态为state的生成树值
 */
//Gym - 101908J
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 200005;
const int K = 11;
const double INF = 1000000000;
int n, k;
double f[MAXN][1 << K];
queue<int> q;
bool in[MAXN];
int x[MAXN], y[MAXN];
int to[MAXM << 1], nxt[MAXM << 1], Head[MAXN], ed = 1;
double cost[MAXM << 1];
inline void addedge(int u, int v, double c) {
        to[++ed] = v;
        cost[ed] = c;
        nxt[ed] = Head[u];
        Head[u] = ed;
}
void spfa(int S) {
        while (!q.empty()) {
                int now = q.front();
                q.pop();
                in[now] = 0;
                for (int i = Head[now]; i; i = nxt[i]) {
                        int v = to[i];
                        if (v <= k)
                                continue;
                        if (f[v][S] > f[now][S] + cost[i]) {
                                f[v][S] = f[now][S] + cost[i];
                                if (!in[v])
                                        q.push(v), in[v] = 1;
                        }
                }
        }
}
void work() {
        for (int i = 1; i <= n; i++) {
                for (int j = 0; j <= (1 << k); j++)
                        f[i][j] = INF;
        }
        for (int i = 1; i <= k; i++)  //指定集合初始化为0
                f[i][1 << (i - 1)] = 0;
        for (int sta = 1; sta < (1 << k); sta++) {
                for (int i = 1; i <= n; i++) {
                        for (int s = sta & (sta - 1); s; s = (s - 1)&sta) {
                                f[i][sta] = min(f[i][sta], f[i][s] + f[i][sta ^ s]);
                        }
                        if (f[i][sta] != INF)
                                q.push(i), in[i] = 1;
                }
                spfa(sta);
        }
        double ans = INF;
        for (int i = 1; i <= n; i++)
                ans = min(ans, f[i][(1 << k) - 1]);
        printf("%.5f\n", ans);
}
int main() {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; i++) {
                scanf("%d %d", &x[i], &y[i]);
        }
        for (int i = 1; i <= n; i++) {
                for (int j = i + 1; j <= n; j++) {
                        int xxx = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
                        double dis = sqrt(xxx);
                        addedge(i, j, dis);
                        addedge(j, i, dis);
                }
        }
        work();
}


WC2008 游览计划 带输出方案
#include<bits/stdc++.h>
#define INF 2000000
#define N 10
using namespace std;
int dx[] = {0, 1, 0, -1},dy[] = {1, 0, -1, 0};
int max_s, n, m;
int mat[N][N], st[N][N], vis[N][N], cnt;
int d[N][N][1 << N], pre[N][N][1 << N];
bool in[N][N][1 << N];
queue<int> Q;
void spfa()
{
    int x, y, s, tx, ty, ts;
    while (!Q.empty()) {
        x = Q.front() / 100000;
        y = (Q.front() - x * 100000) / 10000;
        s = Q.front() - x * 100000 - y * 10000;
        Q.pop();
        in[x][y][s] = 0;
        for (int i = 0; i < 4; i++) {
            tx = x + dx[i], ty = y + dy[i];
            if (tx >= n || ty >= m || tx < 0 || ty < 0) {
                continue;
            }
            ts = s | st[tx][ty];
            if (d[x][y][s] + mat[tx][ty] < d[tx][ty][ts]) {
                d[tx][ty][ts] = d[x][y][s] + mat[tx][ty];
                pre[tx][ty][ts] = x * 100000 + y * 10000 + s;
                if (!in[tx][ty][ts] && s == ts) {
                    in[tx][ty][ts] = 1, Q.push(tx * 100000 + ty * 10000 + ts);
                }
            }
        }
    }
}
void go(int x, int y, int s)
{
    vis[x][y] = 1;
    int t = pre[x][y][s], tx, ty, ts;
    if (!t) {
        return;
    }
    tx = t / 100000;
    ty = (t - tx * 100000) / 10000;
    ts = t - tx * 100000 - ty * 10000;
    go(tx, ty, ts);
    if (x == tx && y == ty) {
        go(x, y, (s - ts) | st[x][y]);
    }
}
int main()
{
    //freopen("in.in","r",stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            scanf("%d", &mat[i][j]);
            if (!mat[i][j]) {
                st[i][j] = 1 << (cnt++);
            }
        }
    max_s = 1 << cnt;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < max_s; k++) {
                d[i][j][k] = INF;
            }
            if (st[i][j]) {
                d[i][j][st[i][j]] = 0;
            }
        }
    for (int k = 1; k < max_s; k++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (st[i][j] && !(st[i][j]&k)) {
                    continue;
                }
                for (int x = (k - 1)&k; x; x = (x - 1)&k) {
                    int t = d[i][j][x | st[i][j]] + d[i][j][(k - x) | st[i][j]] - mat[i][j];
                    //因为是点权 所以需要减去多出来的一次
                    if (t < d[i][j][k]) {
                        d[i][j][k] = t, pre[i][j][k] = i * 100000 + j * 10000 + (x | st[i][j]);
                    }
                }
                if (d[i][j][k] < INF) {
                    Q.push(i * 100000 + j * 10000 + k), in[i][j][k] = 1;
                }
            }
        spfa();
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (st[i][j]) {
                printf("%d\n", d[i][j][max_s - 1]);
                go(i, j, max_s - 1);
                for (int x = 0; x < n; x++) {
                    for (int y = 0; y < m; y++) {
                        if (st[x][y]) {
                            putchar('x');
                        } else if (vis[x][y]) {
                            putchar('o');
                        } else {
                            putchar('_');
                        }
                    }
                    puts("");
                }
                return 0;
            }
}
