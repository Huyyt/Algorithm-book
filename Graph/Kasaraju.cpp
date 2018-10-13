//Kasaraju
vector<int> G[maxn], G2[maxn];
vector<int> S;
int vis[maxn], sccno[maxn], scc_cnt;
void dfs1(int u) {
        if (vis[u]) {
                return ;
        }
        vis[u] = 1;
        for (auto x : G[u]) {
                dfs1(x);
        }
        S.push_back(u);
}
void dfs2(int u) {
        if (sccno[u]) {
                return ;
        }
        sccno[u] = scc_cnt;
        for (auto x : G2[u]) {
                dfs2(x);
        }
}
void find_scc(int n) {
        scc_cnt = 0;
        S.clear();
        mem(sccno, 0), mem(vis, 0);
        for (int i = 1; i <= n; i++) {
                dfs1(i);
        }
        for (int i = n; i >= 1; i--) {
                if (!sccno[S[i]]) {
                        scc_cnt++;
                        dfs2(S[i]);
                }
        }
}
