//MCMF double Hdu5988
#include <bits/stdc++.h>
#define PI acos(-1.0)
#define mem(a,b) memset((a),b,sizeof(a))
#define TS printf("!!!\n")
#define pb push_back
#define inf 1e9
//std::ios::sync_with_stdio(false);
using namespace std;
//priority_queue<int,vector<int>,greater<int>> que;
const double EPS = 1.0e-8;
const double eps = 1.0e-8;
typedef pair<int, int> pairint;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 205;
const int  maxm = 300;
//next_permutation
int level[205];
int Si, Ei, Ci;
struct Edge {
        int from, to, cap, flow;
        double cost;
        Edge() {}
        Edge(int f, int t, int c, int fl, double co): from(f), to(t), cap(c), flow(fl), cost(co) {}
};
struct MCMF {
        int n, m, s, t;
        vector<Edge>edges;
        vector<int>g[maxn];
        bool inq[maxn];
        double d[maxn];
        int p[maxn];
        int a[maxn];
        void init(int n, int s, int t) {
                this->n = n;
                this->s = s;
                this->t = t;
                edges.clear();
                for (int i = 0; i <= n; i++) {
                        g[i].clear();
                }
        }
        void AddEdge(int from, int to, int cap, double cost) {
                edges.push_back(Edge(from, to, cap, 0, cost));
                edges.push_back(Edge(to, from, 0, 0, -cost));
                m = edges.size();
                g[from].push_back(m - 2);
                g[to].push_back(m - 1);
        }
        bool BellmanFord(int &flow, double &cost) {
                for (int i = 0; i <= n; i++) {
                        d[i] = inf;
                }
                memset(inq, 0, sizeof(inq));
                d[s] = 0, a[s] = inf, inq[s] = 1, p[s] = 0;
                queue<int>q;
                q.push(s);
                while (!q.empty()) {
                        int u = q.front();
                        q.pop();
                        inq[u] = 0;
                        for (int i = 0; i < g[u].size(); i++) {
                                Edge &e = edges[g[u][i]];
                                if (e.cap > e.flow && d[e.to] > d[u] + e.cost + eps) {
                                        d[e.to] = d[u] + e.cost;
                                        p[e.to] = g[u][i];
                                        a[e.to] = min(a[u], e.cap - e.flow);
                                        if (!inq[e.to]) {
                                                q.push(e.to);
                                                inq[e.to] = 1;
                                        }
                                }
                        }
                }
                if (d[t] == inf) {
                        return false;
                }
                flow += a[t];
                cost += a[t] * d[t];
                int u = t;
                while (u != s) {
                        edges[p[u]].flow += a[t];
                        edges[p[u] ^ 1].flow -= a[t];
                        u = edges[p[u]].from;
                }
                return true;
        }
        double Min_cost(int &flow, double &cost) {
                flow = 0, cost = 0;
                while (BellmanFord(flow, cost));
                return cost;
        }
} mc;
int main() {
        int time;
        scanf("%d", &time);
        while (time--) {

                int n, m;
                int a, b;
                cin >> n >> m;
                int s = 0;
                int t = 2 * n + 1;
                mc.init(n * 2 + 1, s, t);
                for (int i = 1; i <= n; i++) {
                        scanf("%d %d", &a, &b);
                        //cin >> a >> b;
                        if (a == b) {
                                continue;
                        } else {
                                if (a > b) {
                                        mc.AddEdge(s, i, a - b, 0);
                                } else {
                                        mc.AddEdge(i, t, b - a, 0);
                                }
                        }
                }
                int u, v, c;
                double p;
                for (int i = 1; i <= m; i++) {
                        scanf("%d %d %d %lf", &u, &v, &c, &p);
                        //cin >> u >> v >> c >> p;
                        p = -log(1 - p);
                        if (c == 0) {
                                continue;
                        } else if (c == 1) {
                                mc.AddEdge(u, v, 1, 0);
                        } else {
                                mc.AddEdge(u, v, 1, 0);
                                mc.AddEdge(u, v, c - 1, p);
                        }
                }
                int flow = 0;
                double cost = 0;
                cost = mc.Min_cost(flow, cost);
                cost = exp(-cost);
                printf("%.2f\n", 1 - cost);
        }
}
