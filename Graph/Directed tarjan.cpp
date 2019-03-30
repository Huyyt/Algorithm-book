//Directed tarjan(without repeat edge)
int deep, colorsum = 0;
int top;/*sta目前的大小*/
int dfn[MAXN], color[MAXN], low[MAXN];
int sta[MAXN];//存着当前所有可能能构成强连通分量的点
bool visit[MAXN];//表示一个点目前是否在sta中
int cnt[MAXN];//各个强连通分量中含点的数目
void tarjan(int x) {
        dfn[x] = ++deep;
        low[x] = deep;
        visit[x] = 1;
        sta[++top] = x;
        for (int i = Head[x]; i; i = nxt[i]) {
                int v = to[i];
                if (!dfn[v]) {
                        tarjan(v);
                        low[x] = min(low[x], low[v]);
                } else {
                        if (visit[v]) {
                                low[x] = min(low[x], low[v]);
                        }
                }
        }
        if (dfn[x] == low[x]) {
                color[x] = ++colorsum;
                visit[x] = 0;
                while (sta[top] != x) {
                        color[sta[top]] = colorsum;
                        visit[sta[top--]] = 0;
                }
                top--;
        }
}
