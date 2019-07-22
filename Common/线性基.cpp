/*
线性基:

在线性基中任取若干个元素，它们的异或不为零。即它们线性无关。

其所在线性空间中每个元素都有唯一的方案由线性基中元素异或得到。

选取线性基中若干个元素异或起来得到一个元素，用这个元素去替换原线性基中任意一个元素，得到的新线性基张成的空间不变。

线性基构造方式:

// p[i] 表示线性基的第 j 位

for (i = 1; i <= n; ++i)
{
    cin >> x;
    for (j = 60; ~j; --j)
    {
        if (((x >> j) & 1))
        {
            if (p[j]) 
            x ^= p[j];
            else
            {
                p[j] = x;  //线性基新增元素
                break;
            }
        }
    }
}

判断一个数能否由若干数的子集异或得到:

把它插入到线性空间的元素集合中，看线性基是否需要新增元素即可。

最大子集异或和:

依次考虑线性基的每一位，若异或上能让答案更大（即答案的这一位为零）就异或上。



*/
#include<bits/stdc++.h>
#define reg register
using namespace std;
typedef long long ll;
const int MN = 60;
ll a[61], tmp[61];
bool flag;
void ins(ll x) {
        for (reg int i = MN; ~i; i--)
                if (x & (1ll << i))
                        if (!a[i]) {
                                a[i] = x;
                                return;
                        } else
                                x ^= a[i];
        flag = true;
}
bool check(ll x) {
        for (reg int i = MN; ~i; i--)
                if (x & (1ll << i))
                        if (!a[i])
                                return false;
                        else
                                x ^= a[i];
        return true;
}
ll qmax(ll res = 0) {
        for (reg int i = MN; ~i; i--)
                res = max(res, res ^ a[i]);
        return res;
}
ll qmin() {
        if (flag)
                return 0;
        for (reg int i = 0; i <= MN; i++)
                if (a[i])
                        return a[i];
}
ll query(ll k) {
        reg ll res = 0;
        reg int cnt = 0;
        k -= flag;
        if (!k)
                return 0;
        for (reg int i = 0; i <= MN; i++) {
                for (int j = i - 1; ~j; j--)
                        if (a[i] & (1ll << j))
                                a[i] ^= a[j];
                if (a[i])
                        tmp[cnt++] = a[i];
        }
        if (k >= (1ll << cnt))
                return -1;
        for (reg int i = 0; i < cnt; i++)
                if (k & (1ll << i))
                        res ^= tmp[i];
        return res;
}
int main() {
        int n;
        ll x;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        scanf("%lld", &x), ins(x);
        
        return 0;
}
