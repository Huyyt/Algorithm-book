/*给定一个n个点m条边的无向连通图，多次询问两点之间的最小割
根据原图每次dinic生成一条边 把原图连成一棵树 树上去掉(s,t)后产生的两个集合恰好是原图上(s,t)的最小割把原图分成的两个集合
每次询问原图中的一对点的最小割 则需要要找到树上两点简单路径上的最小边割掉即为答案*/

//复杂度(n^3*m)
#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;
const int MAXTALL = 8; //  (2<<MAXTALL) >= N
const int N = 510, M = 14010;
struct Edge {
        int to, capa, next;
} e[N << 1];
int h[N], sum = 0, n, m, now = 0;
int pdx[N], tdx[N], col[N];
int fa[MAXTALL + 1][N], mn[MAXTALL + 1][N], dep[N];

void add_edge1(int u, int v, int w) {
        e[++sum].to = v;
        e[sum].capa = w;
        e[sum].next = h[u];
        h[u] = sum;
}

namespace GHT {
        struct Edge {
                int to, capa, flow, next;
        } e[M];
        int h[N], sum = 1, s, t;
        int d[N], cur[N];
        bool vis[N];

        void add_edge2(int u, int v, int w) {
                e[++sum] = {v, w, 0, h[u]};
                h[u] = sum;
                e[++sum] = {u, w, 0, h[v]};
                h[v] = sum;
        }

        bool BFS() {
                queue<int> q;
                q.push(s);
                memset(vis, 0, sizeof(vis));
                vis[s] = 1;
                d[s] = 0;
                while (!q.empty()) {
                        int u = q.front();
                        q.pop();
                        for (int t = h[u]; t; t = e[t].next) {
                                int v = e[t].to;
                                if (!vis[v] && e[t].capa > e[t].flow) {
                                        d[v] = d[u] + 1;
                                        vis[v] = 1;
                                        q.push(v);
                                }
                        }
                }
                return vis[t];
        }

        int DFS(int u, int a) {
                if (u == t || a == 0) {
                        return a;
                }
                int res = 0, flow;
                for (int &t = cur[u]; t; t = e[t].next) {
                        int v = e[t].to;
                        if (d[v] != d[u] + 1) {
                                continue;
                        }
                        flow = DFS(v, min(a, e[t].capa - e[t].flow));
                        if (!flow) {
                                continue;
                        }
                        e[t].flow += flow;
                        e[t ^ 1].flow -= flow;
                        res += flow;
                        a -= flow;
                        if (a == 0) {
                                break;
                        }
                }
                return res;
        }

        int Dinic(int x, int y) {
                int flow = 0;
                s = x;
                t = y;
                for (int i = 0; i <= sum; i++) {
                        e[i].flow = 0;
                }
                while (BFS()) {
                        memcpy(cur, h, sizeof(h));
                        flow += DFS(s, INF);
                }
                return flow;
        }

        void dfs(int u) {
                col[u] = now;
                for (int t = h[u]; t; t = e[t].next)
                        if (e[t].capa > e[t].flow && col[e[t].to] != now) {
                                dfs(e[t].to);
                        }
        }

        void build(int l, int r) {
                if (l >= r) {
                        return;
                }
                int x = pdx[l], y = pdx[l + 1];
                int cut = Dinic(x, y);
                now++;
                dfs(x);
                int p = l, q = r;
                for (int i = l; i <= r; i++)
                        if (col[pdx[i]] == now) {
                                tdx[p++] = pdx[i];
                        } else {
                                tdx[q--] = pdx[i];
                        }
                for (int i = l; i <= r; i++) {
                        pdx[i] = tdx[i];
                }
                ::add_edge1(x, y, cut);
                ::add_edge1(y, x, cut);
                build(l, p - 1);
                build(q + 1, r);
        }
}

void dfs(int u, int la) { //LCA dfs
        for (int i = 1; i <= MAXTALL; i++) {
                fa[i][u] = fa[i - 1][fa[i - 1][u]];
                mn[i][u] = min(mn[i - 1][u], mn[i - 1][fa[i - 1][u]]);
        }
        for (int t = h[u]; t; t = e[t].next) {
                int v = e[t].to;
                if (v == la) {
                        continue;
                }
                dep[v] = dep[u] + 1;
                mn[0][v] = e[t].capa;
                fa[0][v] = u;
                dfs(v, u);
        }
}

int getcut(int x, int y) {  // find minedge
        int res = INF;
        if (dep[x] < dep[y]) {
                swap(x, y);
        }
        for (int i = MAXTALL; i >= 0; i--)
                if (dep[fa[i][x]] >= dep[y]) {
                        res = min(res, mn[i][x]);
                        x = fa[i][x];
                }
        if (x == y) {
                return res;
        }
        for (int i = MAXTALL; i >= 0; i--)
                if (fa[i][x] != fa[i][y]) {
                        res = min(res, mn[i][x]);
                        res = min(res, mn[i][y]);
                        x = fa[i][x];
                        y = fa[i][y];
                }
        res = min(res, min(mn[0][x], mn[0][y]));
        return res;
}

int main() {
        int u, v, w, q;
        scanf("%d%d", &n, &m);
        //memset(GHT::h, -1, sizeof(GHT::h));
        for (int i = 1; i <= m; i++) {
                scanf("%d%d%d", &u, &v, &w);
                GHT::add_edge2(u, v, w);
        }
        for (int i = 1; i <= n; i++) {
                pdx[i] = i;
        }
        GHT::build(1, n);
        dep[1] = 1;
        dfs(1, 0);
        for (scanf("%d", &q); q; q--) {
                scanf("%d%d", &u, &v);
                printf("%d\n", getcut(u, v));
        }
        return 0;
}
