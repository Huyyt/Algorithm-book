//#include <bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
using namespace std;
const int maxn = 5e5 + 500;
// heappos[] , 点 i 在堆的位置
// ha[]  堆的位置[] 存储的是点 i
int heappos[2000 + 50] , ha[2000 + 50];
// prim 大根堆
struct Heap
{
        const static int HeapSize =  2010 ;
        int val[HeapSize] , sz;
        void swappos(int x , int y)
        {
                int ID1 = ha[x];
                int ID2 = ha[y];
                heappos[ID1] = y;
                heappos[ID2] = x;
                ha[x] = ID2;
                ha[y] = ID1;
                swap( val[x] , val[y] );
        }
        //向上维护
        int maintain_up(int pos)
        {
                int cur = pos , pre = cur >> 1;
                while (pre)
                {
                        if (val[cur] > val[pre])
                        {
                                swappos( cur , pre );
                                cur = pre;
                        }
                        else
                        {
                                break;
                        }
                        pre = cur >> 1;
                }
                return cur;
        }

        //向下维护
        void maintain_down(int pos)
        {
                int cur = pos;
                while (cur * 2 <= sz)
                {
                        int lson = cur << 1;
                        int rson = cur << 1 | 1;
                        if (rson > sz)
                        {
                                rson ^= 1;
                        }
                        int nxt = lson;
                        if (val[rson] > val[lson])
                        {
                                nxt = rson;
                        }
                        if (val[cur] < val[nxt])
                        {
                                swappos(cur , nxt);
                                cur = nxt;
                        }
                        else
                        {
                                break;
                        }
                }
        }

        int insert(int x , int y)
        {
                val[++sz] = x;
                heappos[y] = sz;
                ha[sz] = y;
                return maintain_up(sz);
        }

        int top()
        {
                return val[1];
        }

        void pop()
        {
                if (sz == 0)
                {
                        return;
                }
                swappos( 1 , sz--);
                maintain_down( 1 );
        }
        void init()
        {
                sz = 0 ;
        }
} heap;
struct Edge
{
        int v , nxt;
};
Edge e[maxn << 1];
int n , m , head[2000 + 50] , tot , vis[2000 + 50] , flag[2000 + 50] , mincost[2000 + 50] , mat[2000 + 50][2000 + 50] ;
inline void addedge(int u , int v )
{
        e[tot].v = v, e[tot].nxt = head[u], head[u] = tot++;
}
inline void dfs(int u)
{
        vis[u] = 1;
        for (int i = head[u] ; ~i ; i = e[i].nxt)
        {
                int v = e[i].v;
                if (vis[v])
                {
                        continue;
                }
                dfs( v );
        }
}

// s , 倒数第二个 ， t 倒数第一个
inline int prim(int & s , int & t , int num)
{
        heap.init();
        int base;
        for (int i = 1 ; i <= n ; ++ i) if (!flag[i])
                {
                        base = i ;
                        break;
                }
        t = base;
        for (int i = 1 ; i <= n ; ++ i)
        {
                if (flag[i] || i == base)
                {
                        mincost[i] = -1;
                }
                else
                {
                        heap.insert(mat[base][i] , i ) ;
                        mincost[i] = mat[base][i];
                }
        }
        for (int i = 1 ; i <= num ; ++ i)
        {
                s = t , t = ha[1];// O(1) Get
                heap.pop();
                int sb = t;
                mincost[sb] = -1;
                for (int j = head[sb] ; ~j ; j = e[j].nxt) // mlogn更新堆
                {
                        int v = e[j].v , w = mat[sb][v];
                        if (flag[v] || mincost[v] == -1)
                        {
                                continue;        // 虚拟点 or 已经处理过的点
                        }
                        else
                        {
                                mincost[v] += w;
                                int hs = heappos[v];
                                heap.val[hs] += w;
                                heap.maintain_up(hs);// 更新堆
                        }
                }
        }

        //计算切割值
        int result = 0;
        for (int i = 1 ; i <= n ; ++ i)
        {
                if (flag[i] || i == t)
                {
                        continue;
                }
                result += mat[t][i];
        }
        return result;
}

inline int stoer()
{
        int res = 0x7fffffff , s , t;
        for (int i = 1 ; i < n ; ++ i)
        {
                res = min( res , prim( s , t , n - i));
                flag[t] = 1;
                for (int j = head[t] ; ~j ; j = e[j].nxt)
                {
                        int v = e[j].v;
                        if (flag[v])
                        {
                                continue;
                        }
                        if (s == v)
                        {
                                continue;
                        }
                        int ori = mat[s][v];
                        mat[s][v] += mat[t][v];
                        mat[v][s] += mat[t][v];
                        if (ori == 0 && mat[s][v])
                        {
                                addedge( s , v );
                                addedge( v , s );
                        }
                }
        }
        return res;
}
void init()
{
        tot = 0;
        for (int i = 0; i <= n + 1; i++)
        {
                head[i] = -1;
                ha[i] = heappos[i] = vis[i] = flag[i] = mincost[i] = 0;
                for (int j = 0; j <= n + 1; j++)
                {
                        mat[i][j] = mat[j][i] = 0;
                }
        }
}
int main(int argc, char *argv[])
{
        while (scanf("%d%d", &n, &m) == 2)
        {
                bool jqk = true;
                init();
                for (int i = 1 ; i <= m ; ++ i)
                {
                        int u , v , w;
                        scanf("%d%d%d", &u , &v , &w);
                        u++, v++;
                        if (mat[u][v] == 0)
                        {
                                addedge( u , v  );
                                addedge( v , u  );
                        }
                        mat[u][v] += w, mat[v][u] += w;
                }
                dfs( 1 );
                int fa = 1;
                for (int i = 1 ; i <= n ; ++ i)
                        if (!vis[i])
                        {
                                printf("0\n");
                                jqk = false;
                                break;
                        }
                if (jqk)
                {
                        printf("%d\n", stoer());
                }
        }
        return 0;
}
