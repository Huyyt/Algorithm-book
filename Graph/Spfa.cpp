//Spfa
int spfa(int s) {
        mem(d, 0x3f), mem(vis, 0);
        mem(cnt, 0);
        cnt[s] = d[s] = 0, v[s] = 1;
        q.push(s);
        while (q.size()) {
                int x = q.front();
                q.pop();
                v[x] = 0;
                for (int v, i = Head[x]; i; i = nxt[i]) {
                        v = to[i];
                        int c = cost[i];
                        if (d[v] > d[x] + c) {
                                d[v] = d[x] + c;
                                cnt[v] = cnt[x] + 1;
                        }
                        if (cnt[v] >= n) {
                                return -1;
                        }
                        if (!vis[v]) {
                                q.push(v);
                                vis[v] = 1;
                        }
                }
        }
}
