//Mcmf LargeDumpling
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef int JQK;

const int INF = 0x7f7f7f7f;

const int MAXN = 505, MAXM = 1300;
int Head[MAXN], cur[MAXN], to[MAXM << 1], nxt[MAXM << 1], f[MAXM << 1], ed = 1;
int S, T, MAXP, MAXF, pre[MAXN];
JQK lev[MAXN], mono[MAXM << 1];
bool exist[MAXN];
void addedge(int u, int v, int cap, JQK val)
{
    to[++ed] = v;
    nxt[ed] = Head[u];
    Head[u] = ed;
    f[ed] = cap;
    mono[ed] = val;
    to[++ed] = u;
    nxt[ed] = Head[v];
    Head[v] = ed;
    f[ed] = 0;
    mono[ed] = -1 * val;
    return;
}
bool BFS()
{
    int u;
    queue<int>q;
    for (int i = 0; i <= MAXP + 1; i++) {
        exist[i] = 0;
        lev[i] = INF;
    }
    //memset(exist, false, sizeof(exist));
    //memset(lev, 127, sizeof(lev));
    lev[S] = pre[S] = 0;
    q.push(S);
    while (q.size()) {
        u = q.front();
        q.pop();
        exist[u] = false;
        for (int i = Head[u]; i; i = nxt[i])
            if (f[i] && lev[u] + mono[i] < lev[to[i]]) {
                lev[to[i]] = lev[u] + mono[i];
                pre[to[i]] = i;
                if (!exist[to[i]]) {
                    exist[to[i]] = true;
                    q.push(to[i]);
                }
            }
    }
    for (int i = 0; i <= MAXP + 1; i++) {
        cur[i] = Head[i];
    }
    //memcpy(cur, Head, sizeof(Head));
    return lev[T] != INF;
}
JQK Augment()
{
    int delta = INF;
    for (int i = pre[T]; i; i = pre[to[i ^ 1]])
        if (f[i] < delta) {
            delta = f[i];
        }
    for (int i = pre[T]; i; i = pre[to[i ^ 1]]) {
        f[i] -= delta;
        f[i ^ 1] += delta;
    }
    MAXF += delta;
    return delta * lev[T];
}
JQK MCMF()
{
    JQK ans = 0;
    memset(exist, false, sizeof(exist));
    while (BFS())
        //ans+=DFS(S,INF)*lev[T];
    {
        ans += Augment();
    }
    return ans;
}
void init(int x123, int y123)
{
    MAXP = MAXF = 0;
    memset(Head, 0, sizeof(Head));
    ed = 1;
    S = x123;
    T = y123;
    return;
}
int main()
{


    return 0;
}
/*int DFS(int u, int maxf)
{
    if (u == T || !maxf) {
        return maxf;
    }
    exist[u] = true;
    int cnt = 0;
    for (int &i = cur[u], tem; i; i = nxt[i])
        if (f[i] && lev[u] + mono[i] == lev[to[i]]) {
            if (exist[to[i]]) {
                continue;
            }
            tem = DFS(to[i], min(f[i], maxf));
            maxf -= tem;
            f[i] -= tem;
            f[i ^ 1] += tem;
            cnt += tem;
            if (!maxf) {
                break;
            }
        }
    if (!cnt) {
        lev[u] = -1 * INF;
    }
    exist[u] = false;
    return cnt;
}*/










// MAXMCOST
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const int MAXN = 250005;
const int MAXM = 6000005;
struct qwe {
    int ne, no, to, va, c;
} e[MAXM];
int h[MAXN], fr[MAXN], sm, cnt, ans;
int dis[MAXM];
bool v[MAXN];
int s, t;
int read()
{
    int r = 0, f = 1;
    char p = getchar();
    while (p > '9' || p < '0') {
        if (p == '-') {
            f = -1;
        }
        p = getchar();
    }
    while (p >= '0' && p <= '9') {
        r = r * 10 + p - 48;
        p = getchar();
    }
    return r * f;
}
void add(int u, int v, int w, int c)
{
    cnt++;
    e[cnt].ne = h[u];
    e[cnt].no = u;
    e[cnt].to = v;
    e[cnt].va = w;
    e[cnt].c = c;
    h[u] = cnt;
}
void ins(int u, int v, int w, int c)
{
    add(u, v, w, c);
    add(v, u, 0, -c);
}
bool spfa()
{
    for (int i = s; i <= t; i++) {
        dis[i] = -1e9;
    }
    queue<int>q;
    q.push(s);
    v[s] = 1;
    dis[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        v[u] = 0;
        for (int i = h[u]; i; i = e[i].ne)
            if (e[i].va > 0 && dis[e[i].to] < dis[u] + e[i].c) {
                dis[e[i].to] = dis[u] + e[i].c;
                fr[e[i].to] = i;
                if (!v[e[i].to]) {
                    v[e[i].to] = 1;
                    q.push(e[i].to);
                }
            }
    }
    return dis[t] != -1e9;
}
void mcf()
{
    int x = INT_MAX / 2;
    for (int i = fr[t]; i; i = fr[e[i].no]) {
        x = min(x, e[i].va);
    }
    sm += x;
    for (int i = fr[t]; i; i = fr[e[i].no]) {
        e[i].va -= x;
        e[i ^ 1].va += x;
        ans += 1LL * e[i].c * x;
    }
}
int main()
{
    
}
