//BM
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

namespace linear_seq {
    const int N=10010;
    ll res[N],base[N],_c[N],_md[N];

    vector<int> Md;
    void mul(ll *a,ll *b,int k) {
        rep(i,0,k+k) _c[i]=0;
        rep(i,0,k) if (a[i]) rep(j,0,k) _c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
        for (int i=k+k-1;i>=k;i--) if (_c[i])
            rep(j,0,SZ(Md)) _c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%mod;
        rep(i,0,k) a[i]=_c[i];
    }
    int solve(ll n,VI a,VI b) { // a ÏµÊý b ³õÖµ b[n+1]=a[0]*b[n]+...
//        printf("SIZE %d\n",SZ(b));
        ll ans=0,pnt=0;
        int k=SZ(a);
        assert(SZ(a)==SZ(b));
        rep(i,0,k) _md[k-1-i]=-a[i];_md[k]=1;
        Md.clear();
        rep(i,0,k) if (_md[i]!=0) Md.push_back(i);
        rep(i,0,k) res[i]=base[i]=0;
        res[0]=1;
        while ((1ll<<pnt)<=n) pnt++;
        for (int p=pnt;p>=0;p--) {
            mul(res,res,k);
            if ((n>>p)&1) {
                for (int i=k-1;i>=0;i--) res[i+1]=res[i];res[0]=0;
                rep(j,0,SZ(Md)) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
            }
        }
        rep(i,0,k) ans=(ans+res[i]*b[i])%mod;
        if (ans<0) ans+=mod;
        return ans;
    }
    VI BM(VI s) {
        VI C(1,1),B(1,1);
        int L=0,m=1,b=1;
        rep(n,0,SZ(s)) {
            ll d=0;
            rep(i,0,L+1) d=(d+(ll)C[i]*s[n-i])%mod;
            if (d==0) ++m;
            else if (2*L<=n) {
                VI T=C;
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                L=n+1-L; B=T; b=d; m=1;
            } else {
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                ++m;
            }
        }
        return C;
    }
    int gao(VI a,ll n) {
        VI c=BM(a);
        c.erase(c.begin());
        rep(i,0,SZ(c)) c[i]=(mod-c[i])%mod;
        return solve(n,c,VI(a.begin(),a.begin()+SZ(c)));
    }
};

int a[2020][2020];
long long det(int n) {
    long long ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            while (a[j][i] != 0) {
                int u = a[i][i] / a[j][i];
                for (int k = 0; k < n; k++) {
                    int t = (a[i][k] - (long long)a[j][k] * u % mod + mod) % mod;
                    a[i][k] = a[j][k];
                    a[j][k] = t;
                }
                ans = -ans;
            }
        }
        ans = ans * a[i][i] % mod;
    }
    if (ans < 0) {
        ans += mod;
    }
    return ans;
}

long long work(int k, int n) {
//  assert(n > 2 * k + 1);
    memset(a, 0, sizeof a);
    for (int i = 0; i < n; i++) {
        a[i][i] = k;
        for (int j = 1; j <= k; j++) {
            a[i][(i + j) % n] = -1;
        }
    }
/*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%c", a[i][j], j == n - 1 ? '\n' : ' ');
        }
    }
*/
    int t = 1;
    for (int i = 1; i < k; i++) {
        t = t * i % mod;
    }
    return (long long)det(n - 1) * powmod(t, n) % mod;
}



void maketable() {
    printf("{\n");
    for (int k = 1; k <= 5; k++) {
        if (k > 1) {
            printf(",\n");
        }
        printf("{\n");
        for (int i = 2 * k + 1; i <= 350; i++) {
            if (i > 2 * k + 1) {
                printf(",");
            }
            printf("%lld", work(k, i));
        }
        printf("}\n");
    }
    printf("}\n");
}
int main() {
    int k;
    long long n;
//  maketable();
    cin >> k >> n;
//  k = 5;
//  printf("%d\n", work(k, n));
    vector<int> a;
    for (int i = 2 * k + 1; i <= (1 << k) + 2 * k + 1; i++) {
//      printf("%d %d\n", i, work(k, i));
        a.push_back(work(k, i));
    }
//  cout << linear_seq::gao(b[k], n - (2 * k + 1)) << endl;
    cout << linear_seq::gao(a, n - (2 * k + 1)) << endl;
    return 0;
}

//BM
