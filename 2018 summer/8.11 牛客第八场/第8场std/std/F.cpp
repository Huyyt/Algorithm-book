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
const int maxn=4e5+11;
int L;
//spikeweeds
struct SGT
{
	struct node
	{
		int v,tl,tr;
		node(){v=tl=tr=0;}
	}a[maxn*2*20];
	#define ls a[p].tl
	#define rs a[p].tr
	int tot;
	SGT(){tot=0;a[0].v=a[0].tl=a[0].tr=0;}
	int newnode(int q)
	{
		int p=++tot;
		a[p].v=a[q].v;
		a[p].tl=a[q].tl;
		a[p].tr=a[q].tr;
		return p;
	}
	int build(int l,int r)
	{
		int p=newnode(0);
		if(l==r)return p;
		int m=l+r>>1;
		a[p].tl=build(l,m);
		a[p].tr=build(m+1,r);
		return p;
	}
	int add(int x,int l,int r,int q)
	{
		int p=newnode(q);
		a[p].v++;
		if(x==l&&x==r)return p;
		int m=l+r>>1;
		if(x<=m)a[p].tl=add(x,l,m,a[q].tl);
		else a[p].tr=add(x,m+1,r,a[q].tr);
		return p;
	}
	int query_sum(int x,int y,int l,int r,int p)
	{
		if(x<=l&&r<=y)return a[p].v;
		int m=l+r>>1,ret=0;
		if(x<=m)ret+=query_sum(x,y,l,m,ls);
		if(m<y)ret+=query_sum(x,y,m+1,r,rs);
		return ret;
	}
	int query_pos(int x,int y,int l,int r,int &v,int p)
	{
		if(x<=l&&r<=y)
		{
			if(v>a[p].v)
			{
				v-=a[p].v;
				return l-1;
			}
			else
			{
				if(l==r)
				{
					v=0;
					return l;
				}
				int m=l+r>>1;
				int tmp=query_pos(x,y,m+1,r,v,rs);
				if(v==0)return tmp;
				else return query_pos(x,y,l,m,v,ls);
			}
		}
		int m=l+r>>1;
		if(x<=m&&m<y)
		{
			int tmp=query_pos(x,y,m+1,r,v,rs);
			if(v==0)return tmp;
			else return query_pos(x,y,l,m,v,ls);
		}
		else if(x<=m)return query_pos(x,y,l,m,v,ls);
		else if(m<y)return query_pos(x,y,m+1,r,v,rs);
		assert(false);
	}
}sgt;
int sgt_rt[maxn],sgt_ti[maxn],rtn;
int spt[maxn];
int query_tipos(int x){return upper_bound(sgt_ti+1,sgt_ti+1+rtn,x)-sgt_ti-1;}
int query_tot_damage(int tl,int tr,int pos,int dir)
{
	if(tl>=tr)return 0;
	if(dir==0)
	{
		if(spt[pos+1]==0)return 0;
		else return max(tr-max(tl,spt[pos+1]),0);
	}
	else
	{
		int p=query_tipos(pos+tl);
		assert(p>=1&&p<=rtn);
		return sgt.query_sum(pos-(tr-tl)+1,pos,1,L,sgt_rt[p]);
	}
}
int query_death_time(int tl,int tr,int pos,int dir,int hp)
{
	assert(tl<tr);
	if(dir==0)
	{
		assert(spt[pos+1]>0);
		return max(spt[pos+1],tl)+hp;
	}
	else
	{
		int p=query_tipos(pos+tl);
		assert(p>=1&&p<=rtn);
		int thp=hp;
		int dpos=sgt.query_pos(pos-(tr-tl)+1,pos,1,L,thp,sgt_rt[p]);
		//cerr<<"dpos="<<dpos<<" "<<tl+pos-dpos+1<<endl;
		assert(tl+pos-dpos+1<=tr);
		return tl+pos-dpos+1;
	}
}
void spike_prework()
{
	rtn=1;
	sgt_rt[1]=sgt.build(1,L);
	sgt_ti[1]=0;
	vector<pair<int,int> > v;
	for(int i=1;i<=L;i++)if(spt[i]>0)v.PB(MP(i+spt[i],i));
	sort(v.begin(),v.end());
	for(int i=0;i<v.size();i++)
	{
		rtn++;
		sgt_rt[rtn]=sgt.add(v[i].SS,1,L,sgt_rt[rtn-1]);
		sgt_ti[rtn]=v[i].FF;
	}
}
//object
struct heap_node
{
	int v,id,lz;
	int go[2];
	heap_node(){v=id=lz=go[0]=go[1]=0;}
	void addlz(int LZ)
	{
		lz+=LZ;
		v+=LZ;
	}
}hp[maxn];
int hptot;
void pushdown(int p)
{
	if(hp[p].lz!=0)
	{
		if(hp[p].go[0])hp[hp[p].go[0]].addlz(hp[p].lz);
		if(hp[p].go[1])hp[hp[p].go[1]].addlz(hp[p].lz);
		hp[p].lz=0;
	}
}
int merge(int p,int q)
{
	if(!p||!q)return p^q;
	if(hp[p].v>hp[q].v)swap(p,q);
	pushdown(p);
	hp[p].go[1]=merge(hp[p].go[1],q);
	swap(hp[p].go[0],hp[p].go[1]);
	return p;
}
int TOT;
bool type[maxn];//0 wall-nut 1 zombie
int dur[maxn];//wall-nut DUR zombie HP-id
int nxtid[maxn];
int dti[maxn];//death time
//positions
vector<pair<int,pair<int,int> > > pos_seq[maxn];
int CURT;
struct position_node
{
	int pos,ti,dir,id;
	position_node(int _ti=0,int _pos=0,int _dir=0,int _id=0){pos=_pos;ti=_ti;dir=_dir;id=_id;}
	int getpos()const{return pos+(CURT-ti)*dir;}
	bool operator<(const position_node &t)const
	{
		if(getpos()!=t.getpos())return getpos()<t.getpos();
		if(type[id]!=type[t.id])return type[id]<type[t.id];
		if(dir!=t.dir)return dir>t.dir;
		return id<t.id;
	}
}cpos[maxn];
set<position_node> POS;
int getpos_pre(int id)
{
	set<position_node>::iterator it=POS.lower_bound(cpos[id]);
	if(it==POS.begin())return -1;else return (--it)->id;
}
int getpos_nxt(int id)
{
	set<position_node>::iterator it=POS.lower_bound(cpos[id]);
	it++;
	if(it==POS.end())return -1;else return it->id;
}


//events
struct event_node
{
	int ti,op,id;
	event_node(int _ti=0,int _op=0,int _id=0){ti=_ti;op=_op;id=_id;}
	bool operator<(const event_node &t)const
	{
		if(ti!=t.ti)return ti<t.ti;
		if(op!=t.op)return op<t.op;
		return id<t.id;
	}
}cev[maxn];
set<event_node> EV;

void Walk(int id,int tl,int tr,int pos,int dir)
{
	int &p=dur[id];
	pos_seq[id].PB(MP(tl,MP(pos,dir)));
	int dmg=query_tot_damage(tl,tr,pos,dir);
	hp[p].addlz(-dmg);
	int tg=pos+dir*(tr-tl);
	while(p&&(hp[p].v<=0||tg==0))
	{
		int id=hp[p].id;
		if(hp[p].v<=0)dti[id]=query_death_time(tl,tr,pos,dir,hp[p].v+dmg);
		else dti[id]=tr;
		pushdown(p);
		p=merge(hp[p].go[0],hp[p].go[1]);
	}
}
void Walk(int id,int tl,int tr){Walk(id,tl,tr,cpos[id].pos,cpos[id].dir);}


int Merge(int x,int y)
{
	int p=++TOT;
	assert(TOT<maxn);
	type[p]=1;
	dur[p]=merge(dur[x],dur[y]);
	nxtid[x]=nxtid[y]=p;
	return p;
}

//query
int Q,qti[maxn],qid[maxn],qp[maxn],qd[maxn];
char qc[maxn];

void modifyevent(int id,int coef)
{
	if(type[id]==0||id==-1)return;
	int pre=getpos_pre(id),pos=cpos[id].pos;
	event_node ev(0,0,-1);
	if(cpos[id].dir==-1)
	{
		if(pre==-1)
		{
			ev=event_node(pos-0+cpos[id].ti,1,id);
		}
		else if(type[pre]==0)
		{
			ev=event_node(pos-cpos[pre].pos+cpos[id].ti,1,id);
		}
		else if(cpos[pre].dir==0)
		{
			ev=event_node(pos-cpos[pre].pos+cpos[id].ti,2,id);
		}
	}
	else
	{
		assert(type[pre]==0&&cpos[pre].pos==pos);
		int tw=cpos[pre].ti+dur[pre];
		int tz=spt[pos+1]?max(spt[pos+1],cpos[id].ti)+hp[dur[id]].v:tw;
		ev=event_node(min(tw,tz),3,id);
	}
	if(ev.id!=-1)
	{
		if(coef==1)EV.insert(ev);
		else EV.erase(ev);
	}
}

void insert_pos(int id)
{
	set<position_node>::iterator it=POS.lower_bound(cpos[id]);
	if(it!=POS.end())modifyevent(it->id,-1);
	POS.insert(cpos[id]);
	modifyevent(id,1);
	modifyevent(getpos_nxt(id),1);
}
void modify_position(int id,position_node t)
{
	POS.erase(cpos[id]);
	cpos[id]=t;
	POS.insert(cpos[id]);
}


void Event(event_node &A)
{
	int id=A.id,ti=A.ti,pos=cpos[id].pos,pre,nxt;
	CURT=ti;
	//cerr<<"Event op="<<A.op<<" id="<<A.id<<" ti="<<A.ti<<endl;
	if(A.op<=4)
	{
		pre=getpos_pre(id);
		nxt=getpos_nxt(id);
		modifyevent(id,-1);
		modifyevent(nxt,-1);
	}
	if(A.op==1)
	{
		Walk(id,cpos[id].ti,ti);
		modify_position(id,position_node(ti,cpos[id].pos-(ti-cpos[id].ti),0,id));
		if(pre!=-1)modify_position(pre,position_node(ti,cpos[pre].pos,0,pre));
		if(dur[id]==0||cpos[id].pos==0)POS.erase(cpos[id]);
		else modifyevent(id,1);
		modifyevent(nxt,1);
	}
	else if(A.op==2)
	{
		Walk(id,cpos[id].ti,ti);
		POS.erase(cpos[id]);
		if(dur[id]==0)
		{
			modifyevent(nxt,1);
		}
		else
		{
			modifyevent(pre,-1);
			int ppre=getpos_pre(pre);
			dur[ppre]-=ti-cpos[pre].ti;
			modify_position(ppre,position_node(ti,cpos[ppre].pos,0,ppre));
			Walk(pre,cpos[pre].ti,ti);
			modify_position(pre,position_node(ti,cpos[pre].pos,0,pre));
			POS.erase(cpos[pre]);
			int p=Merge(pre,id);
			cpos[p]=position_node(ti,cpos[pre].pos,0,p);
			POS.insert(cpos[p]);
			modifyevent(nxt,1);
			modifyevent(p,1);
		}
	}
	else if(A.op==3)
	{
		int len=ti-cpos[id].ti;
		dur[pre]-=len;
		if(dur[pre]==0)POS.erase(cpos[pre]);
		else modify_position(pre,position_node(ti,pos,0,pre));
		Walk(id,cpos[id].ti,ti);
		POS.erase(cpos[id]);
		if(dur[id]==0)POS.erase(cpos[id]);
		else
		{
			if(dur[pre]==0)modify_position(id,position_node(ti,pos,-1,id));
			else modify_position(id,position_node(ti,pos,0,id));
			modifyevent(id,1);
		}
		modifyevent(nxt,1);
	}
	else if(A.op==5)
	{
		char op=qc[id];
		int p=qp[id],d=qd[id];
		int cur=++TOT;
		qid[id]=cur;
		if(op=='W')
		{
			type[cur]=0;
			dur[cur]=d;
			cpos[cur]=position_node(ti,p,0,cur);
			insert_pos(cur);
		}
		else
		{
			type[cur]=1;
			dur[cur]=++hptot;
			hp[dur[cur]].v=d;
			hp[dur[cur]].id=cur;
			cpos[cur]=position_node(ti,p,-1,cur);
			insert_pos(cur);
		}
	}
}

int nxt_tab[20][maxn];
void query_prework()
{
	for(int i=1;i<=TOT;i++)nxt_tab[0][i]=nxtid[i];
	for(int i=1;i<20;i++)for(int j=1;j<=TOT;j++)nxt_tab[i][j]=nxt_tab[i-1][nxt_tab[i-1][j]];
}
int query(int id,int ti)
{
//	cerr<<"query:"<<id<<" "<<ti<<" dti="<<dti[id]<<endl;
	ti=min(ti,dti[id]);
	int x=id;
	for(int i=19;i>=0;i--)
	{
		if(nxt_tab[i][x]!=0&&pos_seq[nxt_tab[i][x]][0].FF<=ti)
		{
			x=nxt_tab[i][x];
		}
	}
	int p=lower_bound(pos_seq[x].begin(),pos_seq[x].end(),MP(ti+1,MP(-1,-1)))-pos_seq[x].begin()-1;
	assert(p>=0&&p<pos_seq[x].size());
	pair<int,pair<int,int> > pp=pos_seq[x][p];
	assert(ti>=pp.FF);
	return pp.SS.FF+(ti-pp.FF)*pp.SS.SS;
}

int main()
{
	getii(Q,L);
	for(int i=1;i<=Q;i++)
	{
		char c=getreal();
		qc[i]=c;
		int ti;
		geti(ti);
		qti[i]=ti;
		if(c=='S')
		{
			int p;
			geti(p);
			assert(spt[p]==0);
			spt[p]=ti;
		}
		else if(c=='Q')
		{
			geti(qp[i]);
		}
		else
		{
			event_node cur;
			EV.insert(event_node(ti,5,i));
			if(c=='W')
			{
				getii(qp[i],qd[i]);
			}
			else if(c=='Z')
			{
				qp[i]=L;
				geti(qd[i]);
			}
		}
	}
	spike_prework();
	while(EV.size()>0)
	{
	/*
		cerr<<"==========================="<<endl;
		cerr<<"All events:"<<endl;
		for(auto x:EV) cerr<<x.ti<<" "<<x.op<<" "<<x.id<<endl;
		cerr<<"All positions:"<<endl;
		for(auto x:POS) cerr<<x.ti<<" "<<x.pos<<" "<<x.dir<<" "<<x.id<<" cur="<<x.getpos()<<endl;
		cerr<<"All cpositions:"<<endl;
		for(int i=1;i<=TOT;i++)
		{
			cerr<<i<<":";
			auto x=cpos[i];
			cerr<<x.ti<<" "<<x.pos<<" "<<x.dir<<" "<<x.id<<endl;
		}
		cerr<<"All objects:"<<endl;
		for(int i=1;i<=TOT;i++)cerr<<i<<":"<<type[i]<<" "<<dur[i]<<endl;
	*/
		event_node cur=*EV.begin();
		EV.erase(EV.begin());
		Event(cur);
	}
	/*
	cerr<<"========================="<<endl;
	for(int i=1;i<=TOT;i++)
	{
		cerr<<i<<":"<<nxtid[i]<<" "<<dti[i]<<endl;
		for(auto x:pos_seq[i])cerr<<x.FF<<" "<<x.SS.FF<<" "<<x.SS.SS<<endl;
	}
	*/
	query_prework();
	for(int i=1;i<=Q;i++)
	{
		if(qc[i]=='Q')
		{
			putsi(query(qid[qp[i]],qti[i]));
		}
	}
	return 0;
}
