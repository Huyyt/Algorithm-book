1.每次找一个未匹配的点出来增广
2.在增广过程中，如果相邻点是白点，或者是同一朵花中的节点，则直接跳过这个点
3.如果相邻点是一个未被匹配过的白点，证明找到了增广路，沿着原有的pre和match路径，对这一次的匹配结果进行更新
4.如果相邻点是一个被匹配过的白点，那么把这个点的匹配点丢进队列中，尝试能否让这个点的匹配点找到另外一个点进行匹配，从而可以增广。
(以上步骤同匈牙利算法)
5.如果相邻点是一个被匹配过的黑点，证明此时出现了奇环，我们需要将这个环缩成一个黑点。
具体的实现过程是：找到他们的最近花公共祖先，也就是他们的花根，同时，沿着当前这两个点一路到花根，将花上的所有节点全部染成黑点（因为一朵花都是黑点），
将原来的白点丢进栈中。同时，修改花上所有点的pre，此时，只剩下花根并不与花内的节点相匹配。

#include<bits/stdc++.h>
#define RG register
using namespace std;
typedef long long ll;
const int MAXN = 555;
const int MAXM = 255555;
int Head[MAXN], match[MAXN], pre[MAXN], father[MAXN], vis[MAXN], dfn[MAXN];
int n, m, ans, tim, ed = 1;
queue<int> Q;
struct Line {
        int v, next;
} e[MAXM];
inline void addedge(int u, int v) {
        e[ed] = (Line) {
                v, Head[u]
        };
        Head[u] = ed++;
}
int getfa(int x) {
        return x == father[x] ? x : father[x] = getfa(father[x]);
}
int lca(int u, int v) {
        ++tim;
        u = getfa(u);
        v = getfa(v);
        while (dfn[u] != tim) {
                dfn[u] = tim;
                u = getfa(pre[match[u]]);
                if (v) {
                        swap(u, v);
                }
        }
        return u;
}
void Blossom(int x, int y, int w) {
        while (getfa(x) != w) {
                pre[x] = y, y = match[x];
                if (vis[y] == 2) {
                        vis[y] = 1, Q.push(y);
                }
                if (getfa(x) == x) {
                        father[x] = w;
                }
                if (getfa(y) == y) {
                        father[y] = w;
                }
                x = pre[y];
        }
}
bool Aug(int S) {
        for (int i = 1; i <= n; ++i) {
                father[i] = i, vis[i] = pre[i] = 0;
        }
        while (!Q.empty()) {
                Q.pop();
        }
        Q.push(S);
        vis[S] = 1;
        while (!Q.empty()) {
                int u = Q.front();
                Q.pop();
                for (int i = Head[u]; i; i = e[i].next) {
                        int v = e[i].v;
                        if (getfa(u) == getfa(v) || vis[v] == 2) {
                                continue;
                        }
                        if (!vis[v]) {
                                vis[v] = 2;
                                pre[v] = u;
                                if (!match[v]) {
                                        for (int x = v, lst; x; x = lst) {
                                                lst = match[pre[x]], match[x] = pre[x], match[pre[x]] = x;
                                        }
                                        return true;
                                }
                                vis[match[v]] = 1, Q.push(match[v]);
                        } else {
                                int w = lca(u, v);
                                Blossom(u, v, w);
                                Blossom(v, u, w);
                        }
                }
        }
        return false;
}
void init(int x) {
        ans = tim = 0;
        ed = 1;
        for (int i = 0; i <= x + 1; i++) {
                vis[i] = dfn[i] = pre[i] = match[i] = Head[i] = 0;
                father[i] = i;
        }
}
int main() {
        while (scanf("%d %d", &n, &m) == 2) {
                int u, v;
                init(n);
                for (int i = 1; i <= m; ++i) {
                        scanf("%d %d", &u, &v);
                        addedge(u, v);
                        addedge(v, u);
                }
                for (int i = 1; i <= n; ++i)
                        if (!match[i]) {
                                ans += Aug(i);
                        }
                printf("%d\n", ans);
                for (int i = 1; i <= n; ++i) {
                        printf("%d ", match[i]);
                }
                puts("");
        }
        return 0;
}
