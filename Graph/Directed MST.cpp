//Directed_MST
#include<iostream>
using namespace std;
#include<cstdio>
#include<cstring>
#define MAXN 1005
#define INF 0x7f7f7f7f
typedef __int64 type;
struct node//边的权和顶点
{
        int u, v;
        type w;
} edge[MAXN * MAXN];
int pre[MAXN], id[MAXN], vis[MAXN], n, m, pos;
type in[MAXN];//存最小入边权,pre[v]为该边的起点
type Directed_MST(int root, int V, int E)
{
        type ret = 0;//存最小树形图总权值
        while (true)
        {
                int i;
                //1.找每个节点的最小入边
                for ( i = 0; i < V; i++)
                {
                        in[i] = INF;        //初始化为无穷大
                }
                for ( i = 0; i < E; i++) //遍历每条边
                {
                        int u = edge[i].u;
                        int v = edge[i].v;
                        if (edge[i].w < in[v] && u != v) //说明顶点v有条权值较小的入边  记录之
                        {
                                pre[v] = u;//节点u指向v
                                in[v] = edge[i].w;//最小入边
                                if (u == root) //这个点就是实际的起点
                                {
                                        pos = i;
                                }
                        }
                }
                for ( i = 0; i < V; i++) //判断是否存在最小树形图
                {
                        if (i == root)
                        {
                                continue;
                        }
                        if (in[i] == INF)
                        {
                                return -1;        //除了根以外有点没有入边,则根无法到达它  说明它是独立的点 一定不能构成树形图
                        }
                }
                //2.找环
                int cnt = 0;//记录环数
                memset(id, -1, sizeof(id));
                memset(vis, -1, sizeof(vis));
                in[root] = 0;
                for ( i = 0; i < V; i++) //标记每个环
                {
                        ret += in[i];//记录权值
                        int v = i;
                        while (vis[v] != i && id[v] == -1 && v != root)
                        {
                                vis[v] = i;
                                v = pre[v];
                        }
                        if (v != root && id[v] == -1)
                        {
                                for (int u = pre[v]; u != v; u = pre[u])
                                {
                                        id[u] = cnt;        //标记节点u为第几个环
                                }
                                id[v] = cnt++;
                        }
                }
                if (cnt == 0)
                {
                        break;        //无环   则break
                }
                for ( i = 0; i < V; i++)
                        if (id[i] == -1)
                        {
                                id[i] = cnt++;
                        }
                //3.建立新图   缩点,重新标记
                for ( i = 0; i < E; i++)
                {
                        int u = edge[i].u;
                        int v = edge[i].v;
                        edge[i].u = id[u];
                        edge[i].v = id[v];
                        if (id[u] != id[v])
                        {
                                edge[i].w -= in[v];
                        }
                }
                V = cnt;
                root = id[root];
        }
        return ret;
}
int main()
{
        int i;
        while (scanf("%d%d", &n, &m) != EOF)
        {
                type sum = 0;
                for ( i = 0; i < m; i++)
                {
                        scanf("%d%d%I64d", &edge[i].u, &edge[i].v, &edge[i].w);
                        edge[i].u++;
                        edge[i].v++;
                        sum += edge[i].w;
                }
                sum ++;
                for ( i = m; i < m + n; i++) //增加超级节点0,节点0到其余各个节点的边权相同（此题中 边权要大于原图的总边权值）
                {
                        edge[i].u = 0;
                        edge[i].v = i - m + 1;
                        edge[i].w = sum;
                }
                type ans = Directed_MST(0, n + 1, m + n);
                //n+1为总结点数,m+n为总边数
                //ans代表以超级节点0为根的最小树形图的总权值,
                //将ans减去sum,如果差值小于sum,说明节点0的出度只有1,说明原图是连通图
                //如果差值>=sum,那么说明节点0的出度不止为1,说明原图不是连通图
                if (ans == -1 || ans - sum >= sum)
                {
                        puts("impossible");
                }
                else
                {
                        printf("%I64d %d\n", ans - sum, pos - m);
                }
                puts("");
        }
        return 0;
}
