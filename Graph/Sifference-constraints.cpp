//Sifference-constraints
/*A-B>=C 则建一条B指向A边权为C的有向边
求最小解 则初始化为无穷小 再d[v]<d[x]+c更新
求最大解 则初始化为无穷大 再d[v]>d[x]+c更新
判断是否有解用spfa判正/负环
*/
//POJ 1201
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
const int MAXN = 1e6, MAXM = 1e6;
int to[MAXM << 1], nxt[MAXM << 1], Head[MAXN], ed = 1;
int cost[MAXM << 1];
inline void addedge(int u, int v, int c) {
        to[++ed] = v;
        nxt[ed] = Head[u];
        cost[ed] = c;
        Head[u] = ed;
}
int d[MAXN], cnt[MAXN];
bool vis[MAXN];
queue<int> q;
int spfa(int s, int N) {
        for (int i = 1; i <= N; i++) {
                d[i] = -1e9;
                vis[i] = false;
                cnt[i] = 0;
        }
        cnt[s] = d[s] = 0, vis[s] = 1;
        q.push(s);
        while (q.size()) {
                int x = q.front();
                q.pop();
                vis[x] = 0;
                for (int v, i = Head[x]; i; i = nxt[i]) {
                        v = to[i];
                        int c = cost[i];
                        if (d[v] < d[x] + c) {
                                d[v] = d[x] + c;
                                cnt[v] = cnt[x] + 1;
                                if (cnt[v] >= N) {
                                        return -1;
                                }
                                if (!vis[v]) {
                                        q.push(v);
                                        vis[v] = 1;
                                }
                        }
                }
        }
}
int main() {
        int n;
        int u, v, c;
        scanf("%d", &n);
        int minn = 1e9, maxx = -1e9;
        for (int i = 1; i <= n; i++) {
                scanf("%d %d %d", &u, &v, &c);
                u++, v++;
                addedge(u - 1, v, c);
                minn = min(minn, u);
                maxx = max(maxx, v);
        }
        for (int i = minn; i <= maxx ; i++) {
                addedge(i - 1, i, 0);
                addedge(i, i - 1, -1);
        }
        spfa(minn - 1, maxx);
        printf("%d\n", d[maxx]);
}
