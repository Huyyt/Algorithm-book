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
const int P=998244353;
const int N=19;
inline int Pow(int a,int b){
	int c=1;
	for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
	return c;
}
int a[N];
int n,m;
int num[1<<N];
int bitc[1<<N];
int p2[100000];
int g[1<<N][N+1],f[1<<N][N+1];
void fwt(int f[1<<N][N+1]){
	rep(i,0,n-1)rep(S,0,(1<<n)-1)if(S&(1<<i))rep(j,0,n)f[S][j]=(f[S][j]+f[S^(1<<i)][j])%P;
}
void nfwt(int f[1<<N][N+1]){
	per(i,n-1,0)rep(S,0,(1<<n)-1)if(S&(1<<i))rep(j,0,n)f[S][j]=(f[S][j]+P-f[S^(1<<i)][j])%P;
}
int comb[N*2][N*2];
int d[1<<N][N+1];
int iv[1000];
void jie(int *f,int *g){
	static int invf[N+1];
	memset(invf,0,sizeof invf);
	int t=Pow(f[0],P-2);
	invf[0]=t;
	rep(i,1,n){
		LL w=0;
		rep(j,0,i-1){
			if(w<0)w+=invf[j]*1ll*f[i-j];
			else w+=(invf[j]-P)*1ll*f[i-j];
		}
		invf[i]=(P-((w%P+P)%P))*1ll*t%P;
	}
	static int df[N+1];
	memset(df,0,sizeof df);
	rep(i,1,n){
		df[i-1]=f[i]*1ll*i%P;
	}
	rep(i,0,n)g[i]=0;
	rep(i,0,n){
		LL w=0;
		rep(j,0,i){
			if(w<0)w+=df[j]*1ll*invf[i-j];
			else w+=(df[j]-P)*1ll*invf[i-j];
		}
		g[i]=(w%P+P)%P;
	}
	per(i,n-1,0)g[i+1]=g[i]*1ll*iv[i+1]%P;g[0]=0;
}
void calcG(){
	rep(S,0,(1<<n)-1)d[S][bitc[S]]=p2[num[S]];
	fwt(d);
	rep(S,0,(1<<n)-1)jie(d[S],g[S]);
	nfwt(g);
	rep(S,0,(1<<n)-1)rep(i,0,n)if(bitc[S]!=i)g[S][i]=0;
}
int ifac[N*2];
int fac[N*2];
void equation(int *g,int *f){
	assert(g[0]==0);
	static int h[N+1];
	memset(h,0,sizeof h);
	f[0]=0;
	h[0]=1;
	rep(i,1,n){
		f[i]=h[i]=0;
		rep(j,1,i)f[i]=(f[i]+(g[j]*1ll*h[i-j]%P)*1ll*ifac[i-j])%P;
		rep(j,1,i)h[i]=(h[i]+((f[j]*1ll*h[i-j]%P)*1ll*comb[i-1][j-1]%P)*1ll*fac[j])%P;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	assert(1<=n&&n<=19);
	assert(0<=m&&m<=n*(n-1)/2);
	rep(i,1,n*2)iv[i]=Pow(i,P-2);
	ifac[0]=1;rep(i,1,n)ifac[i]=ifac[i-1]*1ll*iv[i]%P;
	fac[0]=1;rep(i,1,n)fac[i]=fac[i-1]*1ll*i%P;
	rep(i,0,n){
		comb[i][0]=comb[i][i]=1;
		rep(j,1,i-1)comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%P;
	}
	rep(i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		x--;y--;
		assert(!(a[x]&(1<<y)));
		assert(!(a[y]&(1<<x)));
		a[x]|=(1<<(y));
		a[y]|=(1<<(x));
	}
	rep(S,0,(1<<n)-1)rep(i,0,n-1)if(S&(1<<i))bitc[S]++;
	rep(S,0,(1<<n)-1){
		int w=0;
		rep(i,0,n-1)if(S&(1<<i))w+=bitc[(a[i]&S)];
		num[S]=w/2;
	}
	p2[0]=1;rep(i,1,5000)p2[i]=p2[i-1]*2%P;
	calcG();
	fwt(g);
	rep(S,0,(1<<n)-1){
		equation(g[S],f[S]);
	}
	nfwt(f);
	//rep(S,0,(1<<n)-1)printf("f[%d]=%d\n",S,f[S][bitc[S]]);
	printf("%d\n",f[(1<<n)-1][n]);
	return 0;
}







