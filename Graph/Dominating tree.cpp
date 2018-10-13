//Dominating tree
int dfn[MAXN], idom[MAXN], sdom[MAXN];
int son[MAXN], id[MAXN], fa[MAXN], f[MAXN];
int ans[MAXN];
int cnt;
int n, m;
vector<int> DAGTree[MAXN], DomiTree[MAXN];
inline int findfather(int x) {
        if (f[x] == x) {
                return x;
        }
        int y = findfather(f[x]);
        if (sdom[son[x]] > sdom[son[f[x]]]) {
                son[x] = son[f[x]];
        }
        return  f[x] = y;
}
void dfs(int u) {
        id[dfn[u] = ++cnt] = u;
        for (int v, i = Head[u]; i; i = nxt[i]) {
                v = to[i];
                if (!dfn[v]) {
                        dfs(v), fa[dfn[v]] = dfn[u];
                }
        }
}
inline void Lengauer_Tarjan(int s) { //
        for (int i = 1; i <= n; i++) {
                f[i] = sdom[i] = son[i] = fa[i] = i;
                dfn[i] = 0;
        }
        cnt = 0, dfs(s);
        int k, x;
        for (int i = cnt; i > 1; i--) {
                for (int v, j = 0; j < DAGTree[id[i]].size(); j++) {
                        if (v = DAGTree[id[i]][j], dfn[v]) {
                                findfather(k = dfn[v]), sdom[i] = sdom[i] < sdom[son[k]] ? sdom[i] : sdom[son[k]];
                        }
                }
                DomiTree[sdom[i]].push_back(i), f[i] = x = fa[i];
                for (int v, j = 0; j < DomiTree[f[i]].size(); j++) {
                        v = DomiTree[f[i]][j], findfather(k = v), idom[k] = sdom[son[k]] < x ? son[k] : x;
                }
                DomiTree[x].clear();
        }
        for (int i = 2; i <= cnt; DomiTree[id[idom[i]]].push_back(id[i]), i++) {
                if (idom[i] != sdom[i]) {
                        idom[i] = idom[idom[i]];
                }
        }
}
void get_ans(int u) {
        dp[u] = 1;
        for (int v, i = 0; i < DomiTree[u].size(); i++) {
                v = DomiTree[u][i];
                get_ans(v);
                dp[u] += dp[v];
        }
        if (du[u] == 1) {
                ans[preedge[u]] = dp[u];
        }
}
int main() {
        tot = 1;
        mem(Head, 0);
        for (int i = 1; i <= 2 * m; i++) {
                if (dis[edge[i].v] == dis[edge[i].u] + edge[i].c) {
                        chose[i] = true;
                        addedge(edge[i].u, edge[i].v, 0);
                        du[edge[i].v]++;
                        preedge[edge[i].v] = (i + 1) / 2;
                        DAGTree[edge[i].v].push_back(edge[i].u);
                }
        }
        Lengauer_Tarjan(1);
        get_ans(1);
        for (int i = 1; i <= m; i++) {
                cout << ans[i] << endl;
        }
        return 0;
}
