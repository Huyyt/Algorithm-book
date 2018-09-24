//0-1 Shortest path
//POJ 3662 1到N第K+1大条边权路径最小(二分答案+01最短路)
bool check(int x)
{
        deque<int>Q;
        Q.push_back(1);
        Mem(vis, 0);
        Mem(dis, 0x3f);
        dis[1] = 0;
        vis[1] = 1;
        while (!Q.empty())
        {
                int u = Q.front();
                Q.pop_front();
                if (u == N)
                {
                        return dis[u] <= K;
                }
                for (int i = head[u]; ~i; i = edge[i].next)
                {
                        int v = edge[i].v;
                        int w = edge[i].w;
                        if (w <= x)
                        {
                                dis[v] = min(dis[v], dis[u]);
                                if (!vis[v])
                                {
                                        Q.push_front(v);
                                }
                        }
                        else
                        {
                                dis[v] = min(dis[v], 1 + dis[u]);
                                if (!vis[v])
                                {
                                        Q.push_back(v);
                                }
                        }
                        vis[v] = 1;
                }
        }
        return false;
}
