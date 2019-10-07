struct HeapNode {
        int d, u;
        bool operator < (const HeapNode& rhs) const {
                return d > rhs.d;
        }
} zz;
int mindist[MAXN];
bool vis[MAXN];
priority_queue<HeapNode> que;
void Hijkstra(int s, int N) {
        for (int i = 1; i <= N; i++) {
                mindist[i] = INT_MAX;
        }
        mindist[s] = 0;
        memset(vis, 0, sizeof(vis));
        zz.d = 0, zz.u = s;
        que.push(zz);
        while (!que.empty()) {
                HeapNode x = que.top();
                que.pop();
                int u = x.u;
                if (vis[u] || mindist[u] != x.d) {
                        continue;
                }
                vis[u] = true;
                for (int v, i = Head[u]; i; i = nxt[i]) {
                        v = to[i];
                        if (mindist[v] > mindist[u] + cost[i]) {
                                mindist[v] = mindist[u] + cost[i];
                                //p[v]=u;
                                zz.d = mindist[v], zz.u = v;
                                que.push(zz);
                        }
                }
        }
}
