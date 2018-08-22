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
ll qpow(ll x,ll k){return k==0?1:1ll*qpow(1ll*x*x%mod,k>>1)*(k&1?x:1)%mod;}
const int maxn=300111;
int n,a[maxn];
bool ty[maxn];
pair<int,int> p[maxn],p2[maxn];
set<int> s0,s1;
int get2nd(set<int> &st)
{
	set<int>::iterator it=st.begin();
	it++;
	return *it;
}
int vcnt[maxn];
bool vis[maxn];
map<int,set<int> > vs;
int cnte,ans;
vector<int> v;
bool check(int x)
{
	if(ty[x]==0)
	{
		if(s1.size()==0)return true;
		if(s0.size()==1)return true;
		int ce=0;
		if(vs[a[x]].size()==1)ce=vs[a[x]^ans].size()>0;
		return ce<cnte;
	}
	else
	{
		if(s0.size()==0)return true;
		if(s1.size()==1)return true;
		int ce=0;
		if(vs[a[x]].size()==1)ce=vs[a[x]^ans].size()>0;
		return ce<cnte;
	}
}
vector<int> ANS;
void aug(int x)
{
	vis[x]=1;
	vs[a[x]].erase(x);
	if(vs[a[x]].size()==0)
	{
		cnte-=vs[a[x]^ans].size()>0;
	}
	if(ty[x]==0)s0.erase(x);
	else s1.erase(x);
	ANS.PB(x);
}
struct TRIE
{
	int go[maxn*30][2],tot;
	TRIE()
	{
		tot=1;
		memset(go,0,sizeof(go));
	}
	void insert(int x)
	{
		int p=1;
		for(int i=29;i>=0;i--)
		{
			int c=(x>>i)&1;
			int &np=go[p][c];
			if(np==0)np=++tot;
			p=np;
		}
	}
	int query(int x)
	{
		int p=1,ans=0;
		for(int i=29;i>=0;i--)
		{
			int c=(x>>i)&1;
			if(go[p][c])p=go[p][c];
			else
			{
				p=go[p][c^1];
				ans+=1<<i;
			}
		}
		assert(p>0);
		return ans;
	}
}yxg;
int main()
{
	geti(n);
	for(int i=1;i<=n;i++)
	{
		geti(a[i]);
		p[i]=MP(a[i],i);
	}
	int m=-1;
	for(int i=30;i>=0;i--)
	{
		bool f=1;
		for(int j=1;j<=n;j++)
		{
			f&=((a[1]>>i)&1)==((a[j]>>i)&1);
		}
		if(!f)
		{
			m=i;
			break;
		}
	}
	if(m==-1)
	{
		for(int i=1;i<=n;i++)printf("%d ",i);
		return 0;
	}
//	cerr<<"m="<<m<<endl;
	for(int i=1;i<=n;i++)
	{
		int x=a[i]&((1<<m)-1);
		ty[i]=(a[i]>>m)&1;
		if(ty[i])s1.insert(i);
		else s0.insert(i);
		if(ty[i]==0)
		{
			yxg.insert(x);
		}
	}
	ans=2e9;
	for(int i=1;i<=n;i++)
	{
		int x=a[i]&((1<<m)-1);
		if(ty[i]==1)
		{
			ans=min(ans,yxg.query(x));
		}
	}
	ans+=1<<m;
	
	for(int i=1;i<=n;i++)
	{
		if(vs[a[i]].size()==0)
		{
			cnte+=vs[a[i]^ans].size()>0;
		}
		vs[a[i]].insert(i);
	}
	cerr<<"ans="<<ans<<endl;
	for(int i=1;i<=n;i++)
	{
		if(check(i))
		{
			aug(i);
			break;
		}
	}
	assert(ANS.size()>0);
	for(int i=1;i<n;i++)
	{
		int x=ANS.back();
		vector<int> v;
		if(vs[a[x]^ans].size()>0)
		{
			v.PB(*vs[a[x]^ans].begin());
		}
		if(ty[x]==0)
		{
			if(s0.size()>0)v.PB(*s0.begin());
			if(s0.size()>1)v.PB(get2nd(s0));
		}
		else
		{
			if(s1.size()>0)v.PB(*s1.begin());
			if(s1.size()>1)v.PB(get2nd(s1));
		}
		sort(v.begin(),v.end());
		bool f=0;
		for(int j=0;j<v.size();j++)
		{
			if(check(v[j]))
			{
				f=1;
				aug(v[j]);
				break;
			}
		}
		assert(f);
	}
	assert(ANS.size()==n);
	for(int i=0;i<n;i++)puti(ANS[i]);
	for(int i=0;i+1<n;i++)assert((a[ANS[i]]^a[ANS[i+1]])<=ans);
	return 0;
}
