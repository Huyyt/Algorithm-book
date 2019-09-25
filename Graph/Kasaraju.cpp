//Kasaraju
const int MAXN = 100005;
vector<int> G[MAXN], G2[MAXN];
vector<int> S;
int vis[MAXN], sccno[MAXN], scc_cnt;
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
        memset(sccno, 0, sizeof(sccno));
        memset(vis, 0, sizeof(sccno));
        for (int i = 1; i <= n; i++) {
                if (!vis[i]) {
                        dfs1(i);
                }
        }
        for (int i = S.size() - 1; i >= 0; i--) {
                if (!sccno[S[i]]) {
                        scc_cnt++;
                        dfs2(S[i]);
                }
        }
}
int main () {
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= m; i++) {
                int u, v;
                scanf("%d %d", &u, &v);
                G[u].push_back(v);
                G2[v].push_back(u);
        }
        find_scc(n);
        for (int i = 1; i <= n; i++) {
                cout << sccno[i] << " ";
        }
        cout << endl;
}

