//BK
极大团个数
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 130;
bool mp[maxn][maxn];
int some[maxn][maxn], none[maxn][maxn], all[maxn][maxn];
int n, m, ans;
void dfs(int d, int an, int sn, int nn) {
        if (!sn && !nn) {
                ++ans;
        }
        int u = some[d][0];
        for (int i = 0; i < sn; ++i) {
                int v = some[d][i];
                if (mp[u][v]) {
                        continue;
                }
                for (int j = 0; j < an; ++j) {
                        all[d + 1][j] = all[d][j];
                }
                all[d + 1][an] = v;
                int tsn = 0, tnn = 0;
                for (int j = 0; j < sn; ++j)
                        if (mp[v][some[d][j]]) {
                                some[d + 1][tsn++] = some[d][j];
                        }
                for (int j = 0; j < nn; ++j)
                        if (mp[v][none[d][j]]) {
                                none[d + 1][tnn++] = none[d][j];
                        }
                dfs(d + 1, an + 1, tsn, tnn);
                some[d][i] = 0, none[d][nn++] = v;
        }
}
int work() {
        ans = 0;
        for (int i = 0; i < n; ++i) {
                some[1][i] = i + 1;
        }
        dfs(1, 0, n, 0);
        return ans;
}
int main() {
        while (~scanf("%d %d", &n, &m)) {
                memset(mp, 0, sizeof mp);
                for (int i = 1; i <= m; ++i) {
                        int u, v;
                        scanf("%d %d", &u, &v);
                        mp[u][v] = mp[v][u] = 1;
                }
                int tmp = work();
                printf("%d\n", tmp);
        }
        return 0;
}
最大团大小
#include <bits/stdc++.h>
using namespace std;
const int maxn = 55;
bool mp[maxn][maxn];
int best, n, num[maxn];
bool dfs(int *adj, int total, int cnt) {
        int t[maxn], k;
        if (total == 0) {
                if (cnt > best) {
                        best = cnt;
                        return true;    //剪枝4
                }
                return false;
        }
        for (int i = 0; i < total; ++i) {
                if (cnt + total - i <= best) {
                        return false;    //剪枝1
                }
                if (cnt + num[adj[i]] <= best) {
                        return false;    //剪枝3
                }
                k = 0;
                for (int j = i + 1; j < total; ++j)
                        if (mp[adj[i]][adj[j]]) {
                                t[k++] = adj[j];
                        }
                //扫描与u相连的顶点中与当前要选中的adj[i]相连的顶点adj[j]并存储到数组t[]中，数量为k
                if (dfs(t, k, cnt + 1)) {
                        return true;
                }
        }
        return false;
}
int MaximumClique() {
        int adj[maxn], k;
        best = 0;
        for (int i = n; i >= 1; --i) {
                k = 0;
                for (int j = i + 1; j <= n; ++j)
                        if (mp[i][j]) {
                                adj[k++] = j;
                        }
                //得到当前点i的所有相邻点存入adj
                dfs(adj, k, 1); //每次dfs相当于必选当前i点看是否能更新best
                num[i] = best;
        }
        return best;
}
int main() {
        while (scanf("%d", &n) != -1 && n) {
                for (int i = 1; i <= n; ++i)
                        for (int j = 1; j <= n; ++j) {
                                scanf("%d", &mp[i][j]);
                        }
                printf("%d\n", MaximumClique());
        }
        return 0;
}
