#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#define SZ 131072
#define pli pair<long long,int>
using namespace std;
int n, m, Route[101000], PP[101000], ord[101000];
vector<int>E[101000], L[101000], Num[101000], T[101000];
priority_queue<pli>PQ;
struct Edge
{
        int a, b, c;
} Ed[101000];
int Path[101000], chk[101000];
long long D[101000], D2[101000];
void Ins(int a, long long d, int pp)
{
        if (D[a] <= d)
        {
                return;
        }
        D[a] = d;
        Path[a] = pp;
        PQ.push(pli{ -d, a });
}
void Dijk(int st)
{
        int i, a;
        for (i = 1; i <= n; i++)
        {
                D[i] = 1e18, Path[i] = -1;
        }
        Ins(st, 0, 0);
        while (!PQ.empty())
        {
                pli tp = PQ.top();
                PQ.pop();
                if (D[tp.second] != -tp.first)
                {
                        continue;
                }
                a = tp.second;
                for (i = 0; i < E[a].size(); i++)
                {
                        Ins(E[a][i], D[a] + L[a][i], Num[a][i]);
                }
        }
}
void DFS(int a, int pp)
{
        int i;
        if (Route[a])
        {
                pp = Route[a];
        }
        PP[a] = pp;
        for (i = 0; i < T[a].size(); i++)
        {
                DFS(T[a][i], pp);
        }
}
int cnt;
long long IT[SZ + SZ];
void Put(int b, int e, long long x)
{
        b += SZ, e += SZ;
        while (b <= e)
        {
                IT[b] = min(IT[b], x);
                IT[e] = min(IT[e], x);
                b = (b + 1) >> 1, e = (e - 1) >> 1;
        }
}
void Add(int a, int b, int c)
{
        if (D[a] > 5e17 || D2[b] > 5e17)
        {
                return;
        }
        if (!PP[a] || !PP[b])
        {
                return;
        }
        if (PP[a] > PP[b])
        {
                Put(PP[b], PP[a] - 1, D[a] + D2[b] + c);
        }
}
int main()
{
        int i, a, b, c;
        scanf("%d%d", &n, &m);
        for (i = 1; i < SZ + SZ; i++)
        {
                IT[i] = 1e18;
        }
        for (i = 0; i < m; i++)
        {
                scanf("%d%d%d", &a, &b, &c);
                E[b].push_back(a);
                L[b].push_back(c);
                Num[b].push_back(i);
                Ed[i] = { a, b, c };
        }
        Dijk(2);
        for (i = 1; i <= n; i++)
        {
                D2[i] = D[i], E[i].clear(), L[i].clear(), Num[i].clear();
        }
        for (i = 0; i < m; i++)
        {
                a = Ed[i].a, b = Ed[i].b, c = Ed[i].c;
                E[a].push_back(b);
                L[a].push_back(c);
                Num[a].push_back(i);
        }
        Dijk(1);
        a = 2;
        while (a != 1)
        {
                Route[a] = ++cnt;
                chk[Path[a]] = 1;
                a = Ed[Path[a]].a;
        }
        Route[a] = ++cnt;
        for (i = 2; i <= n; i++)
        {
                if (Path[i] != -1)
                {
                        T[Ed[Path[i]].a].push_back(i);
                }
        }
        DFS(1, 0);
        for (i = 0; i < m; i++)
        {
                if (chk[i])
                {
                        continue;
                }
                Add(Ed[i].a, Ed[i].b, Ed[i].c);
        }
        for (i = 0; i < m; i++)
        {
                if (chk[i])
                {
                        int t = SZ + min(Route[Ed[i].a], Route[Ed[i].b]);
                        long long rr = 1e18;
                        while (t)
                        {
                                rr = min(rr, IT[t]);
                                t >>= 1;
                        }
                        if (rr == D[2])
                        {
                                printf("SOSO\n");
                        }
                        else
                        {
                                printf("SAD\n");
                        }
                }
                else
                {
                        if (D[Ed[i].b] + D2[Ed[i].a] + Ed[i].c < D[2])
                        {
                                printf("HAPPY\n");
                        }
                        else
                        {
                                printf("SOSO\n");
                        }
                }
        }
}
