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
const int poly_bits=19;
const int poly_max=1<<poly_bits;//poly_max=2^poly_bits
const int mod=998244353;//a prime in the form of k*poly_max+1 if NTT
const int root=3;//a primitive root of mod

int qpow(int x,int y,const int&mod=::mod){int ret=1;do{if(y&1)ret=1ll*ret*x%mod;x=1ll*x*x%mod;}while(y>>=1);return ret;}
inline int up_pw2(const int&x){int ret=1;while(ret<x)ret<<=1;return ret;}
int inv[poly_max+1],fac[poly_max+1],invf[poly_max+1];

#define NTT
//#define COMB

#ifdef COMB
	int comb(int x,int y){if(x<y||y<0)return 0;return 1ll*fac[x]*invf[y]%mod*invf[x-y]%mod;}
#endif

#ifdef NTT
	#define type int
	static int w[poly_max+1];
#else
	#define type cpx
	inline int dcmp(const double&x){if(fabs(x)<eps)return 0;else if(x<0)return -1;else return 1;}
	struct cpx
	{
		double x,y;
		cpx(double _x=0,double _y=0){x=_x;y=_y;}
		bool operator ==(const cpx&b)const{return dcmp(b.x-x)==0&&dcmp(b.y-y)==0;}
		cpx operator+(const cpx &t){return cpx(x+t.x,y+t.y);}
		cpx operator-(const cpx &t){return cpx(x-t.x,y-t.y);}
		cpx operator*(const cpx &t){return cpx(x*t.x-y*t.y,x*t.y+y*t.x);}
		cpx operator*(const double &t){return cpx(x*t,y*t);}
		cpx conj()const{return cpx(x,-y);}
		cpx inv()const{return cpx(x/(x*x+y*y),-y/(x*x+y*y));}
	};
	cpx w[poly_max+1];
#endif
template<typename tp>int simplify(tp*a,int n){while(n&&a[n-1]==tp(0))n--;return n;}
void copy(int*a,int*b,int n,int m){for(int i=0;i<m;i++)b[i]=(i<n?a[i]:0);}
#ifndef NTT
void copy(cpx*a,cpx*b,int n,int m){for(int i=0;i<m;i++)b[i]=(i<n?a[i]:cpx(0));}
#endif

void prework();

void dft(type*a,int n);
void idft(type*a,int n);

void poly_derive(int*a,int*b,int n);

#ifdef COMB
void poly_integral(int*a,int*b,int n);
#endif

void poly_add(int*a,int*b,int*c,int n,int m);
#ifndef NTT
void poly_add(cpx*a,cpx*b,cpx*c,int n,int m);
#endif
void poly_sub(int*a,int*b,int*c,int n,int m);
#ifndef NTT
void poly_sub(cpx*a,cpx*b,cpx*c,int n,int m);
#endif

void poly_dotmul(int*a,int*b,int*c,int n,int m);
#ifndef NTT
void poly_dotmul(cpx*a,cpx*b,cpx*c,int n,int m);
#endif

void poly_mult(type*a,type*b,type*c,int n,int m);
#ifndef NTT
void poly_mult(int*a,int*b,int*c,int n,int m);
#endif

void poly_cyc_mult(type*a,type*b,type*c,int n);
#ifndef NTT
void poly_cyc_mult(int*a,int*b,int*c,int n);
#endif

void poly_inv(int*a,int*b,int n,int m);

void poly_rdiv(int*a,int*invb,int*c,int n,int m);
void poly_div(int*a,int*b,int*c,int n,int m);
int poly_kdiv(int*a,int*b,int*c,int n,int m);

void poly_rmod(int*a,int*b,int*invb,int*c,int n,int m);
void poly_mod(int*a,int*b,int*c,int n,int m);
int poly_kmod(int*a,int*b,int*c,int n,int m);

void poly_qpow(int*a,int*b,int n,int k,int m);

void poly_sqrt(int*a,int*b,int n,int m);

#ifdef COMB
void poly_ln(int*a,int*b,int n,int m);
void poly_exp(int*a,int*b,int n,int m);
void poly_pow(int*a,int*b,int n,int k,int m);
#endif

/* unfinished: MTT*2

void evaluation(int*a,int*b,int*c,int n,int m);

void interpolation(int*a,int*b,int n);

*/


int a[300111],n;
int main()
{
	freopen("rua.in","r",stdin);
	freopen("rua.out","w",stdout);
	prework();
	get1(n);
	if(n==0||n==1)
	{
		puts("1");
		return 0;
	}
	a[0]=1;a[1]=mod-6;a[2]=1;
	poly_sqrt(a,a,3,n+1);
	printf("%d\n",(mod-1ll*a[n]*(mod+1)/2%mod+mod)%mod);
	return 0;
}


void prework()
{
#ifdef NTT
	w[0]=1;w[1]=qpow(root,mod-1>>poly_bits);
	for(int i=2;i<=poly_max;i++)w[i]=1ll*w[i-1]*w[1]%mod;
#else
	for(int i=0;i<=poly_max;i++)w[i]=cpx(cos(2*pi/poly_max*i),sin(2*pi/poly_max*i));
#endif
#ifdef COMB
	fac[0]=inv[0]=invf[0]=1;
	for(int i=1;i<=poly_max;i++)
	{
		fac[i]=1ll*i*fac[i-1]%mod;
		inv[i]=qpow(i,mod-2);
		invf[i]=1ll*inv[i]*invf[i-1]%mod;
	}
#endif
}

void poly_dotmul(int*a,int*b,int*c,int n,int m){for(int i=0;i<n||i<m;i++)c[i]=(i<n&&i<m?1ll*a[i]*b[i]%mod:0);}
#ifndef NTT
void poly_dotmul(cpx*a,cpx*b,cpx*c,int n,int m){for(int i=0;i<n||i<m;i++)c[i]=(i<n&&i<m?a[i]*b[i]:cpx(0));}
#endif

void poly_add(int*a,int*b,int*c,int n,int m){for(int i=0;i<n||i<m;i++){c[i]=(i<n?a[i]:0)+(i<m?b[i]:0);if(c[i]>=mod)c[i]-=mod;}}
#ifndef NTT
void poly_add(cpx*a,cpx*b,cpx*c,int n,int m){for(int i=0;i<n||i<m;i++){c[i]=(i<n?a[i]:cpx(0))+(i<m?b[i]:cpx(0));}}
#endif
void poly_sub(int*a,int*b,int*c,int n,int m){for(int i=0;i<n||i<m;i++){c[i]=(i<n?a[i]:0)-(i<m?b[i]:0);if(c[i]<0)c[i]+=mod;}}
#ifndef NTT
void poly_sub(cpx*a,cpx*b,cpx*c,int n,int m){for(int i=0;i<n||i<m;i++){c[i]=(i<n?a[i]:cpx(0))-(i<m?b[i]:cpx(0));}}
#endif

inline void dft(type*a,int n)
{
	for(int i=0,j=0;i<n;i++){if(i<j)swap(a[i],a[j]);for(int t=n>>1;(j^=t)<t;t>>=1);}
	for(int l=1,d=1;l<n;l<<=1,d++)
	{
		int l2=l<<1;
		for(int i=0;i<n;i+=l2)for(int j=0;j<l;j++)
		{
#ifdef NTT
			int tmp=1ll*a[i|l|j]*w[j<<poly_bits-d]%mod;
			a[i|l|j]=a[i|j]-tmp+mod;if(a[i|l|j]>=mod)a[i|l|j]-=mod;
			a[i|j]+=tmp;if(a[i|j]>=mod)a[i|j]-=mod;
#else
			cpx tmp=a[i|l|j]*w[j<<poly_bits-d];
			a[i|l|j]=a[i|j]-tmp;
			a[i|j]=a[i|j]+tmp;
#endif
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
#ifdef NTT
			int tmp=1ll*a[i|l|j]*w[poly_max-(j<<poly_bits-d)]%mod;
			a[i|l|j]=a[i|j]-tmp+mod;if(a[i|l|j]>=mod)a[i|l|j]-=mod;
			a[i|j]+=tmp;if(a[i|j]>=mod)a[i|j]-=mod;
#else
			cpx tmp=a[i|l|j]*w[poly_max-(j<<poly_bits-d)];
			a[i|l|j]=a[i|j]-tmp;
			a[i|j]=a[i|j]+tmp;
#endif
		}
	}
#ifdef NTT
	int inv=qpow(n,mod-2);for(int i=0;i<n;i++)a[i]=1ll*a[i]*inv%mod;
#else
	for(int i=0;i<n;i++)a[i]=a[i]*cpx(1.0/n);
#endif
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
#ifndef NTT
void poly_mult(int*a,int*b,int*c,int n,int m)
{
	
}
#endif

void poly_cyc_mult(type*a,type*b,type*c,int n)
{
	copy(a,ttA,n,n);
	copy(b,ttB,n,n);
	dft(ttA,n);dft(ttB,n);
	poly_dotmul(ttA,ttB,ttA,n,n);
	idft(ttA,n);
	copy(ttA,c,n,n);
}
#ifndef NTT
void poly_cyc_mult(int*a,int*b,int*c,int n)
{
	
}
#endif

static int tA[poly_max],tB[poly_max],tC[poly_max],tD[poly_max],tE[poly_max];
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

void poly_rdiv(int*a,int*invb,int*c,int n,int m)
{
	assert(n>=m);
	int l=up_pw2(n+n-m-m+1);
	for(int i=0;i<l;i++)
	{
		tA[i]=(i<=n-m?a[n-i-1]:0);
		tB[i]=(i<=n-m?invb[i]:0);
	}
	dft(tA,l);dft(tB,l);
	poly_dotmul(tA,tB,tA,l,l);
	idft(tA,l);
	for(int i=0;i<=n-m;i++)c[i]=tA[n-m-i];
}
void poly_div(int*a,int*b,int*c,int n,int m)
{
	for(int i=0;i<m;i++)tC[i]=b[m-i-1];
	poly_inv(tC,tC,m,n-m+1);
	poly_rdiv(a,tC,c,n,m);
}
int poly_kdiv(int*a,int*b,int*c,int n,int m)
{
	n=simplify(a,n);m=simplify(b,m);
	if(n<m)return 0;
	assert(m>1);
	poly_div(a,b,c,n,m);
	return n-m+1;
}

void poly_rmod(int*a,int*b,int*invb,int*c,int n,int m)
{
	assert(m>1);
	poly_rdiv(a,invb,tC,n,m);
	poly_mult(b,tC,tC,m-1,min(n-m+1,m-1));
	poly_sub(a,tC,c,m-1,m-1);
}
void poly_mod(int*a,int*b,int*c,int n,int m)
{
	if(n<=m)
	{
		copy(a,c,n,m-1);
		return;
	}
	assert(m>1);
	poly_div(a,b,tC,n,m);
	poly_mult(b,tC,tC,m-1,min(m-1,n-m+1));
	poly_sub(a,tC,c,m-1,m-1);
}
int poly_kmod(int*a,int*b,int*c,int n,int m)
{
	n=simplify(a,n);m=simplify(b,m);
	poly_mod(a,b,c,n,m);
	return m-1;
}


void poly_qpow(int*a,int*b,int n,int k,int m)
{
	copy(a,tA,n,m);copy(b,tB,0,m);tB[0]=1;
	while(k)
	{
		if(k&1)poly_mult(tB,tA,tB,m,m);
		k>>=1;
		if(k)poly_mult(tA,tA,tA,m,m);
	}
	copy(tB,b,m,m);
}

void poly_sqrt(int*a,int*b,int n,int m)
{
	assert(a[0]==1);
	int tn=up_pw2(m);
	tD[0]=1;
	for(int l=2;l<=tn;l<<=1)
	{
		int l2=l<<1;
		copy(a,tC,min(n,l),l2);
		poly_inv(tD,tB,l>>1,l);
		copy(tB,tB,l,l2);
		dft(tB,l2);dft(tC,l2);
		poly_dotmul(tB,tC,tB,l2,l2);
		idft(tB,l2);
		for(int i=l>>1;i<l;i++)
		{
			if(tB[i]&1)tD[i]=tB[i]+mod>>1;
			else tD[i]=tB[i]>>1;
		}
	}
	copy(tD,b,m,m);
}

void poly_derive(int*a,int*b,int n){for(int i=1;i<n;i++)b[i-1]=1ll*a[i]*i%mod;b[n-1]=0;}
#ifdef COMB
void poly_integral(int*a,int*b,int n){for(int i=n-2;i>=0;i--)b[i+1]=1ll*a[i]*inv[i+1]%mod;b[0]=0;}
#endif

#ifdef COMB
void poly_ln(int*a,int*b,int n,int m)
{
	assert(a[0]==1);
	poly_inv(a,tB,n,m);
	poly_derive(a,tA,m);
	poly_mult(tA,tB,tA,m-1,m-1);
	poly_integral(tA,b,m);
}

void poly_exp(int*a,int*b,int n,int m)
{
	assert(a[0]==0);
	
	int tn=up_pw2(m);
	tD[0]=1;
	for(int l=2;l<=tn;l<<=1)
	{
		int l2=l<<1;
		copy(a,tC,min(n,l),l2);
		copy(tD,tD,l>>1,l2);
		poly_ln(tD,tB,l>>1,l);
		poly_sub(tC,tB,tC,l,l);tC[0]++;if(tC[0]==mod)tC[0]=0;
		
		dft(tC,l2);dft(tD,l2);
		poly_dotmul(tC,tD,tD,l2,l2);
		idft(tD,l2);
	}
	copy(tD,b,m,m);
}

void poly_pow(int*a,int*b,int n,int k,int m)
{
	int fir=0;while(fir<n&&a[fir]==0)fir++;
	if(fir==n||1ll*k*n>=m)
	{
		copy(a,b,0,m);
		return;
	}
	n-=fir;m-=fir*k;
	copy(a+fir,tE,n,n);
	int coef=qpow(tE[0],k),rcoef=qpow(tE[0],mod-2);
	for(int i=0;i<n;i++)tE[i]=1ll*tE[i]*rcoef%mod;
	poly_ln(tE,tE,n,m);
	for(int i=0;i<n;i++)tE[i]=1ll*tE[i]*k%mod;
	poly_exp(tE,tE,m,m);
	for(int i=0;i<fir*k;i++)b[i]=0;
	for(int i=0;i<m;i++)b[i+fir*k]=1ll*tE[i]*coef%mod;
}
#endif
