/*
 *  Steiner Tree：求，使得指定K个点连通的生成树的最小总权值
 *  st[i] 表示顶点i的标记值，如果i是指定集合内第m(0<=m<K)个点，则st[i]=1<<m
 *  endSt=1<<K
 *  dptree[i][state] 表示以i为根，连通状态为state的生成树值
 */
#define CLR(x,a) memset(x,a,sizeof(x))
int dptree[N][1 << K], st[N], endSt;
bool vis[N][1 << K];
queue<int> que;
int input()
{
    /*
     *    输入，并且返回指定集合元素个数K
     *    因为有时候元素个数需要通过输入数据处理出来，所以单独开个输入函数。
     */
}
void initSteinerTree()
{
    CLR(dptree, -1);
    CLR(st, 0);
    for (int i = 1; i <= n; i++) {
        CLR(vis[i], 0);
    }
    endSt = 1 << input();
    for (int i = 1; i <= n; i++) {
        dptree[i][st[i]] = 0;
    }
}
void update(int &a, int x)
{
    a = (a > x || a == -1) ? x : a;
}
void SPFA(int state)
{
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u][state] = false;
        for (int i = p[u]; i != -1; i = e[i].next) {
            int v = e[i].vid;
            if (dptree[v][st[v] | state] == -1 ||
                    dptree[v][st[v] | state] > dptree[u][state] + e[i].w) {
                dptree[v][st[v] | state] = dptree[u][state] + e[i].w;
                if (st[v] | state != state || vis[v][state]) {
                    continue;    //只更新当前连通状态
                }
                vis[v][state] = true;
                que.push(v);
            }
        }
    }
}
void steinerTree()
{
    for (int j = 1; j < endSt; j++) {
        for (int i = 1; i <= n; i++) {
            if (st[i] && (st[i]&j) == 0) {
                continue;
            }//如果当前状态没有i节点 跳过
            for (int sub = (j - 1)&j; sub; sub = (sub - 1)&j) {
                //枚举子集 更新
                int x = st[i] | sub, y = st[i] | (j - sub);
                if (dptree[i][x] != -1 && dptree[i][y] != -1) {
                    update(dptree[i][j], dptree[i][x] + dptree[i][y]);
                }
            }
            if (dptree[i][j] != -1) {
                que.push(i), vis[i][j] = true;
            }
        }
        SPFA(j);
    }
}
