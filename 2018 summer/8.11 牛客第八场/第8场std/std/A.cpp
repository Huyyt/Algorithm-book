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

const double pi=acos(-1);
const int maxn=1011;
int curx,cury;
struct point
{
	int x,y;
	point(int X=0,int Y=0){x=X;y=Y;}
	ll det(const point &t)const{return 1ll*x*t.y-1ll*y*t.x;}
	ll dot(const point &t)const{return 1ll*x*t.x+1ll*y*t.y;}
	bool operator<(const point &t)const
	{
		if(det(t)!=0)return det(t)>0;
		else
		{
			if(point(curx,cury).det(t)==0)return point(curx,cury).dot((*this))>0&&(*this).dot(t)<0;
			else return det(t)>0;
		}
	}
};
struct segment
{
	int x,y,g;bool f;
	segment(int X=0,int Y=0,int G=0){x=X;y=Y;g=G;f=0;}
	bool operator<(const segment &t)const
	{
		return MP(y,x)<MP(t.y,t.x);
	}
};
int n;
segment P[maxn];
ll ANS[maxn];
int sx[maxn],sy[maxn],sk[maxn];
set<pair<point,int> > st;
int mnp[maxn];
bool has_gap[maxn];

pair<point,int> calc_p(int i)
{
	return MP(point(P[i+1].x-P[i].x,P[i+1].y-P[i].y),i);
}
void add_gap(int x)
{
	if(x>=0&&x+1<n&&(P[x].x!=P[x+1].x||P[x].y!=P[x+1].y))
	{
		assert(has_gap[x]==0);
		has_gap[x]=1;
		st.insert(calc_p(x));
	}
}
void del_gap(int x)
{
	if(x>=0&&x+1<n&&(P[x].x!=P[x+1].x||P[x].y!=P[x+1].y))
	{
		assert(has_gap[x]==1);
		has_gap[x]=0;
		st.erase(calc_p(x));
	}
}
void swap_points(int x)
{
//	cerr<<"swap:"<<x<<endl;
	del_gap(x-1);
	del_gap(x);
	del_gap(x+1);
	swap(P[x],P[x+1]);
	if(P[x].g==P[x+1].g&&(P[x].f^P[x+1].f))
	{
		swap(P[x].f,P[x+1].f);
		for(int i=x;i<n;i++)
		{
			sx[i]=(i==0?0:sx[i-1])+(P[i].f?P[i].x:0);
			sy[i]=(i==0?0:sy[i-1])+(P[i].f?P[i].y:0);
			sk[i]=(i==0?0:sk[i-1])+P[i].f;
			ANS[sk[i]]=max(ANS[sk[i]],1ll*sx[i]*sx[i]+1ll*sy[i]*sy[i]);
		}
	}
	else
	{
		for(int i=x;i<=x+1;i++)
		{
			sx[i]=(i==0?0:sx[i-1])+(P[i].f?P[i].x:0);
			sy[i]=(i==0?0:sy[i-1])+(P[i].f?P[i].y:0);
			sk[i]=(i==0?0:sk[i-1])+P[i].f;
			ANS[sk[i]]=max(ANS[sk[i]],1ll*sx[i]*sx[i]+1ll*sy[i]*sy[i]);
		}
	}
	add_gap(x-1);
	add_gap(x);
	add_gap(x+1);
}
void solve()
{
	static bool f[maxn];
	memset(has_gap,0,sizeof(has_gap));
	st.clear();
	sort(P,P+n);
	memset(f,0,sizeof(f));
	for(int i=0;i<n;i++)
	{
		if(f[P[i].g])continue;
		f[P[i].g]=1;
		P[i].f=1;
	}
	curx=1;cury=0;
//	for(int i=0;i<n;i++)cerr<<P[i].x<<","<<P[i].y<<" "<<P[i].g<<" "<<P[i].f<<endl;	
	for(int i=0;i<n;i++)
	{
		sx[i]=(i==0?0:sx[i-1])+(P[i].f?P[i].x:0);
		sy[i]=(i==0?0:sy[i-1])+(P[i].f?P[i].y:0);
		sk[i]=(i==0?0:sk[i-1])+P[i].f;
		ANS[sk[i]]=max(ANS[sk[i]],1ll*sx[i]*sx[i]+1ll*sy[i]*sy[i]);
		add_gap(i);
	}
	point pre=point(1,0);
	while(st.size()>0)
	{
		point cur=st.begin()->FF;
		assert(cur.x!=0||cur.y!=0);
		curx=cur.x;cury=cur.y;
		if((pre.det(point(1,0))>0||pre.det(point(1,0))==0&&pre.dot(point(1,0))<0)&&
		   (point(1,0).det(cur)>0||point(1,0).det(cur)==0&&point(1,0).dot(cur)>0))break;
		int x=st.begin()->SS;
		st.erase(st.begin());
		swap_points(x);
//		if(rand()%10000==0)cerr<<cur.x<<" "<<cur.y<<endl;
//		for(int i=0;i<n;i++)cerr<<P[i].x<<","<<P[i].y<<" "<<P[i].g<<" "<<P[i].f<<" "<<cur.det(point(P[i].x-cur.x,P[i].y-cur.y))<<endl;
		pre=cur;
//		system("pause");
	}
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		int x,y,g;
		cin>>x>>y>>g;
		P[i]=segment(x,y,g);
	}
	for(int i=0;i<=n;i++)ANS[i]=0;
	solve();
	for(int i=1;i<=n;i++)
	{
		ANS[i]=max(ANS[i],ANS[i-1]);
		cout<<ANS[i];
		if(i<n)cout<<" ";else cout<<endl;
	}
	return 0;
}
