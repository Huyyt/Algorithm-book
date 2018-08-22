//by yjz
#include<bits/stdc++.h>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
#define bged(v) (v).begin(),(v).end()
#define foreach(it,s) for(__typeof((s).begin()) it=(s).begin();it!=(s).end();it++)
typedef long long ll;
const int Imx=2147483647;
const ll Lbig=2e18;

/*
	Template: Polynomial V2(Simplified)
	Author: FizzyDavid
	Last edit: 2018/05/28
*/
//Settings
#define useNTT //if you use the NTT head
const int mod=998244353;//mod SHOULD be prime
const int proot=3;//for NTT only
const int FFTbitn=20;
const int FFTpmx=1<<FFTbitn;
const int FFTmx=FFTpmx+233;
const int FFTbit=15;//for FFT only  max_value=2^(2*FFTbit)
const int comb_mx=FFTmx;

//Prerequisite
typedef unsigned long long ull;
ll qpow(ll x,ll k){return k==0?1:qpow(x*x%mod,k>>1)*(k&1?x:1)%mod;}
const double pi=acos(-1);
struct point
{
	double x,y;
	point(double _x=0,double _y=0){x=_x;y=_y;}
	point operator+(const point &t)const{return point(x+t.x,y+t.y);}
	point operator-(const point &t)const{return point(x-t.x,y-t.y);}
	point operator*(const point &t)const{return point(x*t.x-y*t.y,x*t.y+y*t.x);}
	point conj()const{return point(x,-y);}
};

//Comb
ll inv[comb_mx],fac[comb_mx],ifac[comb_mx];
void comb_init()
{
	assert(comb_mx<=mod);
	fac[0]=1;
	for(int i=1;i<comb_mx;i++)fac[i]=fac[i-1]*i%mod;
	ifac[comb_mx-1]=qpow(fac[comb_mx-1],mod-2);
	for(int i=comb_mx-2;i>=0;i--)ifac[i]=ifac[i+1]*(i+1)%mod;
	inv[1]=1;
	for(int i=2;i<comb_mx;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}

//FFT
int fsz;
int uptopow(int x){while(x!=(x&(-x)))x+=x&(-x);return x;}
void FFTinit(int sz){fsz=uptopow(sz);assert(fsz<=FFTpmx);}
void FFTprecalc();
#ifdef useNTT
void FFT(int a[],int coef);
#else
void FFT(point a[],int coef);
#endif

//Mul
void polymul(int a[],int an,int b[],int bn,int c[],int cn);

//Basic
void polyclear(int a[],int n){for(int i=0;i<n;i++)a[i]=0;}
void polyclear(int a[],int l,int r){for(int i=l;i<r;i++)a[i]=0;}

void polyset(int a[],int an,int b[],int bn){for(int i=0;i<bn;i++)b[i]=i<an?a[i]:0;}

void polyadd(int a[],int an,int b[],int bn,int c[],int cn){for(int i=0;i<cn;i++)c[i]=((i<an?a[i]:0)+(i<bn?b[i]:0))%mod;}
void polyadd(int a[],int b[],int c[],int sz){polyadd(a,sz,b,sz,c,sz);}

void polysub(int a[],int an,int b[],int bn,int c[],int cn){for(int i=0;i<cn;i++)c[i]=((i<an?a[i]:0)-(i<bn?b[i]:0)+mod)%mod;}
void polysub(int a[],int b[],int c[],int sz){polysub(a,sz,b,sz,c,sz);}

void polyaddinv(int a[],int an,int b[],int bn){for(int i=0;i<bn;i++)b[i]=(mod-(i<an?a[i]:0))%mod;}
void polyaddinv(int a[],int n,int b[]){polyaddinv(a,n,b,n);}
void polyaddinv(int a[],int n){polyaddinv(a,n,a,n);}

void polymulnum(int a[],int an,int b,int c[],int cn){for(int i=0;i<cn;i++)c[i]=1ll*(i<an?a[i]:0)*b%mod;}
void polymulnum(int a[],int b,int c[],int n){polymulnum(a,n,b,c,n);}
void polymulnum(int a[],int b,int n){polymulnum(a,n,b,a,n);}

//Qpow
void polyqpow(int a[],int an,int k,int b[],int bn);

//Inv   a[0] SHOULDN'T BE 0
void polyinv(int a[],int an,int b[],int bn);
void polyinv(int a[],int n,int b[]){polyinv(a,n,b,n);}
void polyinv(int a[],int n){polyinv(a,n,a,n);}

const int maxn=500111;
int n,f[maxn];
int g[maxn];
void push(int l0,int r0,int l1,int r1,int l2,int r2)
{
	static int tmp[FFTmx];
	int sz=r0-l0+r1-l1;
	polymul(f+l0,r0-l0+1,g+l1,r1-l1+1,tmp,sz+1);
	for(int i=0;i<=sz&&l0+l1+i<=n;i++)
	{
		if(l0+l1+i>=l2&&l0+l1+i<=r2)f[i+l0+l1]=(f[i+l0+l1]+tmp[i])%mod;
	}
}
void solve(int l,int r,bool flag)
{
	if(l==r)
	{
		if(l>1)g[l]=f[l];
		return;
	}
	int m=l+r>>1;
	solve(l,m,flag);
	if(flag)push(l,m,l,m,m+1,r);
	else push(l,m,1,r-l,m+1,r),push(1,r-l,l,m,m+1,r);
	solve(m+1,r,flag&0);
}
int main()
{
	FFTprecalc();
	comb_init();
	cin>>n;
	f[1]=1;
	g[1]=2;
	solve(1,n,1);
	cout<<f[n]<<endl;
	return 0;
}

//===========================================================================

//Head
#ifdef useNTT
	int w_pre[FFTmx];
	void FFTprecalc()
	{
		w_pre[0]=1;
		int ww=qpow(proot,(mod-1)/FFTpmx);
		for(int i=1;i<=FFTpmx;i++)w_pre[i]=1ll*w_pre[i-1]*ww%mod;
	}
	void FFT(int a[],int coef)
	{
		static ull f_a[FFTmx];
		static int w[FFTmx];
		for(int i=0,j=0;i<fsz;i++)
		{
			f_a[j]=a[i]<0?a[i]+mod:a[i];
			for(int l=fsz>>1;(j^=l)<l;l>>=1);
		}
		const ull md2=1ull*mod*mod;
		for(int l=1;l<fsz;l<<=1)
		{
			int l2=l<<1,u=FFTpmx/l2;
			if(coef==1)for(int j=0,j2=0;j<l;j++,j2+=u)w[j]=w_pre[j2];
			else for(int j=0,j2=FFTpmx;j<l;j++,j2-=u)w[j]=w_pre[j2];
			for(int i=0;i<fsz;i+=l2)
			{
				for(int j=0;j<l;j++)
				{
					ull tmp=f_a[i+j+l]%mod*w[j];
					f_a[i+j+l]=f_a[i+j]+md2-tmp;
					f_a[i+j]+=tmp;
				}
			}
			if(l==(1<<16))for(int j=0;j<fsz;j++)f_a[j]%=mod;
		}
		for(int i=0;i<fsz;i++)a[i]=f_a[i]%mod;
		if(coef==-1)
		{
			int inv=qpow(fsz,mod-2);
			for(int i=0;i<fsz;i++)a[i]=1ll*a[i]*inv%mod;
		}
	}
	void polymul(int a[],int an,int b[],int bn,int c[],int cn=-1)
	{
		static int mul_a[FFTmx],mul_b[FFTmx];
		if(cn==-1)cn=an+bn;
		an=min(an,cn);bn=min(bn,cn);
		if(1ll*an*bn<=4096)
		{
			for(int i=0;i<an+bn;i++)mul_a[i]=0;
			for(int i=0;i<an;i++)
				for(int j=0;j<bn;j++)
					mul_a[i+j]=(mul_a[i+j]+1ll*a[i]*b[j])%mod;
			for(int i=0;i<cn;i++)c[i]=mul_a[i];
			return;
		}
		FFTinit(an+bn);
		for(int i=0;i<fsz;i++)mul_a[i]=i<an?a[i]:0;
		for(int i=0;i<fsz;i++)mul_b[i]=i<bn?b[i]:0;
		FFT(mul_a,1);
		FFT(mul_b,1);
		for(int i=0;i<fsz;i++)mul_a[i]=1ll*mul_a[i]*mul_b[i]%mod;
		FFT(mul_a,-1);
		for(int i=0;i<cn;i++)c[i]=mul_a[i];
	}
#else
	point w_pre[FFTmx];
	void FFTprecalc()
	{
		for(int i=0;i<=FFTpmx;i++)w_pre[i]=point(cos(2.0/FFTpmx*i*pi),sin(2.0/FFTpmx*i*pi));
	}
	void FFT(point a[],int coef)
	{
		static point w[FFTmx];
		for(int i=0,j=0;i<fsz;i++)
		{
			if(i<j)swap(a[i],a[j]);
			for(int l=fsz>>1;(j^=l)<l;l>>=1);
		}
		for(int l=1;l<fsz;l<<=1)
		{
			int l2=l<<1,u=FFTpmx/l2;
			if(coef==1)for(int j=0,j2=0;j<l;j++,j2+=u)w[j]=w_pre[j2];
			else for(int j=0,j2=FFTpmx;j<l;j++,j2-=u)w[j]=w_pre[j2];
			for(int i=0;i<fsz;i+=l2)
			{
				for(int j=0;j<l;j++)
				{
					point tmp=a[i+l+j]*w[j];
					a[i+l+j]=a[i+j]-tmp;
					a[i+j]=a[i+j]+tmp;
				}
			}
		}
		if(coef==-1)
		{
			for(int i=0;i<fsz;i++)a[i]=a[i]*(1.0/fsz);
		}
	}
	void polymul(int a[],int an,int b[],int bn,int c[],int cn=-1)
	{
		static point tl[FFTmx],tr[FFTmx],ta[FFTmx],tb[FFTmx];
		if(cn==-1)cn=an+bn;
		an=min(an,cn);bn=min(bn,cn);
		FFTinit(an+bn);
		int msk=(1<<FFTbit)-1;
		for(int i=0;i<fsz;i++)
		{
			ta[i]=i<an?point((a[i]>=0?a[i]:a[i]+mod)&msk,(a[i]>=0?a[i]:a[i]+mod)>>FFTbit):0;
			tb[i]=i<bn?point((b[i]>=0?b[i]:b[i]+mod)&msk,(b[i]>=0?b[i]:b[i]+mod)>>FFTbit):0;
		}
		FFT(ta,1);ta[fsz]=ta[0];
		FFT(tb,1);tb[fsz]=tb[0];
		for(int i=0;i<fsz;i++)
		{
			point a0=(ta[i]+ta[fsz-i].conj())*point(+0.5,0),a1=(ta[i]-ta[fsz-i].conj())*point(0,-0.5);
			point b0=(tb[i]+tb[fsz-i].conj())*point(+0.5,0),b1=(tb[i]-tb[fsz-i].conj())*point(0,-0.5);
			tl[i]=a0*b0+a0*b1*point(0,1);
			tr[i]=a1*b0+a1*b1*point(0,1);
		}
		FFT(tl,-1);
		FFT(tr,-1);
		for(int i=0;i<fsz;i++)
		{
			c[i]=(ll(tl[i].x+0.5)+
			    ((ll(tr[i].y+0.5)%mod)<<(FFTbit+FFTbit))+
		       (((ll(tl[i].y+0.5)+ll(tr[i].x+0.5))%mod)<<FFTbit))%mod;
		}
	}
#endif

//Qpow
void polyqpow(int a[],int an,int k,int b[],int bn=-1)
{
	if(bn==-1)bn=(an-1)*k+1;
	static int pow_ans[FFTmx],pow_x[FFTmx];
	copy(a,a+an,pow_x);
	pow_ans[0]=1;
	int ansn=1;
	while(k>0)
	{
		if(k&1)
		{
			polymul(pow_ans,ansn,pow_x,an,pow_ans);
			ansn=min(ansn+an,bn);
		}
		polymul(pow_x,an,pow_x,an,pow_x);
		an=min(an+an,bn);
		k>>=1;
	}
	for(int i=0;i<bn;i++)b[i]=i<ansn?pow_ans[i]:0;
}


//Inv
void polyinv_s(int a[],int n,int b[])
{
	static int inv_a[FFTmx],inv_b[FFTmx];
	assert(a!=b);
	if(n==1)
	{
		assert(a[0]!=0);
		b[0]=qpow(a[0],mod-2);
		return;
	}
	int nn=n>>1;
	polyinv_s(a,nn,b);
#ifdef useNTT
	FFTinit(n+n);
	polyset(b,nn,inv_a,fsz);
	FFT(inv_a,1);
	polyset(a,n,inv_b,fsz);
	FFT(inv_b,1);
	for(int i=0;i<fsz;i++)inv_a[i]=1ll*(2ll-1ll*inv_a[i]*inv_b[i]%mod+mod)*inv_a[i]%mod;
	FFT(inv_a,-1);
	polyset(inv_a,fsz,b,n);
#else
	polymul(b,nn,a,n,inv_a,n);
	polyaddinv(inv_a,n);
	inv_a[0]=(inv_a[0]+2)%mod;
	polymul(b,nn,inv_a,n,b,n);
#endif
}
void polyinv(int a[],int an,int b[],int bn)
{
	static int inv_ta[FFTmx],inv_tb[FFTmx];
	int sz=uptopow(bn);
	polyset(a,an,inv_ta,sz);
	polyinv_s(inv_ta,sz,inv_tb);
	polyset(inv_tb,sz,b,bn);
}

