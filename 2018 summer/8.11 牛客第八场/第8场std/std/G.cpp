//by yjz
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
ll qpow(ll x,ll k){return k==0?1:1ll*qpow(1ll*x*x%mod,k>>1)*(k&1?x:1)%mod;}
ll n;
int main()
{
	cin>>n;
	ll V,E;
	V=n*(n-1)%mod*(n-2)%mod*(n-3)%mod*qpow(24,mod-2)%mod;
	E=((n*(n-1)/2)%mod+V*2)%mod;
	V=(V+n)%mod;
	cout<<((E-V+1)%mod+mod)%mod;
	return 0;
}
