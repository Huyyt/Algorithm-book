#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef int JQK;
typedef pair<JQK, int> pli;
namespace MCMF {
        const int MAXN = 100005;
        const JQK INF = INT_MAX;
        struct edge {
                int v, p;
                JQK c, f;
                JQK w;
        };
        vector<edge> g[MAXN];
        int cur[MAXN], nc;//every test case nc=0 at first
        int addv(int cnt) {
                while (cnt--) {
                        int p = ++nc;
                        g[p].resize(0);
                }
                return nc;
        }

        void addedge(int u, int v, JQK c, JQK w) {
                g[u].push_back({v, g[v].size(), c, 0, w});
                g[v].push_back({u, g[u].size() - 1, c, c, -w});
        }

        bool inq[MAXN];
        JQK dis[MAXN], pot[MAXN];
        bool dijkstra(int s, int t) {
                fill_n(dis + 1, nc, INF);
                priority_queue<pli, vector<pli>, greater<pli> > pq;
                pq.push({dis[s] = 0, s});
                while (!pq.empty()) {
                        pli p = pq.top();
                        pq.pop();
                        JQK du = p.first;
                        int u = p.second;
                        if (dis[u] < du) {
                                continue;
                        }
                        for (edge e : g[u]) {
                                int v = e.v;
                                if (e.c == e.f) {
                                        continue;
                                }
                                JQK dv = du + e.w + pot[u] - pot[v];
                                if (dis[v] > dv) {
                                        pq.push({dis[v] = dv, v});
                                }
                        }
                }
                return dis[t] != INF;
        }
        JQK dfs_mcmf(int u, int t, JQK f) {
                if (u == t) {
                        return f;
                }
                JQK sf = 0;
                inq[u] = 1;
                for (int& i = cur[u]; i != g[u].size(); i++) {
                        edge& e = g[u][i];
                        int v = e.v;
                        if (e.c == e.f || dis[u] + e.w + pot[u] - pot[v] != dis[v] || inq[v]) {
                                continue;
                        }
                        JQK df = dfs_mcmf(v, t, min(f, e.c - e.f));
                        e.f += df;
                        sf += df;
                        f -= df;
                        g[v][e.p].f -= df;
                        if (!f) {
                                break;
                        }
                }
                inq[u] = 0;
                return sf;
        }
        pair<JQK, JQK> mcmf(int s, int t, JQK mf = INF) {
                JQK sflow = 0, scost = 0;
                fill_n(pot + 1, nc, 0);
                while (dijkstra(s, t)) {
                        fill_n(cur + 1, nc, 0);
                        JQK df = dfs_mcmf(s, t, mf);
                        mf -= df;
                        sflow += df;
                        scost += (dis[t] + pot[t]) * df;
                        for (int i = 1; i <= nc; i++) {
                                pot[i] += dis[i];
                        }
                }
                return {sflow, scost};
        }
}
