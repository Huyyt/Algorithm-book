#define INF 0xfffffff
#define maxn 10025
#define min(a,b) (a<b?a:b)
int m, n, Time, cnt, top;
int dfn[maxn], block[maxn], low[maxn], Father[maxn], Stack[maxn];
vector<int> G[maxn];
void init()
{
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(block, 0, sizeof(block));
    memset(Father, 0, sizeof(Father));
    top = Time = cnt = 0;

    for(int i=0; i<=n; i++)
        G[i].clear();
}
void Tarjan(int u,int fa)
{
    dfn[u] = low[u] = ++Time;
    Father[u] = fa;
    Stack[top++] = u;
    int len = G[u].size(), v, k = 0;

    for(int i=0; i<len; i++)
    {
        v = G[u][i];
        if(v == fa && !k)
        {
            k ++;
            continue;
        }

        if(!low[v])
        {
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else
            low[u] = min(low[u], dfn[v]);
    }

    if(dfn[u] == low[u])
    {
        do
        {
            v = Stack[--top];
            block[v] = cnt;
        }while(u != v);
        cnt ++;
    }
}

void solve()
{
    int i, degree[maxn] = {0}, ans = 0;
    for(i=1; i<=n; i++)
    {
        if( !low[i] )
            Tarjan(i, i);
    }

    for(i=1; i<=n; i++)
    {
        int v = Father[i];
        if(block[i] != block[v])
        {
            degree[block[i] ] ++;
            degree[block[v] ] ++;
        }
    }

    for(i=0; i<cnt; i++)
    {
        if(degree[i] == 1)
            ans ++;
    }
    printf("%d\n", (ans+1)/2 );
}
int main()
{
    while(scanf("%d %d",&n, &m) != EOF)
    {
        init();
        while(m --)
        {
            int a, b;
            scanf("%d %d",&a, &b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        solve();
    }
    return0;
}
