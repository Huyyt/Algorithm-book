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
//My i/o stream
struct fastio
{
	char s[100000];
	int it,len;
	fastio(){it=len=0;}
	inline char get()
	{
		if(it<len)return s[it++];it=0;
		len=fread(s,1,100000,stdin);
		if(len==0)return EOF;else return s[it++];
	}
	bool notend()
	{
		char c=get();
		while(c==' '||c=='\n')c=get();
		if(it>0)it--;
		return c!=EOF;
	}
}_buff;
#define geti(x) x=getnum()
#define getii(x,y) geti(x),geti(y)
#define getiii(x,y,z) getii(x,y),geti(z)
#define puti(x) putnum(x),putchar(' ')
#define putii(x,y) puti(x),puti(y)
#define putiii(x,y,z) putii(x,y),puti(z)
#define putsi(x) putnum(x),putchar('\n')
#define putsii(x,y) puti(x),putsi(y)
#define putsiii(x,y,z) putii(x,y),putsi(z)
inline ll getnum()
{
	ll r=0;bool ng=0;char c;c=_buff.get();
	while(c!='-'&&(c<'0'||c>'9'))c=_buff.get();
	if(c=='-')ng=1,c=_buff.get();
	while(c>='0'&&c<='9')r=r*10+c-'0',c=_buff.get();
	return ng?-r:r;
}
template<class T> inline void putnum(T x)
{
	if(x<0)putchar('-'),x=-x;
	register short a[20]={},sz=0;
	while(x)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1;i>=0;i--)putchar('0'+a[i]);
}
inline char getreal(){char c=_buff.get();while(c<=32)c=_buff.get();return c;}
const int mod=1002030409;
const int maxm=20;
const int maxn=1<<maxm;
int n,m;
int sum;
int a[maxn],b[maxn],cnt1[maxn];
inline void upd(int &x,int v){x=x+v>=mod?x+v-mod:x+v;}
int fwt(int a[])
{
	for(int i=0;i<m;i++)
	{
		int t=1<<i;
		for(int j=0;j<(1<<m);j++)
		{
			if((j>>i)&1)continue;
			int tmp=a[j+t];
			upd(a[j+t],mod-a[j]);
			a[j+t]=mod-a[j+t];
			upd(a[j],tmp);
		}
	}
}
int query(int a[],int x)
{
	int ret=0;
	for(int i=0;i<(1<<m);i++)
	{
		if(cnt1[i&x]&1)upd(ret,mod-a[i]);
		else upd(ret,a[i]);
	}
	return ret;
}
int main()
{
	geti(n);
	int sum=0,mx=0;
	for(int i=1;i<=n;i++)
	{
		int x;
		geti(x);
		sum^=x;
		a[x]=1;
		mx=max(mx,x);
	}
	while((1<<m)<=mx)m++;
	assert(m<maxm);
	for(int i=1;i<(1<<m);i++)cnt1[i]=cnt1[i-(i&(-i))]+1;
	fwt(a);
	b[0]=1;
	for(int i=0;i<(1<<m);i++)b[i]=1;
	for(int i=0;i<m;i++)
	{
		if(query(b,sum)%mod!=0)
		{
			cout<<n-i<<endl;
			return 0;
		}
		for(int j=0;j<(1<<m);j++)b[j]=1ll*b[j]*a[j]%mod;
	}
	cout<<n-m<<endl;
	return 0;
}

