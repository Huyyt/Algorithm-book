//HK
const int N = 1e6 + 10;
int n1, n2;
vector<int> g[N];
int linkx[N], linky[N];
int que[N * 5];
int head, tail;
int dx[N], dy[N];
bool vis[N];
bool find(int u)
{
        for (int i = 0; i < g[u].size(); i ++)
                if (! vis[g[u][i]] && dy[g[u][i]] == dx[u] + 1)
                {
                        vis[g[u][i]] = true;
                        if (! linky[g[u][i]] || find(linky[g[u][i]]))
                        {
                                linkx[u] = g[u][i];
                                linky[g[u][i]] = u;
                                return true;
                        }
                }
        return false;
}
int matching()
{
        memset(linkx, 0, (n1 + 5) << 2);
        memset(linky, 0, (n2 + 5) << 2);
        int ans = 0;
        while (true)
        {
                bool flag = false;
                head = 1, tail = 0;
                memset(dx, 0, (n1 + 5) << 2);
                memset(dy, 0, (n2 + 5) << 2);
                for (int i = 1; i <= n1; i ++)
                        if (! linkx[i])
                        {
                                que[++tail] = i;
                        }
                while (head <= tail)
                {
                        int u = que[head++];
                        for (int i = 0; i < g[u].size(); i ++)
                                if (! dy[g[u][i]])
                                {
                                        dy[g[u][i]] = dx[u] + 1;
                                        if (linky[g[u][i]])
                                        {
                                                dx[linky[g[u][i]]] = dy[g[u][i]] + 1;
                                                que[++tail] = linky[g[u][i]];
                                        }
                                        else
                                        {
                                                flag = true;
                                        }
                                }
                }
                if (! flag)
                {
                        break;
                }
                memset(vis, 0, max(n1, n2) + 5);
                for (int i = 1; i <= n1; i ++)
                        if (! linkx[i] && find(i))
                        {
                                ans ++;
                        }
        }
        return ans;
}
int n, m, a, b;
int main()
{
        while (~ scanf("%d%d%d%d", &n, &m, &a, &b))
        {
                n1 = m;
                n2 = 2 * n ;
                for (int i = 1; i <= m; i ++)
                {
                        scanf("%d%d", &x, &y);
                        g[i].clear();
                }
                int ans = matching();
        }
}
