//by yjz
#include<bits/stdc++.h>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
#define bged(v) (v).begin(),(v).end()
#define foreach(it,s) for(__typeof((s).begin()) it=(s).begin();it!=(s).end();it++)
typedef long long ll;
const int Imx = 2147483647;
const ll Lbig = 2e18;
const int mod = 998244353;
//My i/o stream
struct fastio
{
        char s[100000];
        int it, len;
        fastio()
        {
                it = len = 0;
        }
        inline char get()
        {
                if (it < len)
                {
                        return s[it++];
                }
                it = 0;
                len = fread(s, 1, 100000, stdin);
                if (len == 0)
                {
                        return EOF;
                }
                else
                {
                        return s[it++];
                }
        }
        bool notend()
        {
                char c = get();
                while (c == ' ' || c == '\n')
                {
                        c = get();
                }
                if (it > 0)
                {
                        it--;
                }
                return c != EOF;
        }
} _buff;
#define geti(x) x=getnum()
#define getii(x,y) geti(x),geti(y)
#define getiii(x,y,z) getii(x,y),geti(z)
#define puti(x) putnum(x),putchar(' ')
#define putii(x,y) puti(x),puti(y)
#define putiii(x,y,z) putii(x,y),puti(z)
#define putsi(x) putnum(x),putchar('\n')
#define putsii(x,y) puti(x),putsi(y)
#define putsiii(x,y,z) putii(x,y),putsi(z)
inline ll getnum()
{
        ll r = 0;
        bool ng = 0;
        char c;
        c = _buff.get();
        while (c != '-' && (c < '0' || c > '9'))
        {
                c = _buff.get();
        }
        if (c == '-')
        {
                ng = 1, c = _buff.get();
        }
        while (c >= '0' && c <= '9')
        {
                r = r * 10 + c - '0', c = _buff.get();
        }
        return ng ? -r : r;
}
template<class T> inline void putnum(T x)
{
        if (x < 0)
        {
                putchar('-'), x = -x;
        }
        register short a[20] = {}, sz = 0;
        while (x)
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
inline char getreal()
{
        char c = _buff.get();
        while (c <= 32)
        {
                c = _buff.get();
        }
        return c;
}
ll qpow(ll x, ll k)
{
        return k == 0 ? 1 : 1ll * qpow(1ll * x * x % mod, k >> 1) * (k & 1 ? x : 1) % mod;
}
const int maxn = 1000111;
ll pw2[maxn], pw22[maxn], tab[maxn];
ll ipw2[maxn], ipw22[maxn];
vector<int> con[maxn];
int n, sz[maxn], fa[maxn];
void pdfs(int x)
{
        sz[x] = 1;
        tab[x] = 1;
        for (int i = 0; i < con[x].size(); i++)
        {
                int u = con[x][i];
                if (u == fa[x])
                {
                        continue;
                }
                fa[u] = x;
                pdfs(u);
                sz[x] += sz[u];
                tab[x] = tab[x] * pw22[sz[u]] % mod;
        }
}
ll query(int x, int y)
{
        if (fa[y] == x)
        {
                return tab[y];
        }
        else
        {
                return tab[y] * ipw22[sz[x]] % mod * pw22[n - sz[y]] % mod;
        }
}
ll solve1()
{
        ll ret = 0;
        for (int i = 1; i <= n; i++)
        {
                ret = (ret + tab[i] * pw22[n - sz[i]]) % mod;
        }
        return ret;
}
ll solve2()
{
        ll ret = 0;
        for (int i = 1; i <= n; i++)
        {
                for (int j = 0; j < con[i].size(); j++)
                {
                        int u = con[i][j];
                        if (i > u)
                        {
                                continue;
                        }
                        ret = (ret + query(i, u) * query(u, i)) % mod;
                }
        }
        return ret;
}
int main()
{
        pw2[0] = 1;
        for (int i = 1; i < maxn; i++)  //2的i次方
        {
                pw2[i] = pw2[i - 1] * 2 % mod;
        }
        pw22[0] = 1;
        for (int i = 1; i < maxn; i++)  //2的i*(i+1)/2次方
        {
                pw22[i] = pw22[i - 1] * pw2[i] % mod;
        }
        ll inv2 = qpow(2, mod - 2);
        ipw2[0] = 1;
        for (int i = 1; i < maxn; i++) //2的i次方逆元
        {
                ipw2[i] = ipw2[i - 1] * inv2 % mod;
        }
        ipw22[0] = 1;
        for (int i = 1; i < maxn; i++)  //2的i*(i+1)/2次方逆元
        {
                ipw22[i] = ipw22[i - 1] * ipw2[i] % mod;
        }
        geti(n);
        for (int i = 1; i < n; i++)
        {
                int x, y;
                getii(x, y);
                con[x].PB(y);
                con[y].PB(x);
        }
        pdfs(1);
        ll ans = (solve1() - solve2() + mod) % mod;
        cout << ans << endl;
        return 0;
}

