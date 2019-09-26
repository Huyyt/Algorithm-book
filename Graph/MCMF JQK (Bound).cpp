#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef int JQK;
const JQK INF = 0x3f3f3f3f;
const int MAXN = 505;
namespace MCMF {
        const int INFFLOW = 0x3f3f3f3f;
        const JQK INFDIS = 0x3f3f3f3f;
        const int MAXN = 505;
        const int MAXM = 13000;
        int Head[MAXN], cur[MAXN], to[MAXM << 1], nxt[MAXM << 1], f[MAXM << 1], ed = 1;
        int S, T, SS, TT, MAXP, MAXF, pre[MAXN];
        int totflow[MAXN];
        JQK dis[MAXN], cost[MAXM << 1];
        bool exist[MAXN];
        inline void addedge(int u, int v, int cap, JQK val) {
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
        inline void add(int u, int v, int caplow, int captop, JQK val) {
                addedge(u, v, captop - caplow, val);
                totflow[u] -= caplow, totflow[v] += caplow;
                return ;
        }
        inline bool BFS() {
                int u;
                queue<int> q;
                for (int i = 0; i <= MAXP + 1; i++) {
                        exist[i] = 0;
                        dis[i] = INFDIS;
                }
                //memset(exist, false, sizeof(exist));
                //memset(dis, 127, sizeof(dis));
                dis[S] = pre[S] = 0;
                q.push(S);
                while (q.size()) {
                        u = q.front();
                        q.pop();
                        //cout << "q: " << u << endl;
                        exist[u] = false;
                        for (int i = Head[u]; i; i = nxt[i])
                                if (f[i] && dis[u] + cost[i] < dis[to[i]]) {
                                        dis[to[i]] = dis[u] + cost[i];
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
                return dis[T] != INFDIS;
        }
        JQK Augment() {
                JQK delta = INFFLOW;
                for (int i = pre[T]; i; i = pre[to[i ^ 1]])
                        if (f[i] < delta) {
                                delta = f[i];
                        }
                for (int i = pre[T]; i; i = pre[to[i ^ 1]]) {
                        f[i] -= delta;
                        f[i ^ 1] += delta;
                }
                MAXF += delta;
                return delta * dis[T];
        }
        void init(int s1, int t1, int s2, int t2) {
                MAXF = 0;
                memset(Head, 0, sizeof(Head));
                ed = 1;
                S = s1;
                T = t1;
                SS = s2;
                TT = t2;
                return;
        }
        inline JQK pushdownflow(int x) {
                JQK sum = 0;
                for (int i = 1; i <= x; i++) {
                        if (totflow[i] > 0) {
                                addedge(SS, i, totflow[i], 0);
                                sum += totflow[i];
                        } else if (totflow[i] < 0) {
                                addedge(i, TT, -totflow[i], 0);
                        }
                }
                return sum;//sum==dinic 循环流有解
        }
        JQK work() {
                JQK ans = 0;
                memset(exist, false, sizeof(exist));
                JQK sum = pushdownflow(T);
                addedge(T, S, INF, 0);
                swap(S, SS), swap(T, TT);
                int ccc = 0;
                while (BFS())
                        //ans+=DFS(S,INFFLOW)*dis[T];
                {
                        ans += Augment();
                }
                if (MAXF != sum) {
                        cout << -1 << endl;
                        return 0;
                }
                cout << ans << endl;
                return ans;
        }
}
int main()
{

  return 0;
}
