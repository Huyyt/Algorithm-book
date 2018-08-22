#include<stdio.h>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<cmath>
#include<iostream>
#include<assert.h>
#include<queue>
#include<string>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int P = 998244353;
const int N = 100005;
inline int Pow(int a, int b)
{
        int c = 1;
        for (; b; b >>= 1, a = a * 1ll * a % P)
                if (b & 1)
                {
                        c = c * 1ll * a % P;
                }
        return c;
}
int p[N], d[N], n, inv100;
int tmp[N], m;
int cnt[N];
void add(int x, int v)
{
        for (; x <= m; x += (x & (-x)))
        {
                cnt[x] = cnt[x] * 1ll * v % P;
        }
}
int ask(int x)
{
        int ans = 1;
        for (; x; x -= (x & (-x)))
        {
                ans = ans * 1ll * cnt[x] % P;
        }
        return ans;
}
int main()
{
        scanf("%d", &n);
        assert(1 <= n && n <= 100000);
        inv100 = Pow(100, P - 2);
        rep(i, 1, n)
        {
                scanf("%d%d", &p[i], &d[i]);
                assert(1 <= p[i] && p[i] <= 100);
                assert(1 <= d[i] && d[i] <= 1000000000);
                p[i] = p[i] * 1ll * inv100 % P;
                tmp[++m] = d[i];
        }
        sort(tmp + 1, tmp + 1 + m);
        m = unique(tmp + 1, tmp + 1 + m) - tmp - 1;
        rep(i, 1, n)
        d[i] = lower_bound(tmp + 1, tmp + 1 + m, d[i]) - tmp;
        rep(i, 0, m)
        cnt[i] = 1;
        int ans = 0;
        rep(i, 1, n)
        {
                ans = (ans + ask(m - d[i] + 1) * 1ll * p[i]) % P;
                add(m - d[i] + 1, (P + 1 - p[i]) % P);
        }
        printf("%d\n", ans);
        return 0;
}






