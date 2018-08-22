#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <cassert>
using namespace std;
const int N=410000;
struct atom{
	int t,where,w;
}A[N];
int len,I[N+10],nI[N+10];
const int mo=998244353;
int quick(int k1,int k2){
	int k3=1;
	while (k2){
		if (k2&1) k3=1ll*k3*k1%mo;
		k2>>=1; k1=1ll*k1*k1%mo;
	}
	return k3;
}
int C(int k1,int k2){
	return 1ll*I[k1]*nI[k2]%mo*nI[k1-k2]%mo;
}
int n,m;
int query(int where,int t){
	int ans=0;
	for (int i=1;i<=len;i++)
		if (A[i].where<=where) ans=(ans+1ll*A[i].w*C(where-A[i].where+t-A[i].t-1,t-A[i].t-1))%mo;
	return ans;
}
void solve(){
	scanf("%d%d",&n,&m); len=0; int t=0; int numq=0;
	assert(1<=n&&n<=100000&&1<=m&&m<=100000);
	for (;m;m--){
		int k1; scanf("%d",&k1);
		assert(k1==1||k1==2||k1==3);
		if (k1==1){
			int l,r,w; scanf("%d%d%d",&l,&r,&w);
			assert(1<=l&&l<=r&&r<=n);
			assert(0<=w&&w<=1000000000);
			A[++len]=(atom){t-1,l,w};
			A[++len]=(atom){t-1,r+1,(mo-w)%mo};
		} else if (k1==2) t++;
		else {
			int l,r,ans=0; scanf("%d%d",&l,&r);
			assert(1<=l&&l<=r&&r<=n); numq++;
			printf("%d\n",(query(r,t+1)-query(l-1,t+1)+mo)%mo);
		}
	}
	assert(numq<=500);
}
int main(){
	I[0]=1;
	for (int i=1;i<=N;i++) I[i]=1ll*I[i-1]*i%mo;
	nI[N]=quick(I[N],mo-2);
	for (int i=N-1;i>=0;i--) nI[i]=1ll*nI[i+1]*(i+1)%mo;
	int t; scanf("%d",&t); assert(1<=t&&t<=3);
	for (;t;t--) solve();
	return 0;
}
