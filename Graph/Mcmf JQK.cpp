#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef int JQK;
namespace MCMF {
        const JQK INF = 0x7f7f7f7f;
        const int MAXN = 505, MAXM = 1300;
        int Head[MAXN], cur[MAXN], to[MAXM << 1], nxt[MAXM << 1], f[MAXM << 1], ed = 1;
        int S, T, MAXP, MAXF, pre[MAXN];
        JQK lev[MAXN], cost[MAXM << 1];
        bool exist[MAXN];
        void addedge(int u, int v, int cap, JQK val) {
                to[++ed] = v;
                nxt[ed] = Head[u];
                Head[u] = ed;
                f[ed] = cap;
                cost[ed] = val;
                to[++ed] = u;
                nxt[ed] = Head[v];
                Head[v] = ed;
                f[ed] = 0;
                cost[ed] = -1 * val;
                return;
        }
        bool spfa() {
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
                                if (f[i] && lev[u] + cost[i] < lev[to[i]]) {
                                        lev[to[i]] = lev[u] + cost[i];
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
        JQK Augment() {
                JQK delta = 0x7f7f7f7f;
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
        void init(int S1, int T1) {
                MAXF = 0;
                memset(Head, 0, sizeof(Head));
                ed = 1;
                S = S1;
                T = T1;
                return;
        }
        JQK mcmf() {
                JQK ans = 0;
                memset(exist, false, sizeof(exist));
                while (spfa())
                        //ans+=DFS(S,INF)*lev[T];
                {
                        ans += Augment();
                }
                return ans;
        }
}
int main() {


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
