//Off-line LCA
int fa[MAXN], d[MAXN], vis[MAXN], LCA[MAXQ], ans[MAXQ];
vector<int> query[MAXQ], query_id[MAXQ];
void add_query(int x, int y, int id)
{
        query[x].push_back(y), query_id[x].push_back(id);
        query[y].push_back(x), query_id[y].push_back(id);
}
int get(int x)
{
        if (x == fa[x])
        {
                return x;
        }
        return fa[x] = get(fa[x]);
}
void tarjan(int x)
{
        vis[x] = 1;
        for (int v, i = Head[x]; i; i = nxt[i])
        {
                v = to[i];
                if (vis[v])
                {
                        continue;
                }
                d[v] = d[x] + value[i];
                tarjan(v);
                fa[v] = x;
        }
        for (int i = 0; i < query[x].size(); i++)
        {
                int v = query[x][i], id = query_id[x][i];
                if (vis[v] == 2)
                {
                        LCA[id] = get(v);
                        ans[id] = min(ans[id], d[x] + d[v] - 2 * d[LCA[id]]);
                }
        }
        vis[x] = 2;
}
int n, m;
int u, v, z;
int main()
{
        int T;
        scanf("%d", &T);
        while (T--)
        {
                scanf("%d %d", &n, &m);
                for (int i = 1; i <= n; i++)
                {
                        vis[i] = Head[i] = 0, fa[i] = i;
                        query[i].clear(), query_id[i].clear();
                }
                ed = 0;
                for (int i = 1; i < n; i++)
                {
                        scanf("%d %d %d", &u, &v, &z);
                        addedge(u, v, z), addedge(v, u, z);
                }
                for (int i = 1; i <= m; i++)
                {
                        scanf("%d %d", &u, &v);
                        if (u == v)
                        {
                                ans[i] = 0;
                                LCA[i] = u;
                        }
                        else
                        {
                                add_query(u, v, i);
                                ans[i] = 1 << 30;
                        }
                }
                tarjan(1);
                for (int i = 1; i <= m; i++)
                {
                        printf("%d\n", ans[i]);
                }
        }
        return 0;
}
