//Mcmf LargeDumpling
#include<bits/stdc++.h>
using namespace std;
const int INF = 0x7f7f7f7f;
const int MAXN = 505, MAXM = 1300;
int Head[MAXN], cur[MAXN], lev[MAXN], to[MAXM << 1], nxt[MAXM << 1], f[MAXM << 1], mono[MAXM << 1], ed = 1, S, T;
int pre[MAXN];
bool exist[MAXN];
void init() {
        memset(Head, 0, sizeof(Head));
        ed = 1;
        S = 498;
        T = 499;
        return;
}
void addedge(int u, int v, int cap, int val) {
        to[++ed] = v;
        nxt[ed] = Head[u];
        Head[u] = ed;
        f[ed] = cap;
        mono[ed] = val;
        to[++ed] = u;
        nxt[ed] = Head[v];
        Head[v] = ed;
        f[ed] = 0;
        mono[ed] = -1 * val;
        return;
}
bool BFS() {
        int u;
        queue<int>q;
        memset(exist, false, sizeof(exist));
        memset(lev, 127, sizeof(lev));
        lev[S] = pre[S] = 0;
        q.push(S);
        while (q.size()) {
                u = q.front();
                q.pop();
                exist[u] = false;
                for (int i = Head[u]; i; i = nxt[i])
                        if (f[i] && lev[u] + mono[i] < lev[to[i]]) {
                                lev[to[i]] = lev[u] + mono[i];
                                pre[to[i]] = i;
                                if (!exist[to[i]]) {
                                        exist[to[i]] = true;
                                        q.push(to[i]);
                                }
                        }
        }
        memcpy(cur, Head, sizeof(Head));
        return lev[T] != INF;
}
int DFS(int u, int maxf) {
        if (u == T || !maxf) {
                return maxf;
        }
        exist[u] = true;
        int cnt = 0;
        for (int &i = cur[u], tem; i; i = nxt[i])
                if (f[i] && lev[u] + mono[i] == lev[to[i]]) {
                        if (exist[to[i]]) {
                                continue;
                        }
                        tem = DFS(to[i], min(f[i], maxf));
                        maxf -= tem;
                        f[i] -= tem;
                        f[i ^ 1] += tem;
                        cnt += tem;
                        if (!maxf) {
                                break;
                        }
                }
        if (!cnt) {
                lev[u] = -1 * INF;
        }
        exist[u] = false;
        return cnt;
}
int Augment() {
        int delta = INF;
        for (int i = pre[T]; i; i = pre[to[i ^ 1]])
                if (f[i] < delta) {
                        delta = f[i];
                }
        for (int i = pre[T]; i; i = pre[to[i ^ 1]]) {
                f[i] -= delta;
                f[i ^ 1] += delta;
        }
        return delta * lev[T];
}
int MCMF() {
        int ans = 0;
        memset(exist, false, sizeof(exist));
        while (BFS())
                //ans+=DFS(S,INF)*lev[T];
        {
                ans += Augment();
        }
        return ans;
}
int main() {
        init();
        return 0;
}
