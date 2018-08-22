// This amazing code is by Eric Sunli Chen.
#include<bits/stdc++.h>
using namespace std;
template<typename T> bool get_int(T &x)
{
        char t = getchar();
        bool neg = false;
        x = 0;
        for (; (t > '9' || t < '0') && t != '-' && t != EOF; t = getchar());
        if (t == '-')
        {
                neg = true, t = getchar();
        }
        if (t == EOF)
        {
                return false;
        }
        for (; t <= '9' && t >= '0'; t = getchar())
        {
                x = x * 10 + t - '0';
        }
        if (neg)
        {
                x = -x;
        }
        return true;
}
template<typename T> void print_int(T x)
{
        if (x < 0)
        {
                putchar('-'), x = -x;
        }
        short a[20] = {}, sz = 0;
        while (x > 0)
        {
                a[sz++] = x % 10, x /= 10;
        }
        if (sz == 0)
        {
                putchar('0');
        }
        for (int i = sz - 1; i >= 0; i--)
        {
                putchar('0' + a[i]);
        }
}
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define get1(a) get_int(a)
#define get2(a,b) (get1(a)&&get1(b))
#define get3(a,b,c) (get1(a)&&get2(b,c))
#define printendl(a) print_int(a),puts("")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
const int inf = 0x3f3f3f3f;
const LL Linf = 1ll << 61;
const double pi = acos(-1.0);
const int mod = 998244353;
int power(int x, LL y)
{
        int ret = 1;
        while (y)
        {
                if (y & 1)
                {
                        ret = 1ll * ret * x % mod;
                }
                x = 1ll * x * x % mod;
                y >>= 1;
        }
        return ret;
}

vector<int>g[1000111];
int n, sz[1000111], dp[1000111], ans;

LL sum[1000111];

void dfs1(int x, int f)
{
        sz[x] = 1;
        sum[x] = 0;
        for (int i = 0; i < (int)g[x].size(); i++)if (g[x][i] != f)
                {
                        dfs1(g[x][i], x);
                        sz[x] += sz[g[x][i]];
                        sum[x] += 1ll * sz[g[x][i]] * (sz[g[x][i]] + 1) / 2;
                }
}
void dfs2(int x, int f)
{
        dp[x] = 1;
        for (int i = 0; i < (int)g[x].size(); i++)if (g[x][i] != f)
                {
                        dfs2(g[x][i], x);
                        int c = (power(2, 1ll * sz[g[x][i]] * (sz[g[x][i]] + 1) / 2) - power(2, sum[g[x][i]]) + mod) % mod;
                        dp[x] = 1ll * dp[x] * (dp[g[x][i]] + c) % mod;
                }
        if (f)
        {
                LL tmp = sum[f] - 1ll * sz[x] * (sz[x] + 1) / 2 + 1ll * (n - sz[f]) * (n - sz[f] + 1) / 2;
                int c = (power(2, 1ll * (n - sz[x]) * (n - sz[x] + 1) / 2) - power(2, tmp) + mod) % mod;
                ans = (ans + 1ll * c * dp[x]) % mod;
        }
        else
        {
                ans += dp[x];
                if (ans >= mod)
                {
                        ans -= mod;
                }
        }
}
int main()
{
        get1(n);
        for (int i = 1, u, v; i < n; i++)
        {
                get2(u, v);
                g[u].pb(v);
                g[v].pb(u);
        }
        dfs1(1, 0);
        dfs2(1, 0);
        printendl(ans);
        return 0;
}
