#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;
const int N=410,mo=998244353,M=1000000;
int dp[N][N],inv[N],f[N][N],ext[N][N],C[N][N];
int p,A[N*N],B[N*N],n,ans;
int quick(int k1,int k2){
	int k3=1;
	while (k2){
		if (k2&1) k3=1ll*k3*k1%mo;
		k2>>=1; k1=1ll*k1*k1%mo;
	}
	return k3;
}
int getext(int a,int b,int c){
	return 1ll*ext[a][b]*B[a*c]%mo;
}
void update(int &k1,long long k2){
	k1=(k1+k2)%mo;
}
int main(){
	int t; scanf("%d",&t); assert(1<=t&&t<=5);
	for (int i=0;i<=400;i++){
		C[i][0]=1;
		for (int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mo;
	} 
	for (;t;t--){
		memset(f,0x00,sizeof f);
		scanf("%d%d",&n,&p); assert(1<=n&&n<=400);
		assert(0<=p&&p<=M);
		p=1ll*p*quick(M,mo-2)%mo;
		memset(dp,0x00,sizeof dp);
		inv[0]=1;
		for (int i=1;i<=n;i++) inv[i]=quick(i,mo-2);
		A[0]=1; B[0]=1;
		for (int i=1;i<=n*n;i++) A[i]=1ll*A[i-1]*p%mo;
		for (int i=1;i<=n*n;i++) B[i]=1ll*B[i-1]*(1-p+mo)%mo;
		for (int i=1;i<=n;i++){
			ext[i][1]=(1-B[i]+mo)%mo;
			for (int j=2;j<=n;j++)
				ext[i][j]=1ll*ext[i][j-1]*ext[i][1]%mo;
		}
		for (int i=1;i<=n;i++)
			for (int j=1;j<=i;j++){
				int enp=1ll*j*inv[i]%mo;
				f[i][j]=enp;
				for (int k=1;k<=i-j;k++){
					update(f[i][j],1ll*f[i-j][k]*getext(j,k,i-j-k)%mo*(1-enp+mo)%mo*C[i-j][k]);
				}
			}
		dp[n][1]=1; int ans=0;
		for (int i=n;i;i--)
			for (int j=1;j<=i;j++){
				int enp=1ll*j*inv[i]%mo;
				int rem=(f[i][j]-enp+mo)%mo;
				for (int k=1;k<=i-j;k++){
					update(dp[i-j][k],1ll*dp[i][j]*(1-enp+mo)%mo*getext(j,k,i-j-k)%mo*C[i-j][k]);
				}
				update(ans,1ll*dp[i][j]*rem);
			}
		ans=(ans+1ll*1000000000*(1-f[n][1]+mo))%mo;
		ans=1ll*ans*n%mo;
		for (int i=1;i<=n*n;i++) ans=1ll*ans*M%mo;
		printf("%d\n",ans);
	}
	return 0;
}