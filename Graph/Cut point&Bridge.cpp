//cut point&bridge
dfn[u]表示顶点u第几个被(首次)访问
low[u]表示顶点u及其子树中的点通过非父子边(回边)能够回溯到的最早的点(dfn最小)的dfn值(但不能通过连接u与其父节点的边)
int deep;
int dfn[maxn], low[maxn];
bool iscut[maxn], isbridge[maxm << 1];
int tarjan(int x, int pre) {
        int child = 0;
        int lowx;
        lowx = dfn[x] = ++deep;
        for (int i = Head[x]; i; i = nxt[i]) {
                int v = to[i];
                if (!dfn[v]) {
                        child++;
                        int lowto = tarjan(v, x);
                        lowx = min(lowx, lowto);
                        if (lowto >= dfn[x]) {
                                iscut[x] = true;;
                        }
                        if (lowto > dfn[x]) {
                                isbridge[i] = isbridge[i ^ 1] = true;
                        }
                } else {
                        if (v != pre && dfn[v] < dfn[x]) {
                                lowx = min(lowx, dfn[to]);
                        }
                }
        }
        if (pre < 0 && child == 1) {
                iscut[x] = 0;
        }
        low[x] = lowx;
        return lowx;
}
