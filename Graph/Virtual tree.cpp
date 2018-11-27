//virtual tree
/*Huyyt*/
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const double eps = 1e-8;
const int dir[8][2] = {{0, 1}, {1, 0}, {0, -1}, { -1, 0}, {1, 1}, {1, -1}, { -1, -1}, { -1, 1}};
const int mod = 1e9 + 7, gakki = 5 + 2 + 1 + 19880611 + 1e9;
const int MAXN = 3e5 + 5, MAXM = 3e5 + 5, MAXQ = 100010, INF = 1e9;
const ll LLINF = (1LL << 50);
int to[MAXM << 1], nxt[MAXM << 1], Head[MAXN], tot = 1;
ll cost[MAXM << 1];
struct node {
        int u, v;
        ll c;
} edge[MAXM << 1];
inline void addedge(int u, int v, int c) {
        if (u == v) {
                return ;
        }
        to[++tot] = v;
        nxt[tot] = Head[u];
        cost[tot] = c;
        Head[u] = tot;
}
template <typename T> inline void read(T&x) {
        char cu = getchar();
        x = 0;
        bool fla = 0;
        while (!isdigit(cu)) {
                if (cu == '-') {
                        fla = 1;
                }
                cu = getchar();
        }
        while (isdigit(cu)) {
                x = x * 10 + cu - '0', cu = getchar();
        }
        if (fla) {
                x = -x;
        }
}
int n;
int jumpfa[MAXN][20];
int jumpdis[MAXN][20];
int dfn[MAXN], deep[MAXN];
int cnt = 0;
int top;
int xutot = 0;
int s[MAXN];
int k[MAXN];
bool del[MAXN];
ll minedge[MAXN];
ll finalans[MAXN];
void dfs1(int x, int fa) {
        jumpfa[x][0] = fa;
        dfn[x] = ++cnt;
        for (int i = 1; i <= 18; i++) {
                jumpfa[x][i] = jumpfa[jumpfa[x][i - 1]][i - 1];
        }
        for (int v, i = Head[x]; i; i = nxt[i]) {
                if (v = to[i], v != fa) {
                        deep[v] = deep[x] + 1;
                        minedge[v] = min(minedge[x], cost[i]);
                        dfs1(v, x);
                }
        }
}
inline int lca(int x, int y) {
        if (deep[x] < deep[y]) {
                swap(x, y);
        }
        int t = 0;
        while ((1 << t) <= deep[x]) {
                t++;
        }
        t--;
        for (int i = t; i >= 0; i--) {
                if (deep[x] - (1 << i) >= deep[y]) {
                        x = jumpfa[x][i];
                }
        }
        if (x == y) {
                return x;
        }
        for (int i = t; i >= 0; i--) {
                if (jumpfa[x][i] != jumpfa[y][i]) {
                        x = jumpfa[x][i], y = jumpfa[y][i];
                }
        }
        return jumpfa[x][0];
}
inline void get_ans(int x, int fa) {
        ll anser = 0;
        finalans[x] = minedge[x];
        for (int i = Head[x]; i; i = nxt[i]) {
                if (to[i] != fa) {
                        get_ans(to[i], x);
                        anser += finalans[to[i]];
                }
        }
        Head[x] = 0;
        if (!anser || del[x]) {
                finalans[x] = minedge[x];
        } else {
                finalans[x] = min(finalans[x], anser);
        }
}
inline bool cmp(int a, int b) {
        return dfn[a] < dfn[b];
}
void init() {
        minedge[1] = LLONG_MAX;
        deep[1] = 1;
}
inline void insert_point(int x) { ///½¨Á¢ÐéÊ÷
        if (top == 0) {
                s[++top] = x;
                return ;
        }
        int grand = lca(x, s[top]);
        if (grand == s[top]) {
                s[++top] = x;
                return ;
        }
        while (top >= 1 && dfn[s[top - 1]] >= dfn[grand]) {
                addedge(s[top - 1], s[top], 0);
                top--;
        }
        if (grand != s[top]) {
                addedge(grand, s[top], 0);
                s[top] = grand;
        }
        s[++top] = x;
}
int main() {
        int u, v, c;
        read(n);
        for (int i = 1; i <= n - 1; i++) {
                read(u), read(v), read(c);
                edge[i].u = u, edge[i].v = v, edge[i].c = c;
                addedge(u, v, c);
                addedge(v, u, c);
        }
        init();
        dfs1(1, 0);
        mem(Head, 0);
        int m, number;
        read(m);
        while (m--) {
                tot = 1;
                int nowtot = 1;
                top = 0;
                xutot = 0;
                read(number);
                for (int i = 1; i <= number; i++) {
                        read(k[i]);
                        del[k[i]] = 1;
                }
                k[++number] = 1;
                sort(k + 1, k + number + 1, cmp);
                for (int i = 1; i <= number; i++) {
                        insert_point(k[i]);
                }
                while (top > 1) {
                        addedge(s[top - 1], s[top], 0);
                        top--;
                }
                get_ans(1, 0);
                printf("%lld\n", finalans[1]);
                for (int i = 1; i <= number; i++) {
                        del[k[i]] = 0;
                }
        }
        return 0;
}

