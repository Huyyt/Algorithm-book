//Directed tarjan(without repeat edge)
int deep, colorsum = 0;
int top;/*staĿǰ�Ĵ�С*/
int dfn[maxn], color[maxn], low[maxn];
int sta[maxn];//���ŵ�ǰ���п����ܹ���ǿ��ͨ�����ĵ�
bool visit[maxn];//��ʾһ����Ŀǰ�Ƿ���sta��
int cnt[maxn];//����ǿ��ͨ�����к������Ŀ
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
