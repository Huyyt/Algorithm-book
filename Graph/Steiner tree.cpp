/*
 *  Steiner Tree：求，使得指定K个点连通的生成树的最小总权值
 *  st[i] 表示顶点i的标记值，如果i是指定集合内第m(0<=m<K)个点，则st[i]=1<<m
 *  endSt=1<<K
 *  dptree[i][state] 表示以i为根，连通状态为state的生成树值
 */
#define CLR(x,a) memset(x,a,sizeof(x))
int dptree[N][1 << K], st[N], endSt;
bool vis[N][1 << K];
queue<int> que;
int input()
{
    /*
     *    输入，并且返回指定集合元素个数K
     *    因为有时候元素个数需要通过输入数据处理出来，所以单独开个输入函数。
     */
}
void initSteinerTree()
{
    CLR(dptree, -1);
    CLR(st, 0);
    for (int i = 1; i <= n; i++) {
        CLR(vis[i], 0);
    }
    endSt = 1 << input();
    for (int i = 1; i <= n; i++) {
        dptree[i][st[i]] = 0;
    }
}
void update(int &a, int x)
{
    a = (a > x || a == -1) ? x : a;
}
void SPFA(int state)
{
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u][state] = false;
        for (int i = p[u]; i != -1; i = e[i].next) {
            int v = e[i].vid;
            if (dptree[v][st[v] | state] == -1 ||
                    dptree[v][st[v] | state] > dptree[u][state] + e[i].w) {
                dptree[v][st[v] | state] = dptree[u][state] + e[i].w;
                if (st[v] | state != state || vis[v][state]) {
                    continue;    //只更新当前连通状态
                }
                vis[v][state] = true;
                que.push(v);
            }
        }
    }
}
void steinerTree()
{
    for (int j = 1; j < endSt; j++) {
        for (int i = 1; i <= n; i++) {
            if (st[i] && (st[i]&j) == 0) {
                continue;
            }//如果当前状态没有i节点 跳过
            for (int sub = (j - 1)&j; sub; sub = (sub - 1)&j) {
                //枚举子集 更新
                int x = st[i] | sub, y = st[i] | (j - sub);
                if (dptree[i][x] != -1 && dptree[i][y] != -1) {
                    update(dptree[i][j], dptree[i][x] + dptree[i][y]);
                }
            }
            if (dptree[i][j] != -1) {
                que.push(i), vis[i][j] = true;
            }
        }
        SPFA(j);
    }
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
