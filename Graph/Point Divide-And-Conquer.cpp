//树上距离<=K的点对数
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;
int to[MAXM << 1], nxt[MAXM << 1], Head[MAXN], ed = 1;
int cost[MAXM << 1];
inline void addedge(int u, int v, int c) {
        to[++ed] = v;
        cost[ed] = c;
        nxt[ed] = Head[u];
        Head[u] = ed;
}
inline void ADD(int u, int v, int c) {
        addedge(u, v, c);
        addedge(v, u, c);
}
int n, k, anser;
int sz[MAXN], f[MAXN], dep[MAXN], sumsz, root;
bool vis[MAXN];
int o[MAXN], cnt;
void getroot(int x, int fa) {
        sz[x] = 1;
        f[x] = 0;
        for (int i = Head[x]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa || vis[v]) {
                        continue;
                }
                getroot(v, x);
                sz[x] += sz[v];
                f[x] = max(f[x], sz[v]);
        }
        f[x] = max(f[x], sumsz - sz[x]);
        if (f[x] < f[root]) {
                root = x;
        }
}
void getdeep(int x, int fa) {
        o[++cnt] = dep[x];
        for (int i = Head[x]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa || vis[v]) {
                        continue;
                }
                dep[v] = dep[x] + cost[i];
                getdeep(v, x);
        }
}
int calc(int x, int d) {
        cnt = 0;
        dep[x] = d;
        getdeep(x, 0);
        sort(o + 1, o + cnt + 1);
        int l = 1, r = cnt, ansnow = 0;
        while (l < r) {
                if (o[l] + o[r] <= k) {
                        ansnow += r - l, l++;
                } else {
                        r--;
                }
        }
        return ansnow;
}
void solve(int x) {
        anser += calc(x, 0); //满足Depth(i)+Depth(j)<=k的对数
        vis[x] = 1;
        int totsz = sumsz;
        for (int i = Head[x]; i; i = nxt[i]) {
                int v = to[i];
                if (vis[v]) {
                        continue;
                }
                anser -= calc(v, cost[i]);//满足Depth(i)+Depth(j)<=k且Belong(i)=Belong(j)的对数
                root = 0;
                sumsz = sz[v] > sz[x] ? totsz - sz[x] : sz[v];
                getroot(v, 0);
                solve(root);
        }
}
int main() {
        while (scanf("%d %d", &n, &k) && (n + k)) {
                cnt = anser = 0;
                memset(Head, 0, sizeof(Head));
                memset(vis, 0, sizeof(vis));
                ed = 1;
                int u, v, c;
                for (int i = 1; i < n; i++) {
                        scanf("%d %d %d", &u, &v, &c);
                        ADD(u, v, c);
                }
                root = 0, sumsz = f[0] = n;
                getroot(1, 0);
                solve(root);
                printf("%d\n", anser);
        }
        return 0;
}
