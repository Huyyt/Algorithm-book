// This amazing code is by Eric Sunli Chen.
#include<bits/stdc++.h>
using namespace std;
template<typename T> bool get_int(T &x)
{
	char t=getchar();
	bool neg=false;
	x=0;
	for(; (t>'9'||t<'0')&&t!='-'&&t!=EOF; t=getchar());
	if(t=='-')neg=true,t=getchar();if(t==EOF)return false;
	for(; t<='9'&&t>='0'; t=getchar())x=x*10+t-'0';
	if(neg)x=-x;return true;
}
template<typename T> void print_int(T x)
{
	if(x<0)putchar('-'),x=-x;
	short a[20]= {},sz=0;
	while(x>0)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1; i>=0; i--)putchar('0'+a[i]);
}
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define get1(a) get_int(a)
#define get2(a,b) (get1(a)&&get1(b))
#define get3(a,b,c) (get1(a)&&get2(b,c))
#define printendl(a) print_int(a),puts("")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;
const LL Linf=1ll<<61;
const double pi=acos(-1.0);
const double eps=1e-10;

const int poly_bits=6;
const int poly_max=1<<poly_bits;//poly_max=2^poly_bits
const int mod=998244353;//a prime in the form of k*poly_max+1 if NTT
const int root=3;//a primitive root of mod

int qpow(int x,int y,const int&mod=::mod){int ret=1;do{if(y&1)ret=1ll*ret*x%mod;x=1ll*x*x%mod;}while(y>>=1);return ret;}
inline int up_pw2(const int&x){int ret=1;while(ret<x)ret<<=1;return ret;}
int inv[poly_max+1],fac[poly_max+1],invf[poly_max+1],bits[1<<14];

int comb(int x,int y){if(x<y||y<0)return 0;return 1ll*fac[x]*invf[y]%mod*invf[x-y]%mod;}

#define type int
static int w[poly_max+1];
template<typename tp>int simplify(tp*a,int n){while(n&&a[n-1]==tp(0))n--;return n;}
inline void copy(int*a,int*b,int n,int m){for(int i=0;i<m;i++)b[i]=(i<n?a[i]:0);}

void prework()
{
	w[0]=1;w[1]=qpow(root,mod-1>>poly_bits);
	for(int i=2;i<=poly_max;i++)w[i]=1ll*w[i-1]*w[1]%mod;
	fac[0]=inv[0]=invf[0]=1;
	for(int i=1;i<=poly_max;i++)
	{
		fac[i]=1ll*i*fac[i-1]%mod;
		inv[i]=qpow(i,mod-2);
		invf[i]=1ll*inv[i]*invf[i-1]%mod;
	}
	for(int i=0;i<(1<<14);i++)bits[i]=__builtin_popcount(i);
}

void poly_dotmul(int*a,int*b,int*c,int n,int m){for(int i=0;i<n||i<m;i++)c[i]=(i<n&&i<m?1ll*a[i]*b[i]%mod:0);}
void poly_add(int*a,int*b,int*c,int n,int m){for(int i=0;i<n||i<m;i++){c[i]=(i<n?a[i]:0)+(i<m?b[i]:0);if(c[i]>=mod)c[i]-=mod;}}
void poly_sub(int*a,int*b,int*c,int n,int m){for(int i=0;i<n||i<m;i++){c[i]=(i<n?a[i]:0)-(i<m?b[i]:0);if(c[i]<0)c[i]+=mod;}}

inline void dft(type*a,int n)
{
	for(int i=0,j=0;i<n;i++){if(i<j)swap(a[i],a[j]);for(int t=n>>1;(j^=t)<t;t>>=1);}
	for(int l=1,d=1;l<n;l<<=1,d++)
	{
		int l2=l<<1;
		for(int i=0;i<n;i+=l2)for(int j=0;j<l;j++)
		{
			int tmp=1ll*a[i|l|j]*w[j<<poly_bits-d]%mod;
			a[i|l|j]=a[i|j]-tmp+mod;if(a[i|l|j]>=mod)a[i|l|j]-=mod;
			a[i|j]+=tmp;if(a[i|j]>=mod)a[i|j]-=mod;
		}
	}
}
inline void idft(type*a,int n)
{
	for(int i=0,j=0;i<n;i++){if(i<j)swap(a[i],a[j]);for(int t=n>>1;(j^=t)<t;t>>=1);}
	for(int l=1,d=1;l<n;l<<=1,d++)
	{
		int l2=l<<1;
		for(int i=0;i<n;i+=l2)for(int j=0;j<l;j++)
		{
			int tmp=1ll*a[i|l|j]*w[poly_max-(j<<poly_bits-d)]%mod;
			a[i|l|j]=a[i|j]-tmp+mod;if(a[i|l|j]>=mod)a[i|l|j]-=mod;
			a[i|j]+=tmp;if(a[i|j]>=mod)a[i|j]-=mod;
		}
	}
	int inv=qpow(n,mod-2);for(int i=0;i<n;i++)a[i]=1ll*a[i]*inv%mod;
}

static type ttA[poly_max],ttB[poly_max];
inline void poly_mult(type*a,type*b,type*c,int n,int m)
{
	int len=up_pw2(n+m-1);
	copy(a,ttA,n,len);
	copy(b,ttB,m,len);
	dft(ttA,len);dft(ttB,len);
	poly_dotmul(ttA,ttB,ttA,len,len);
	idft(ttA,len);
	copy(ttA,c,len,n+m-1);
}

static int tA[poly_max],tB[poly_max];
void poly_inv(int*a,int*b,int n,int m)
{
	assert(a[0]!=0);
	int tn=up_pw2(m);
	tB[0]=qpow(a[0],mod-2);
	for(int l=2;l<=tn;l<<=1)
	{
		int l2=l<<1;
		copy(a,tA,min(n,l),l2);
		copy(tB,tB,l>>1,l2);
		dft(tA,l2);dft(tB,l2);
		for(int i=0;i<l2;i++)tB[i]=(mod+2-1ll*tA[i]*tB[i]%mod)*tB[i]%mod;
		idft(tB,l2);
		copy(tB,tB,l,l2);
	}
	copy(tB,b,tn,m);
}

void poly_derive(int*a,int*b,int n){for(int i=1;i<n;i++)b[i-1]=1ll*a[i]*i%mod;b[n-1]=0;}
void poly_integral(int*a,int*b,int n){for(int i=n-2;i>=0;i--)b[i+1]=1ll*a[i]*inv[i+1]%mod;b[0]=0;}

void poly_ln(int*a,int*b,int n,int m)
{
	assert(a[0]==1);
	poly_inv(a,tB,n,m);
	poly_derive(a,tA,m);
	poly_mult(tA,tB,tA,m-1,m-1);
	poly_integral(tA,b,m);
}

inline void add(int&x,int y){x+=y;if(x>=mod)x-=mod;}
#define getcode(i,j) (((i)>>(j))&1)
void fmt(int *a,int n,bool f=0)
{
	if(f){for(int i=0;i<(1<<n);i++)if((bits[i]&1)&&a[i])a[i]=mod-a[i];}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<(1<<n);j++)if(getcode(j,i))
			add(a[j],a[j^(1<<i)]);
	}
	if(f){for(int i=0;i<(1<<n);i++)if((bits[i]&1)&&a[i])a[i]=mod-a[i];}
}

int tmp[2333];

int n,m,f[1<<13],eu[233],ev[233],val[1<<13];
int ft[14][1<<13];
LL c,a[13],mn[1<<13];

int calc(vector<LL>&v,LL k)
{
	sort(v.begin(),v.end());
	int sz=(int)v.size(),t1=-1,t2=-1;
	if(sz==0)return 0;
	if(sz==1||v[sz-1]==0)return (k<=v[0]);
	for(int i=60;i>=0;i--)if(getcode(v[sz-1],i)){t1=i;break;}
	for(int i=60;i>=0;i--)if(getcode(k,i)){t2=i;break;}
	if(t1<t2)return 0;
	
	int a[2]={1,0},na[2];
	for(int i=0;i<sz-1;i++)
	{
		LL v0=min(1ll<<t1,v[i]+1),v1=v[i]+1-v0;v0%=mod;v1%=mod;
		na[0]=(a[0]*v0+a[1]*v1)%mod;
		na[1]=(a[1]*v0+a[0]*v1)%mod;
		a[0]=na[0];a[1]=na[1];
	}
	
	v[sz-1]^=(1ll<<t1);if(v[sz-1]==0)v.pop_back();
	return (a[t1==t2]+calc(v,k^(1ll<<t1)))%mod;
}

int ans;
void dfs(int msk,int vmsk,LL coef)
{
	if(!coef)return;
	if(msk==0)
	{
		ans=(ans+val[vmsk]*coef)%mod;
		return;
	}
	int t=__builtin_ctz(msk);msk^=1<<t;
	for(int tmsk=msk;;tmsk=(tmsk-1)&msk)
	{
		int nmsk=tmsk|(1<<t);
		if(bits[nmsk]&1)dfs(msk^tmsk,vmsk|(1<<mn[nmsk]),coef*f[nmsk]%mod);
		else dfs(msk^tmsk,vmsk,coef*f[nmsk]%mod*((a[mn[nmsk]]+1)%mod)%mod);
		if(tmsk==0)break;
	}
}

int main()
{
	prework();
	
	get3(n,m,c);
	for(int i=0;i<n;i++)get1(a[i]);
	for(int i=0,u,v;i<m;i++)
	{
		get2(eu[i],ev[i]);
		eu[i]--;ev[i]--;
	}
	for(int i=0;i<(1<<n);i++)
	{
		vector<LL> v;
		mn[i]=-1;
		for(int j=0;j<n;j++)if(getcode(i,j))
		{
			v.pb(a[j]);
			if(mn[i]==-1||a[mn[i]]>a[j])mn[i]=j;
		}
		val[i]=calc(v,c);
	}
	
	for(int i=0;i<(1<<n);i++)
	{
		f[i]=1;
		for(int j=0;j<m;j++)if(getcode(i,eu[j])&&getcode(i,ev[j]))f[i]=0;
	}
	
	for(int i=0;i<(1<<n);i++)ft[bits[i]][i]=f[i];
	for(int i=0;i<=n;i++)fmt(ft[i],n,0);
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=0;j<=n;j++)tmp[j]=ft[j][i];
		poly_ln(tmp,tmp,n+1,n+1);
		for(int j=0;j<=n;j++)ft[j][i]=tmp[j];
	}
	for(int i=0;i<=n;i++)fmt(ft[i],n,1);
	for(int i=0;i<(1<<n);i++)f[i]=ft[bits[i]][i];
	
	dfs((1<<n)-1,0,1);
	printendl(ans);
	
	return 0;
}
