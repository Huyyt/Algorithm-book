//Hungary
#define N 202
int useif[N];   //记录y中节点是否使用 0表示没有访问过，1为访问过
int link[N];   //记录当前与y节点相连的x的节点
int mat[N][N]; //记录连接x和y的边，如果i和j之间有边则为1，否则为0
int gn, gm;   //二分图中x和y中点的数目
int can(int t) {
        int i;
        for (i = 1; i <= gm; i++) {
                if (useif[i] == 0 && mat[t][i]) {
                        useif[i] = 1;
                        if (link[i] == -1 || can(link[i])) {
                                link[i] = t;
                                return 1;
                        }
                }
        }
        return 0;
}
int MaxMatch() {
        int i, num;
        num = 0;
        memset(link, 0xff, sizeof(link));
        for (i = 1; i <= gn; i++) {
                memset(useif, 0, sizeof(useif));
                if (can(i)) {
                        num++;
                }
        }
        return num;
}






const int maxn = 1000 + 5;
struct BPM {
    int n, m;
    vector<int > G[maxn];
    int left[maxn];
    bool T[maxn];

    int right[maxn];
    bool S[maxn];

    void init(int n, int m)
    {
        this -> n = n;
        this -> m = m;
        for (int i = 0; i < maxn; i++) {
            G[i].clear();
        }
    }
    void AddEdge(int u, int v)
    {
        G[u].push_back(v);
    }
    bool match(int u)
    {
        S[u] = true;
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if (!T[v]) {
                T[v] = true;
                if (left[v] == -1 || match(left[v])) {
                    left[v] = u;
                    right[u] = v;
                    return true;
                }
            }
        }
        return false;
    }
    int solve()
    {
        memset(left, -1, sizeof(left));
        memset(right, -1, sizeof(right));
        int ans = 0;
        for (int u = 0; u < n; u++) {
            memset(S, 0, sizeof(S));
            memset(T, 0, sizeof(T));
            if (match(u)) {
                ans++;
            }
        }
        return ans;
    }
    int mincover(vector<int>& X, vector<int>& Y)
    {
        int ans = solve();
        memset(S, 0, sizeof(S));
        memset(T, 0, sizeof(T));
        for (int u = 0; u < n; u++)
            if (right[u] == -1) {
                match(u);
            }
        for (int u = 0; u < n; u++)
            if (!S[u]) {
                X.push_back(u);
            }
        for (int v = 0; v < m; v++)
            if (T[v]) {
                Y.push_back(v);
            }
        return  ans;
    }
};
BPM solver;
int main()
{
    int n, r, c;
    while (scanf("%d%d%d", &r, &c, &n)) {
        if (r == 0 && c == 0 && n == 0) {
            break;
        }
        solver.init(r, c);
        while (n--) {
            int x, y;
            scanf("%d%d", &x, &y);
            x--;
            y--;//模版中编号是从0开始的
            solver.AddEdge(x, y);
        }
        vector<int> X, Y;
        printf("%d", solver.mincover(X, Y));
        for (int i = 0; i < X.size(); i++) {
            printf(" r%d", X[i] + 1);    //最后别忘了加回来
        }
        for (int j = 0; j < Y.size(); j++) {
            printf(" c%d", Y[j] + 1);
        }
        printf("\n");
    }
    return 0;
}
