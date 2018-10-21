#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
const int N=100000,mo=998244353;
int n,A[N+10],ans[N+10],m,inv[N+10],x[N+10];
int phi[N+10];
int quick(int k1,int k2){
	int k3=1;
	while (k2){
		if (k2&1) k3=1ll*k3*k1%mo;
		k2>>=1; k1=1ll*k1*k1%mo;
	}
	return k3;
}
void solve(){
	scanf("%d%d",&n,&m);
	assert(1<=n&&n<=N&&1<=m&&m<=N);
	memset(A,0x00,sizeof A);
	memset(ans,0x00,sizeof ans);
	for (int i=1;i<=n;i++){
		int k1; scanf("%d",&k1); 
		assert(1<=k1&&k1<=N);
		A[k1]++; x[i]=k1;
	}
	for (int i=1;i<=N;i++)
		for (int j=i+i;j<=N;j+=i) A[i]+=A[j];
	for (int i=1;i<=N;i++)
		for (int j=i;j<=N;j+=i)
			ans[j]=(ans[j]+1ll*(quick(j+1,A[i])-1)*phi[i])%mo;
	for (int i=1;i<=N;i++) ans[i]=1ll*ans[i]*inv[i]%mo;
	//for (int i=1;i<=m;i++) cout<<ans[i]<<" "; cout<<endl;
	int num=0;
	for (int i=1;i<=m;i++) num^=ans[i];
	printf("%d\n",num);
}
int main(){
	inv[1]=1;
	for (int i=2;i<=N;i++) inv[i]=(mo-1ll*(mo/i)*inv[mo%i]%mo)%mo;
	for (int i=1;i<=N;i++) phi[i]=i;
	for (int i=1;i<=N;i++)
		for (int j=i+i;j<=N;j+=i) phi[j]-=phi[i];
	int t; scanf("%d",&t); 
	for (;t;t--) solve();
	return 0;
}
