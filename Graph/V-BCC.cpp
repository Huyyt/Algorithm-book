//tarjan V-BCC
int dfn[MAXN], low[MAXN], dfs_clock = 0;
int BCCcnt = 0, blong[MAXN], inque[MAXM << 1];
int st[MAXN], l = 0, ans[MAXN], ansnum = 0;
bool vis[MAXM << 1];
void tarjanBCC(int x, int fa) {
        dfn[x] = low[x] = ++dfs_clock;
        for (int i = Head[x]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa || vis[i]) {
                        continue;
                }
                vis[i] = vis[i ^ 1] = 1;
                st[l++] = i;
                if (!dfn[v]) {
                        tarjanBCC(v, x);
                        low[x] = min(low[v], low[x]);
                        if (dfn[x] <= low[v]) {
                                int now, vnumber = 0, enumber = 0;
                                BCCcnt++;
                                while (1) {
                                        now = st[--l];
                                        if (blong[to[now]] != BCCcnt) {
                                                blong[to[now]] = BCCcnt, ++vnumber;
                                        }
                                        if (blong[to[now ^ 1]] != BCCcnt) {
                                                blong[to[now ^ 1]] = BCCcnt, ++vnumber;
                                        }
                                        inque[++enumber] = now;
                                        if (now == i) {
                                                break;
                                        }
                                }
                                if (vnumber == enumber) {
                                        for (int i = 1; i <= enumber; i++) {
                                                ans[++ansnum] = inque[i] / 2;
                                        }
                                }
                        }
                } else {
                        low[x] = min(low[x], dfn[v]);
                }
        }
}
