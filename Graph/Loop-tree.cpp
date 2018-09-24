//Loop-tree
/*Huyyt*/
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define pb push_back
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN = 1e6 + 5, MAXM = 1e6 + 5;
int to[MAXM << 1], nxt[MAXM << 1], Head[MAXN], ed = 1;
int value[MAXM << 1];
int i, v;
inline void addedge(int u, int v, int val)
{
        to[++ed] = v;
        nxt[ed] = Head[u];
        value[ed] = val;
        Head[u] = ed;
}
inline void read(int &v)
{
        v = 0;
        char c = 0;
        int p = 1;
        while (c < '0' || c > '9')
        {
                if (c == '-')
                {
                        p = -1;
                }
                c = getchar();
        }
        while (c >= '0' && c <= '9')
        {
                v = (v << 3) + (v << 1) + c - '0';
                c = getchar();
        }
        v *= p;
}
bool circle[MAXN];
int vis[MAXN], cnt;
int nnxt[MAXN], nxtcircle[MAXN];
int que[MAXN << 1];
ll dpd[MAXN], sum[MAXN << 1], pre[MAXN];
ll sa[MAXN], ansnow, anser;
stack<int> sk;
void dfs(int x, int pre)
{
        vis[x] = 1;
        for (int v, i = Head[x]; i; i = nxt[i])
        {
                v = to[i];
                if (pre != -1 && i == (pre ^ 1))
                {
                        continue;
                }
                if (vis[v] == 1)
                {
                        circle[x] = true;
                        nxtcircle[x] = nnxt[x] = i;
                        int cur;
                        cur = to[nxtcircle[x]];
                        while (cur != x)
                        {
                                circle[cur] = true;
                                nxtcircle[cur] = nnxt[cur];
                                cur = to[nxtcircle[cur]];
                        }
                }
                else if (vis[v] == 2)
                {
                        continue;
                }
                else
                {
                        nnxt[x] = i;
                        dfs(v, i);
                }
        }
        vis[x] = 2;
}
void ZJdp(int x)
{
        vis[x] = 1;
        for (int v, i = Head[x]; i; i = nxt[i])
        {
                v = to[i];
                if (vis[v])
                {
                        continue;
                }
                ZJdp(v);
                if (!circle[v])
                {
                        ansnow = max(ansnow, dpd[x] + dpd[v] + value[i]);
                        dpd[x] = max(dpd[x], dpd[v] + value[i]);
                }

        }
}
int main()
{
        int n;
        int u;
        read(n);
        for (i = 1; i <= n; i++)
        {
                read(u), read(v);
                addedge(i, u, v), addedge(u, i, v);
        }
        for (i = 1; i <= n; i++)
        {
                if (!vis[i])
                {
                        dfs(i, -1);
                }
        }
        mem(vis, 0);
        int top, tail, et, cur;
        for (i = 1; i <= n; i++)
        {
                if (circle[i])
                {
                        if (!vis[i])
                        {
                                ansnow = 0;
                                ZJdp(i);
                                top = tail = cnt = 0;
                                que[tail++] = 0;
                                cur = to[nxtcircle[i]];
                                sa[cnt] = dpd[i];
                                pre[cnt++] = value[nxtcircle[i]];
                                while (cur != i)
                                {
                                        sa[cnt] = dpd[cur];
                                        pre[cnt++] = value[nxtcircle[cur]];
                                        cur = to[nxtcircle[cur]];
                                }
                                for (et = 1; et < (cnt << 1); et++)
                                {
                                        sum[et] = sum[et - 1] + pre[(et - 1) >= cnt ? (et - 1 - cnt) : (et - 1)];
                                }
                                for (et = 1; et < (cnt << 1); ++et)
                                {
                                        while (top < tail && et - que[top] >= cnt)
                                        {
                                                ++top;
                                        }
                                        u = que[top];
                                        ansnow = max(ansnow, sa[et >= cnt ? et - cnt : et] + sa[u >= cnt ? u - cnt : u] + sum[et] - sum[u]);
                                        while (top < tail && sa[et >= cnt ? et - cnt : et] >= sa[que[tail - 1] >= cnt ? que[tail - 1] - cnt : que[tail - 1]] + sum[et] - sum[que[tail - 1]])
                                        {
                                                --tail;
                                        }
                                        que[tail++] = et;
                                }
                                anser += ansnow;
                        }
                }
        }
        printf("%lld", anser);
        return 0;
}
