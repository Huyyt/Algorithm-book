#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;
const int mo=998244353;
int get2(long long n){
	n%=mo;
	return n*(n+1)/2%mo;
}
int getans(long long n,long long a,long long d,long long m){
	if (n==0) return 0;
	int ans=0;
	if (a>=m){
		long long k1=a/m; a-=k1*m;
		ans=(ans+k1%mo*(n%mo))%mo;
	}
	if (d>=m){
		long long k1=d/m; d-=k1*m;
		ans=(ans+k1%mo*get2(n-1))%mo;
	}
	if (d==0) return ans;
	__int128 mul=__int128(d)*__int128(n);
	long long l=(a+mul)/m;
	ans=(ans+getans(l,(a+mul)%m,m,d))%mo;
	return ans;
}
void solve(){
	int a,b,c,d; scanf("%d%d%d%d",&a,&b,&c,&d);
	assert(1<=min(min(a,b),min(c,d))&&max(max(a,b),max(c,d))<=1000000000);
	if (1ll*a*d>1ll*b*c){
		swap(a,c); swap(b,d);
	}
	if (1ll*a*d==1ll*b*c){
		puts("-1"); return;
	}
	long long lim=(1ll*b*c+1ll*b*d)/(1ll*b*c-1ll*a*d);
	int ans=(getans(lim+1,b,a,b)-getans(lim,0,c,d)-1+mo)%mo;
	printf("%d\n",ans);
}
int main(){
	int t; scanf("%d",&t); assert(1<=t&&t<=100000);
	for (;t;t--) solve();
	return 0;
}