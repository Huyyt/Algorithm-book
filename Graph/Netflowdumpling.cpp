//Netflow dumpling
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1050;
const int MAXM = 1000;
const int INF = 1000000050;
int Head[MAXN], cur[MAXN], lev[MAXN], to[MAXM], nxt[MAXM], f[MAXM], ed, S, T;
inline void addedge(int u, int v, int cap) {
        to[++ed] = v;
        nxt[ed] = Head[u];
        Head[u] = ed;
        f[ed] = cap;
        to[++ed] = u;
        nxt[ed] = Head[v];
        Head[v] = ed;
        f[ed] = 0;
        return;
}
inline bool BFS() {
        int u;
        memset(lev, -1, sizeof(lev));
        queue<int>q;
        lev[S] = 0;
        q.push(S);
        while (q.size()) {
                u = q.front();
                q.pop();
                for (int i = Head[u]; i; i = nxt[i])
                        if (f[i] && lev[to[i]] == -1) {
                                lev[to[i]] = lev[u] + 1;
                                q.push(to[i]);
                                /*
                                if (to[i] == T)
                                {
                                        return 1;
                                }
                                magic one way optimize
                                */
                        }
        }
        memcpy(cur, Head, sizeof Head);
        return lev[T] != -1;
}
inline int DFS(int u, int maxf) {
        if (u == T || !maxf) {
                return maxf;
        }
        int cnt = 0;
        for (int &i = cur[u], tem; i; i = nxt[i])
                if (f[i] && lev[to[i]] == lev[u] + 1) {
                        tem = DFS(to[i], min(maxf, f[i]));
                        maxf -= tem;
                        f[i] -= tem;
                        f[i ^ 1] += tem;
                        cnt += tem;
                        if (!maxf) {
                                break;
                        }
                }
        if (!cnt) {
                lev[u] = -1;
        }
        return cnt;
}
int Dinic() {
        int ans = 0;
        while (BFS()) {
                ans += DFS(S, 2147483647);
        }
        return ans;
}
void init(int SS, int TT) {
        memset(Head, 0, sizeof(Head));
        ed = 1;
        S = SS;
        T = TT;
        return;
}
int main() {
        int n, m;
        int u, v, c;
        while (scanf("%d %d", &n, &m) == 2) {
                init(1, m);
                for (int i = 1; i <= n; i++) {
                        scanf("%d %d %d", &u, &v, &c);
                        addedge(u, v, c);
                }
                printf("%d\n", Dinic());
        }
        return 0;
}
