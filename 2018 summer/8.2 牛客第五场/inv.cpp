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
const int N = 210000;
int n, a[N];
int cnt[N];
void bitadd(int x, int v)
{
        for (; x <= n; x += (x & (-x)))
        {
                cnt[x] += v;
        }
}
int bitsum(int x)
{
        int ans = 0;
        for (; x; x -= (x & (-x)))
        {
                ans += cnt[x];
        }
        return ans;
}
LL getinv()
{
        LL ans = 0;
        rep(i, 1, n / 2)
        {
                ans += i - 1 - bitsum(a[i] - 1);
                bitadd(a[i], 1);
        }
        return ans;
}
int mi[N << 2];
int cov[N << 2];
void upd(int me)
{
        mi[me] = min(mi[me << 1], mi[me << 1 | 1]) + cov[me];
}
void build(int me, int l, int r)
{
        if (l == r)
        {
                mi[me] = l;
                return;
        }
        int mid = (l + r) >> 1;
        build(me << 1, l, mid);
        build(me << 1 | 1, mid + 1, r);
        upd(me);
}
void segadd(int me, int l, int r, int x, int y, int v)
{
        if (x <= l && r <= y)
        {
                mi[me] += v;
                cov[me] += v;
                return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
        {
                segadd(me << 1, l, mid, x, y, v);
        }
        if (y > mid)
        {
                segadd(me << 1 | 1, mid + 1, r, x, y, v);
        }
        upd(me);
}
int pos[N];
int main()
{
        scanf("%d", &n);
        assert(n % 2 == 0);
        assert(2 <= n && n <= 200000);
        rep(i, 1, n / 2)
        {
                scanf("%d", &a[i]);
                assert(a[i] % 2 == 0);
                assert(1 <= a[i] && a[i] <= n);
                assert(!pos[a[i]]);
                pos[a[i]] = i;
        }
        LL ans = getinv();
        build(1, 0, n / 2);
        for (int i = 1; i <= n - 1; i += 2)
        {
                ans += i / 2 + mi[1];
                assert(i / 2 + mi[1] >= 0);
                int d = pos[i + 1];
                segadd(1, 0, n / 2, d, n / 2, -2);
        }
        printf("%lld\n", ans);
        return 0;
}





