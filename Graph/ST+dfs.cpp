//ST+dfs
int depth[MAXN << 1], ver[MAXN << 1], STdfn[MAXN], dfs_clock = 0;
int STdp[MAXN << 1][25];
void dfs(int x, int fa, int deep) {
        ver[++dfs_clock] = x;
        STdfn[x] = dfs_clock;
        depth[dfs_clock] = deep;
        for (int i = Head[x]; i; i = nxt[i]) {
                int v = to[i];
                if (v != fa) {
                        dfs(v, x, deep + 1);
                        ver[++dfs_clock] = x;
                        depth[dfs_clock] = deep;
                }
        }
}
void ST(int n) {
        for (int i = 1; i <= n; i++) {
                STdp[i][0] = i;
        }
        for (int j = 1; (1 << j) <= n; j++) {
                for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                        STdp[i][j] = depth[STdp[i][j - 1]] < depth[STdp[i + (1 << (j - 1))][j - 1]] ? STdp[i][j - 1] : STdp[i + (1 << (j - 1))][j - 1];
                }
        }
}
int RMQ(int l, int r) {
        int k = (int)(log((double)(r - l + 1)) / log(2.0));
        return depth[STdp[l][k]] < depth[STdp[r - (1 << k) + 1][k]] ? STdp[l][k] : STdp[r - (1 << k) + 1][k];
}
int LCA(int u, int v) {
        int a = STdfn[u], b = STdfn[v];
        if (a > b) {
                swap(a, b);
        }
        int res = RMQ(a, b);
        return ver[res];
}
int main() {
        int root;
        int n, m, u, v;
        for (int i = 1; i <= n; i++) {
                addedge(i, u), addedge(u, i);
        }
        dfs(root, 0, 1);
        ST(dfs_clock);
        return 0;
}
