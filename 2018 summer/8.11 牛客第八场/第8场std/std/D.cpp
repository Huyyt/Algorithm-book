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
const int mod=1e9+7;
ll qpow(ll x,ll k){return k==0?1:1ll*qpow(1ll*x*x%mod,k>>1)*(k&1?x:1)%mod;}
const int maxn=100111;
const int lgn=19;
int lg2[maxn];
struct suffix_array
{
	char s[maxn];
	int n,b[maxn],sa[maxn],nsa[maxn],rk[maxn],nrk[maxn],lcp[maxn];
	int tab[lgn][maxn];
	void makeb(int a[])
	{
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++)b[a[i]]++;
		for(int i=1;i<=max(n,256);i++)b[i]+=b[i-1];
	}
	#define PP(x) MP(rk[x],x+k>n?-1:rk[x+k])
	void construct(char S[],int N)
	{
		n=N;
		for(int i=1;i<=n;i++)s[i]=S[i],rk[i]=s[i];
		makeb(rk);
		for(int i=n;i>=1;i--)sa[b[rk[i]]--]=i;
		for(int k=1;k<n;k<<=1)
		{
			makeb(rk);
			for(int i=n;i>=1;i--)if(sa[i]>k)nsa[b[rk[sa[i]-k]]--]=sa[i]-k;
			for(int i=n;i>=1;i--)if(sa[i]>n-k)nsa[b[rk[sa[i]]]--]=sa[i];
			nrk[nsa[1]]=1;
			for(int i=2;i<=n;i++)nrk[nsa[i]]=nrk[nsa[i-1]]+(PP(nsa[i-1])<PP(nsa[i]));
			swap(sa,nsa);
			swap(rk,nrk);
			if(rk[n]==n)break;
		}
		for(int i=1;i<=n;i++)rk[sa[i]]=i;
		int h=0;
		for(int i=1;i<=n;i++)
		{
			if(h>0)h--;
			if(rk[i]==1)continue;
			int j=sa[rk[i]-1];
			while(i+h<=n&&j+h<=n&&s[i+h]==s[j+h])h++;
			lcp[rk[i]-1]=h;
		}
		for(int i=1;i<=n;i++)tab[0][i]=lcp[i];
		for(int i=1;i<lgn;i++)
		{
			for(int j=1;j<=n-(1<<i)+1;j++)
			{
				tab[i][j]=min(tab[i-1][j],tab[i-1][j+(1<<i-1)]);
			}
		}
	}
	int query_lcp(int x,int y)
	{
		if(x==y)return n-x+1;
		x=rk[x];y=rk[y];if(x>y)swap(x,y);
		int lv=lg2[y-x];
		return min(tab[lv][x],tab[lv][y-(1<<lv)]);
	}
}sa1,sa2;
int n;
char s[maxn];
int A,B;
int sum_inv[maxn];
bool dup[maxn*lgn];
ll dp[maxn];
ll rg[maxn*lgn],rgc[maxn*lgn],rtot;
vector<pair<int,int> > v[maxn];
void Solve()
{
	scanf("%d%d",&A,&B);
	scanf("%s",s+1);
	n=strlen(s+1);
//	cerr<<"---init suffix array"<<endl;
	sa1.construct(s,n);
	reverse(s+1,s+n+1);
	sa2.construct(s,n);
	reverse(s+1,s+n+1);
//	cerr<<"---init cyclic substrings"<<endl;
	for(int i=1;i<=n;i++)v[i].clear();
	rtot=0;
	for(int i=1;i+i<=n;i++)sum_inv[i]=sum_inv[i-1]+n/i-1;
	memset(dup,0,sizeof(dup));
	int SUM=0;
	for(int len=1;len+len<=n;len++)
	{
		int l=0,r=0;
		for(int i=len;i+len<=n;i+=len)
		{
			if(i<=r)continue;
			int l1,l2;
			l1=sa1.query_lcp(i,i+len);
			l2=sa2.query_lcp(n-(i)+1,n-(i+len)+1);
			if(l1+l2-1<len)continue;
			l=i-l2+1;r=i+l1-1;
			if(dup[sum_inv[len-1]+i/len])continue;
			SUM+=r-l+2-len;
			for(int tlen=len+len;l+tlen+tlen-1<=r+len;tlen+=len)
			{
				dup[sum_inv[tlen-1]+(l+tlen-1)/tlen]=1;
			}
			int rbs=rtot;
			for(int j=l;j<=r-len+1;j++)
			{
				if(j<l+len)
				{
					rtot++;
					rgc[rtot]=1ll*len*A+B;
					rg[rtot]=4e18;
				}
				v[j+len+len-1].PB(MP(j-1,(j-l)%len+rbs+1));
			}
		}
	}
//	cerr<<"---calc dp"<<endl;
	ll mn=0;
	for(int i=1;i<=n;i++)
	{
		dp[i]=mn+A+B;
		for(int j=0;j<v[i].size();j++)
		{
			int rid=v[i][j].SS;
			rg[rid]=min(rg[rid],dp[v[i][j].FF]+rgc[rid]);
			dp[i]=min(dp[i],rg[rid]);
		}
		mn=min(mn+A,dp[i]);
	}
	ll ans=dp[n];
	cout<<ans<<endl;
//	cerr<<"rtot="<<rtot<<" SUM="<<SUM<<endl;
}
int main()
{
	for(int i=2;i<maxn;i++)lg2[i]=lg2[i>>1]+1;
	int Tn;
	scanf("%d",&Tn);
	while(Tn--)Solve();
	return 0;
}

