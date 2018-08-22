//by yjz
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll qpow(ll x,ll k,ll md){return k==0?1:1ll*qpow(1ll*x*x%md,k>>1,md)*(k&1?x:1)%md;}
int N,M,K,X,cnt[33],a[1001111],b[1001111];
int phi;
const int B=1001111;
int pr[15],pk[15],pn,tab[15][B];
void fac(int K)
{
	int OK=K;
	phi=K;
	for(int i=2;i*i<=K;i++)
	{
		if(K%i==0)
		{
			phi=phi/i*(i-1);
			while(K%i==0)K/=i,pk[pn]++;
			pr[pn++]=i;
		}
	}
	if(K>1)
	{
		phi=phi/K*(K-1);
		pk[pn]=1;
		pr[pn++]=K;
	}
	for(int i=0;i<pn;i++)
	{
		tab[i][0]=1;
		for(int j=1;j<B;j++)tab[i][j]=1ll*tab[i][j-1]*pr[i]%OK;
	}
}
void mul(int x)
{
	for(int i=0;i<pn;i++)
	{
		while(x%pr[i]==0)
		{
			x/=pr[i];
			cnt[i]++;
		}
	}
	X=1ll*X*x%K;
}
void div(int x)
{
	if(X==0)return;
	for(int i=0;i<pn;i++)
	{
		while(x%pr[i]==0)
		{
			x/=pr[i];
			cnt[i]--;
		}
	}
	if(x>1)X=1ll*X*qpow(x,phi-1,K)%K;
}
int query()
{
	int ret=X;
	for(int i=0;i<pn;i++)
	{
		assert(cnt[i]<B);
		ret=1ll*ret*tab[i][cnt[i]]%K;
	}
	return ret;
}
int calc(int K)
{
	int inv2=(K+1)/2;
	b[0]=1ll*a[0]*inv2%K;
	for(int i=1;i<=2*M;i++)
	{
		b[i]=1ll*(a[i]-b[i-1])*inv2%K; 
	}
	ll ret=0;
	for(int i=0;i<=M;i++)ret+=b[i*2];
	return (ret%K+K)%K;
}
int calc2(int K)
{
	for(int i=2*M+32;i>=0;i--)
	{
		b[i-1]=(a[i]-2ll*b[i])%K;
	}
	ll ret=0;
	for(int i=0;i<=M;i++)ret+=b[i*2];
	return (ret%K+K)%K;
}
int main()
{
	cin>>N>>M>>K;
	N=N/2+1;M=M/2;
	fac(K);
//	cerr<<"pn="<<pn<<endl;
//	for(int i=0;i<pn;i++)cerr<<pr[i]<<","<<pk[i]<<endl;
//	cerr<<"K="<<K<<endl;
	X=1;
	for(int i=1;i<=2*M+32;i++)
	{
		if(2*N-i+1==0)break;
		mul(2*N-i+1);
		div(i);
		a[i-1]=query();
	}
//	for(int i=0;i<=10;i++)cerr<<a[i]<<" ";
	
	int d=0;
	if(pn>0&&pr[0]==2)d=pk[0];
	int K1=K/(1<<d),ans1=calc(K1);
	int K2=1<<d,ans2=calc2(K2);
//	cerr<<K1<<" "<<ans1<<endl;
//	cerr<<K2<<" "<<ans2<<endl;
	
	if(K1>K2)
	{
		swap(K1,K2);swap(ans1,ans2);
	}
	for(int i=0;i<K1;i++)
	{
		if((i*K2+ans2)%K1==ans1)
		{
			cout<<i*K2+ans2<<endl;
			return 0;
		}
	}
	return 0;
}
