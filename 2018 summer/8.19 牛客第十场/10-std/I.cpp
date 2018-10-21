#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <bitset>
using namespace std;
const int N=2100,inf=2e9;
struct bian{
	int next,point,l,r;
}b[N<<1];
int p[N],len,n,w[N],dp[N][N],m;
bitset<N>in[N];
struct atom{
	int where,w;
}A[N];
int compare(atom k1,atom k2){
	return k1.w<k2.w||(k1.w==k2.w&&k1.where<k2.where);
}
void ade(int k1,int k2,int k3,int k4){
	b[++len]=(bian){p[k1],k2,k3,k4}; p[k1]=len;
}
void add(int k1,int k2,int k3,int k4){
	ade(k1,k2,k3,k4); ade(k2,k1,k3,k4);
}
const int mo=998244353;
void dfs(int k1,int k2){
	for (int i=1;i<=m;i++)
		if (A[i].where==k1) in[k1][i]=1;
	for (int i=p[k1];i;i=b[i].next){
		int j=b[i].point;
		if (j!=k2){
			dfs(j,k1); in[k1]|=in[j];
		}
	}
}
int pre[N];
int cross(int k1,int k2,int l,int r){
	if (k1>k2) swap(k1,k2); k2--;
	return max(min(k2,r)-max(k1,l)+1,0);
}
void update(int &k1,long long k2){
	k1=(k1+k2)%mo;
}
int x[N];
void treedp(int k1,int k2){
	int where=1;
	for (int i=1;i<=m;i++) if (A[i].where==k1) where=i;
	for (int i=where;i<=m;i++) dp[k1][i]=1;
	for (int i=p[k1];i;i=b[i].next){
		int j=b[i].point;
		int L=b[i].l,R=b[i].r;
		if (j!=k2){
			treedp(j,k1);
			memcpy(pre,dp[k1],sizeof dp[k1]);
			memset(dp[k1],0x00,sizeof dp[k1]);
			int prew=0;
			for (int a=1;a<=m;a++){
				int k=cross(0,A[a].w,L,R);
				update(dp[k1][a],1ll*pre[a]*dp[j][a]%mo*k);
				if (!in[j][a])
					update(dp[k1][a],1ll*pre[a]*prew%mo*(R-L+1-k));
				else update(prew,1ll*dp[j][a]);
			}
			prew=0;
			for (int a=m;a;a--){
				int k=cross(0,A[a].w,L,R);
				if (!in[j][a]) update(dp[k1][a],1ll*pre[a]*prew);
				else update(prew,1ll*dp[j][a]*(R-L+1-k));
			}
		}
	}
}
int quick(int k1,int k2){
	int k3=1;
	while (k2){
		if (k2&1) k3=1ll*k3*k1%mo;
		k2>>=1; k1=1ll*k1*k1%mo;
	}
	return k3;
}
int father[N];
int findfather(int k1){
	if (father[k1]==k1) return k1;
	return father[k1]=findfather(father[k1]);
}
void solve(){
	scanf("%d%d",&n,&m); len=0;
	memset(p,0x00,sizeof p);
	assert(1<=min(n,m)&&max(n,m)<=2000);
	memset(dp,0x00,sizeof dp);
	for (int i=1;i<=n;i++) father[i]=i;
	int all=1;
	memset(w,0x00,sizeof w);
	for (int i=1;i<n;i++){
		int k1,k2,k3,k4; scanf("%d%d%d%d",&k1,&k2,&k3,&k4);
		assert(1<=min(k1,k2)&&max(k1,k2)<=n&&k1!=k2);
		assert(findfather(k1)!=findfather(k2));
		father[findfather(k1)]=findfather(k2);
		add(k1,k2,k3,k4); all=1ll*all*(k4-k3+1)%mo;
		assert(k3<=k4&&1<=k3&&k4<=1000000000);
	}
	for (int i=1;i<=m;i++){
		scanf("%d%d",&A[i].where,&A[i].w);
		assert(1<=A[i].where&&A[i].where<=n);
		assert(1<=A[i].w&&A[i].w<=1000000000);
	}
	sort(A+1,A+m+1,compare);
	for (int i=1;i<=n;i++) in[i]=0;
	dfs(1,0); treedp(1,0);
	int ans=0;
	for (int i=1;i<=m;i++) update(ans,dp[1][i]);
	ans=1ll*ans*quick(all,mo-2)%mo;
	printf("%d\n",(mo+1-ans)%mo);
}
int main(){
	int t; scanf("%d",&t); assert(1<=t&&t<=5);
	for (;t;t--) solve();
	return 0;
}