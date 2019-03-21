int n, cc[SZ], col[SZ], ks[SZ], anss[SZ];
int sz[SZ], son[SZ];
int skip = 0;
void gs(int x, int f = 0) {
        sz[x] = 1;
        for esb(x, e, b) {
                if (b == f) {
                        continue;
                }
                gs(b, x);
                sz[x] += sz[b];
                if (sz[b] > sz[son[x]]) {
                        son[x] = b;
                }
        }
}
void edt(int x, int f, int v) {
        cc[col[x]] += v;
        for esb(x, e, b)
                if (b != f && b != skip) {
                        edt(b, x, v);
                }
}
void dfs(int x, int f = 0, bool kep = 0) {
        for esb(x, e, b)
                if (b != f && b != son[x]) {
                        dfs(b, x);
                }
        if (son[x]) {
                dfs(son[x], x, 1), skip = son[x];
        }
        edt(x, f, 1);
        anss[x] = cc[ks[x]];
        skip = 0;
        if (!kep) {
                edt(x, f, -1);
        }
}
