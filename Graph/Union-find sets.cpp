//Union-find sets
int par[maxn], hs[maxn], int sz[maxn];
int cnt;
void init(int n)
{
        for (int i = 0; i <= n; i++)
        {
                par[i] = i, hs[i] = i, sz[i] = 1;
        }
}
int findpar(int x)
{
        return par[x] == x ? x : par[x] = findpar(par[x]);
}
void unite(int x, int y)
{
        x = findpar(x);
        y = findpar(y);
        if (x != y)
        {
                par[x] = y, sz[y] += sz[x];
        }
}
void del(int x)
{
        sz[findpar(hs[x])]--;
        hs[x] = ++cnt;
}
