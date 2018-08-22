#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char ch;
	do
	{
		ch=getchar();
		if (ch=='-')
		{
			f=-f;
		}
	}while (ch<'0' || ch>'9');
	do
	{
		x=x*10+ch-'0';
		ch=getchar();
	}while (ch>='0' && ch<='9');
	return x*f;
}
const long long Mod=998244353;
int n;
long long pw3[600010],pwinv3[600010];
long long pw(long long x,long long y)
{
	long long res=1;
	while (y)
	{
		if (y&1)
		{
			res=res*x%Mod;
		}
		x=x*x%Mod;
		y>>=1;
	}
	return res;
}
void pre()
{
	long long inv3=pw(3,Mod-2);
	for (int i=1;i<=n;i<<=1)
	{
		pw3[i]=pw(3,(Mod-1)/i);
		pwinv3[i]=pw(inv3,(Mod-1)/i);
	}
}
void rader(long long *a)
{
	for (int i=0,j=0;i<n;i++)
	{
		if (i>j)
		{
			swap(a[i],a[j]);
		}
		int k=n;
		do
		{
			k>>=1;
			j^=k;
		}while (j<k);
	}
}
void ntt(long long *a,long long f)
{
	rader(a);
	for (int i=2;i<=n;i<<=1)
	{
		int m=i>>1;
		for (int j=0;j<n;j+=i)
		{
			long long w=1,wn=pw3[i];
			if (f==-1)
			{
				wn=pwinv3[i];
			}
			for (int k=0;k<m;k++)
			{
				long long x=a[j+k+m]*w%Mod;
				a[j+k+m]=(a[j+k]-x+Mod)%Mod;
				a[j+k]=(a[j+k]+x)%Mod;
				w=w*wn%Mod;
			}
		}
	}
	if (f==-1)
	{
		long long inv=pw(n,Mod-2);
		for (int i=0;i<n;i++)
		{
			a[i]=a[i]*inv%Mod;
		}
	}
}
void conv(long long *a,long long *b)
{
	ntt(a,1);
	ntt(b,1);
	for (int i=0;i<n;i++)
	{
		a[i]=a[i]*b[i]%Mod;
	}
	ntt(a,-1);
}
int m;
long long a[600010],b[600010],f[600010];
void update(int l,int r)
{
	int mid=(l+r)>>1;
	n=1;
	while (n<((r-l+1)<<1))
	{
		n<<=1;
	}
	for (int i=0;i<n;i++)
	{
		a[i]=b[i]=0;
	}
	for (int i=0;i<=mid-l;i++)
	{
		a[i]=f[i+l];
	}
	for (int i=0;i<r-l;i++)
	{
		if (i+1>=l && i+1<=mid)
		{
			b[i]=f[i+1];
		}
		else
		{
			b[i]=f[i+1]*2%Mod;
		}
	}
	conv(a,b);
	for (int i=mid+1;i<=r;i++)
	{
		f[i]=(f[i]+a[i-l-1])%Mod;
	}
}
void solve(int l,int r)
{
	if (l==r)
	{
		f[l]=(f[l]+f[l-1])%Mod;
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	update(l,r);
	solve(mid+1,r);
}
int main()
{
	scanf("%d",&m);
	n=1;
	while (n<(m<<1))
	{
		n<<=1;
	}
	pre();
	f[0]=1;
	solve(1,m);
	printf("%lld\n",f[m]);
	return 0;
}
