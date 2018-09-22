//Directed_MST
#include<iostream>
using namespace std;
#include<cstdio>
#include<cstring>
#define MAXN 1005
#define INF 0x7f7f7f7f
typedef __int64 type;
struct node//�ߵ�Ȩ�Ͷ���
{
        int u, v;
        type w;
} edge[MAXN * MAXN];
int pre[MAXN], id[MAXN], vis[MAXN], n, m, pos;
type in[MAXN];//����С���Ȩ,pre[v]Ϊ�ñߵ����
type Directed_MST(int root, int V, int E)
{
        type ret = 0;//����С����ͼ��Ȩֵ
        while (true)
        {
                int i;
                //1.��ÿ���ڵ����С���
                for ( i = 0; i < V; i++)
                {
                        in[i] = INF;        //��ʼ��Ϊ�����
                }
                for ( i = 0; i < E; i++) //����ÿ����
                {
                        int u = edge[i].u;
                        int v = edge[i].v;
                        if (edge[i].w < in[v] && u != v) //˵������v����Ȩֵ��С�����  ��¼֮
                        {
                                pre[v] = u;//�ڵ�uָ��v
                                in[v] = edge[i].w;//��С���
                                if (u == root) //��������ʵ�ʵ����
                                {
                                        pos = i;
                                }
                        }
                }
                for ( i = 0; i < V; i++) //�ж��Ƿ������С����ͼ
                {
                        if (i == root)
                        {
                                continue;
                        }
                        if (in[i] == INF)
                        {
                                return -1;        //���˸������е�û�����,����޷�������  ˵�����Ƕ����ĵ� һ�����ܹ�������ͼ
                        }
                }
                //2.�һ�
                int cnt = 0;//��¼����
                memset(id, -1, sizeof(id));
                memset(vis, -1, sizeof(vis));
                in[root] = 0;
                for ( i = 0; i < V; i++) //���ÿ����
                {
                        ret += in[i];//��¼Ȩֵ
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
                                        id[u] = cnt;        //��ǽڵ�uΪ�ڼ�����
                                }
                                id[v] = cnt++;
                        }
                }
                if (cnt == 0)
                {
                        break;        //�޻�   ��break
                }
                for ( i = 0; i < V; i++)
                        if (id[i] == -1)
                        {
                                id[i] = cnt++;
                        }
                //3.������ͼ   ����,���±��
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
                for ( i = m; i < m + n; i++) //���ӳ����ڵ�0,�ڵ�0����������ڵ�ı�Ȩ��ͬ�������� ��ȨҪ����ԭͼ���ܱ�Ȩֵ��
                {
                        edge[i].u = 0;
                        edge[i].v = i - m + 1;
                        edge[i].w = sum;
                }
                type ans = Directed_MST(0, n + 1, m + n);
                //n+1Ϊ�ܽ����,m+nΪ�ܱ���
                //ans�����Գ����ڵ�0Ϊ������С����ͼ����Ȩֵ,
                //��ans��ȥsum,�����ֵС��sum,˵���ڵ�0�ĳ���ֻ��1,˵��ԭͼ����ͨͼ
                //�����ֵ>=sum,��ô˵���ڵ�0�ĳ��Ȳ�ֹΪ1,˵��ԭͼ������ͨͼ
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
