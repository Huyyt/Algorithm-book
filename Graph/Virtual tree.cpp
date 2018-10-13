//virtual tree
//倍增版//
int n, jumpfa[MAXN][20], dfn[MAXN], deep[MAXN];
int cnt = 0, xutot = 0, xusta[MAXN], k[MAXN];
bool del[MAXN];
ll minedge[MAXN], finalans[MAXN];
void dfs1(int x, int fa) {
        jumpfa[x][0] = fa;
        dfn[x] = ++cnt;
        for (int i = 1; i <= 18; i++) {
                jumpfa[x][i] = jumpfa[jumpfa[x][i - 1]][i - 1];
        }
        for (int v, i = Head[x]; i; i = nxt[i]) {
                if (v = to[i], v != fa) {
                        deep[v] = deep[x] + 1;
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
        for (int i = Head[x]; i; i = nxt[i]) {
                if (to[i] != fa) {
                        get_ans(to[i], x);
                }
        }
        Head[x] = 0;
}
inline bool cmp(int a, int b) {
        return dfn[a] < dfn[b];
}
void init() {
        minedge[1] = LLONG_MAX;
        deep[1] = 1;
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
                xutot = 0;
                read(number);
                for (int i = 1; i <= number; i++) {
                        read(k[i]);
                }
                sort(k + 1, k + number + 1, cmp);
                for (int i = 2; i <= number; i++) {
                        if (lca(k[i], k[nowtot]) != k[nowtot]) {
                                k[++nowtot] = k[i];
                        }
                }
                number = nowtot;
                xusta[++xutot] = 1;
                for (int i = 1; i <= number; i++) {
                        int grand = lca(xusta[xutot], k[i]);
                        while (1) {
                                if (deep[xusta[xutot - 1]] <= deep[grand]) { //分别处在两个子树，grand深度更大！！！
                                        addedge(grand, xusta[xutot], 0);
                                        xutot--;
                                        if (xusta[xutot] != grand) {
                                                xusta[++xutot] = grand;
                                        }
                                        break;
                                }
                                addedge(xusta[xutot - 1], xusta[xutot], 0);
                                xutot--;
                        }
                        if (xusta[xutot] != k[i]) {
                                xusta[++xutot] = k[i];        //在同一子树
                        }
                }
                xutot--;
                while (xutot) {
                        addedge(xusta[xutot], xusta[xutot + 1], 0);
                        xutot--;
                }
                get_ans(1, 0);
                cout << finalans[1] << endl;
        }
        return 0;
}
