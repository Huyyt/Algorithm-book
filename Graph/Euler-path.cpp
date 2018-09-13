//Euler-path
/*
无向欧拉回路:当且仅当无向图连通且并且每个点的度数为偶数
无向欧拉通路:当且仅当无向图连通并且图中恰好有两个节点的度数为奇数其他为偶数
有向欧拉回路:当且仅当每个点的入度等于出度
有向欧拉通路:当且仅当有两个点的入度不等于出度且其中一个差为1另一个差为-1
混合图欧拉
*/
//欧拉回路非递归:
int top, t;
int sta[maxn], ans[maxn]; //系统栈 答案栈
bool vis[maxn];
void euler(int JQK)
{
        sta[++top] = JQK;
        while (top > 0)
        {
                int x = sta[top], i = Head[x];
                while (i && vis[i])
                {
                        i = nxt[i];        //找到一条尚未访问的边
                }
                if (i) //沿着这条边模拟递归过程,标记该边,并更新表头
                {
                        sta[++top] = to[i];
                        vis[i] = vis[i ^ 1] = true;
                        Head[x] = nxt[i];
                }
                else  //x相连的所有边都已经访问,模拟回溯过程并记在答案栈中
                {
                        top--;
                        ans[++t] = x;  //答案栈要倒叙输出
                }
        }
}
