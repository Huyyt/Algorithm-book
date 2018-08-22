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

const int maxn=100111;
struct suffix_array
{
	int sa[maxn],t[maxn],t2[maxn],c[maxn],n;
	int rk[maxn],v[20][maxn],lg[maxn];
	void construct_sa(char*s)
	{
		vector<int> all;for(int i=0;i<n;i++)all.pb(s[i]);
		sort(all.begin(),all.end());all.erase(unique(all.begin(),all.end()),all.end());
		
		int m=all.size();
		for(int i=0;i<n;i++)s[i]=lower_bound(all.begin(),all.end(),s[i])-all.begin();
		
		int *x=t,*y=t2;
		for(int i=0;i<m;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]=s[i]]++;
		for(int i=1;i<m;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
		
		for(int k=1;k<=n;k<<=1)
		{
			int p=0;
			for(int i=n-k;i<n;i++)y[p++]=i;
			for(int i=0;i<n;i++)if(sa[i]>=k)y[p++]=sa[i]-k;
			for(int i=0;i<m;i++)c[i]=0;
			for(int i=0;i<n;i++)c[x[y[i]]]++;
			for(int i=1;i<m;i++)c[i]+=c[i-1];
			for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
			swap(x,y);
			x[sa[0]]=0;p=1;
			for(int i=1;i<n;i++)x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
			if(p>=n)break;
			m=p;
		}
	}
	void construct_lcp(char*s)
	{
		int k=0;
		for(int i=0;i<n;i++)rk[sa[i]]=i;
		for(int i=0;i<n-1;i++)
		{
			if(k)k--;
			int j=sa[rk[i]-1];
			while(s[i+k]==s[j+k])k++;
			v[0][rk[i]]=k;
		}
		for(int i=2;i<n;i++)lg[i]=lg[i>>1]+1;
		for(int i=1;i<20;i++)
		{
			for(int j=2;j<n;j++)
			{
				int nxt=j+(1<<i-1);
				if(nxt>=n)v[i][j]=v[i-1][j];
				else v[i][j]=min(v[i-1][j],v[i-1][nxt]);
			}
		}
	}
	int qlcp(int l,int r)const
	{
		l=rk[l];
		r=rk[r];
		if(l>r)swap(l,r);
		int t=lg[r-l];
		return min(v[t][l+1],v[t][r-(1<<t)+1]);
	}
}sa,rsa;

vector<int> vs[100111],pre[100111];
vector<LL>dpv[100111];

bool done[1200111];
int spre[100111];

LL dp[100111];

char s[100111];
int n,a,b,cnt;
void solve()
{
	get2(a,b);scanf("%s",s);n=strlen(s);
	sa.n=rsa.n=n+1;
	sa.construct_sa(s);sa.construct_lcp(s);
	reverse(s,s+n);rsa.construct_sa(s);rsa.construct_lcp(s);
	
	memset(done,0,sizeof(done));
	for(int i=1;i<=n;i++)spre[i]=spre[i-1]+n/i;
	
	for(int i=0;i<n;i++){vs[i].clear();pre[i].clear();}
	
	cnt=0;
	for(int len=1;len+len<=n;len++)
	{
		for(int i=len;i+len<=n;i+=len)if(!done[spre[len-1]+i/len])//[i,i+len-1]
		{
			int r=sa.qlcp(i-1,i+len-1),l=rsa.qlcp(n-i,n-i-len);
			if(l+r<len+1)continue;
			l=i-l;r=i+len-1+r-1;
			for(int nl=len;nl+nl<=r-l+1;nl+=len)for(int nk=(l+nl-1)/nl*nl;nk+nl<=r+1;nk+=nl)
				done[spre[nl-1]+nk/nl]=1;
			for(int j=l+len+len-1;j<=r;j++)
			{
				cnt++;
				vs[j].pb(len);
				if(j-len>=l+len+len-1)pre[j].pb((int)vs[j-len].size()-1);
				else pre[j].pb(-1);
			}
		}
	}
	LL mn=a;dp[0]=a+b;
	for(int i=1;i<n;i++)
	{
		dp[i]=mn+a+b;
		dpv[i].resize(vs[i].size());
		for(int j=0;j<(int)vs[i].size();j++)
		{
			if(i<vs[i][j]<<1)dpv[i][j]=1ll*vs[i][j]*a+b;
			else dpv[i][j]=1ll*vs[i][j]*a+b+dp[i-vs[i][j]-vs[i][j]];
			if(pre[i][j]!=-1)dpv[i][j]=min(dpv[i][j],dpv[i-vs[i][j]][pre[i][j]]);
			dp[i]=min(dp[i],dpv[i][j]);
		}
		mn=min(dp[i],mn+a);
	}
	printendl(dp[n-1]);
}
int main()
{
	int tc;get1(tc);
	while(tc--)solve();
	return 0;
}
