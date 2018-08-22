#include<bits/stdc++.h>
using namespace std;
struct trie
{
	int nxt[10000010][2],tot,root;
	inline int newtrie()
	{
		memset(nxt[tot],-1,sizeof(nxt[tot]));
		return tot++;
	}
	inline void init()
	{
		tot=0;
		root=newtrie();
	}
	inline void insert(int x,int l)
	{
		int p=root;
		int idx;
		for (int i=l-1;i>=0;i--)
		{
			idx=(x>>i)&1;
			if (nxt[p][idx]==-1)
			{
				nxt[p][idx]=newtrie();
			}
			p=nxt[p][idx];
		}
	}
	inline int search(int x,int l)
	{
		int p=root;
		int idx;
		int res=0;
		for (int i=l-1;i>=0;i--)
		{
			idx=(x>>i)&1;
			//cout<<idx<<" "<<nxt[p][idx]<<endl;
			if (nxt[p][idx]==-1)
			{
				p=nxt[p][idx^1];
				res|=1<<i;
				continue;
			}
			p=nxt[p][idx];
		}
		//cout<<x<<" "<<res<<endl;
		return res;
	}
}t;
int n,tot,a[300010],mx,nxt[300010],s[2],i0,i1;
map<int,int> mp,b;
vector<int> v[300010];
bool used[300010];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		mx=max(mx,a[i]);
	}
	int k=0;
	while (mx)
	{
		k++;
		mx>>=1;
	}
	k--;
	while (k)
	{
		bool f0=false,f1=false;
		for (int i=1;i<=n;i++)
		{
			if (a[i]&(1<<k))
			{
				f1=true;
			}
			else 
			{
				f0=true;
			}
		}
		if (f1 && f0)
		{
			break;
		}
		k--;
	}
	int s0=0,s1=0,lst0,lst1;
	t.init();
	for (int i=1;i<=n;i++)
	{
		if (!(a[i]&(1<<k)))
		{
			if (!i0)
			{
				i0=i;
				nxt[n+1]=i;
			}
			else
			{
				nxt[lst0]=i;
			}
			nxt[i]=n+1;
			t.insert(a[i],k);
			s0++;
			lst0=i;
		}
	}
	int mn=1<<k;
	for (int i=1;i<=n;i++)
	{
		if (a[i]&(1<<k))
		{
			if (!i1)
			{
				i1=i;
				nxt[n+2]=i;
			}
			else
			{
				nxt[lst1]=i;
			}
			nxt[i]=n+2;
			mn=min(mn,t.search(a[i],k));
			s1++;
			lst1=i;
		}
	}
	/*
	for (int i=1;i<=n+2;i++)
	{
		cerr<<i<<" "<<nxt[i]<<endl;
	}
	*/
	mn+=1<<k;
	for (int i=1;i<=n;i++)
	{
		if (!mp[a[i]])
		{
			tot++;
			b[a[i]]=tot;
			v[tot].push_back(1);
		}
		mp[a[i]]++;
		v[b[a[i]]].push_back(i);
	}
	int cnt=0;
	for (map<int,int>::iterator it=mp.begin();it!=mp.end();it++)
	{
		cnt+=min(it->second,mp[(it->first)^mn]);
	}
	cnt/=2;
	int h=0;
	while (true)
	{
		h++;
		if (mp[a[h]^mn]<mp[a[h]] || a[h]==(a[h]^mn))
		{
			printf("%d ",h);
			mp[a[h]]--;
			v[b[a[h]]][0]++;
			s[(a[h]>>k)&1]++;
			break;
		}
		else
		{
			if (cnt>1 || (((a[h]>>k)&1) && s[1]==s1-1) || (!((a[h]>>k)&1) && s[0]==s0-1))
			{
				cnt--;
				printf("%d ",h);
				mp[a[h]]--;
				v[b[a[h]]][0]++;
				s[(a[h]>>k)&1]++;
				break;
			}
		}
	}
	int tmp=a[h];
	used[h]=true;
	/*
	int l;
	if ((tmp>>k)&1)
	{
		l=n+2;
	}
	else
	{
		l=n+1;
	}
	while (true)
	{
		if (nxt[l]==h)
		{
			nxt[l]=nxt[h];
			break;
		}
	}
	*/
	//cerr<<k<<" "<<mn<<" "<<cnt<<" "<<s0<<" "<<s1<<endl;
	for (int i=2;i<=n;i++)
	{
		int j,lst;
		//cout<<tmp<<endl;
		//cout<<cnt<<endl;
		if ((tmp>>k)&1)
		{
			lst=n+2;
		}
		else
		{
			lst=n+1;
		}
		j=lst;
		while (true)
		{
			j=nxt[j];
			while (used[j] && j<=n)
			{
				j=nxt[j];
			}
			nxt[lst]=j;
			int now=b[tmp^mn];
			//cerr<<j<<" "<<tmp<<" "<<v[now][v[now][0]]<<endl;
			if (mp[tmp^mn] && v[now][v[now][0]]<j)
			{
				int x=v[now][v[now][0]];
				//cerr<<x<<" ";
				if (mp[a[x]^mn]<mp[a[x]] || a[x]==(a[x]^mn))
				{
				
					printf("%d ",x);
					mp[a[x]]--;
					v[b[a[x]]][0]++;
					tmp=a[x];
					s[(tmp>>k)&1]++;
					used[x]=true;
					break;
				}
				else
				{
				
					if (cnt>1)
					{
						cnt--;
						printf("%d ",x);
						mp[a[x]]--;
						v[b[a[x]]][0]++;
						tmp=a[x];
						s[(tmp>>k)&1]++;
						used[x]=true;
						break;
					}
					//cout<<((a[j]>>k)&1)<<" "<<s[1]<<endl;
					if ((((a[x]>>k)&1) && s[1]==s1-1) || (!((a[x]>>k)&1) && s[0]==s0-1))
					{
						cnt--;
						printf("%d ",x);
						mp[a[x]]--;
						v[b[a[x]]][0]++;
						tmp=a[x];
						s[(tmp>>k)&1]++;
						used[x]=true;
						break;
					}
				}
			}
			if (j>n)
			{
				break;
			}
			//cout<<a[j]<<" "<<mp[a[j]]<<" "<<mp[a[j]^mn]<<endl;
			//cout<<a[j]<<" "<<tmp<<" "<<((a[j]^tmp)>>k)<<endl;
			if (mp[a[j]^mn]<mp[a[j]] || a[j]==(a[j]^mn))
			{
				
					printf("%d ",j);
					mp[a[j]]--;
					v[b[a[j]]][0]++;
					tmp=a[j];
					s[(tmp>>k)&1]++;
					nxt[lst]=nxt[j];
					break;
			}
			else
			{
				
					if (cnt>1)
					{
						cnt--;
						printf("%d ",j);
						mp[a[j]]--;
						v[b[a[j]]][0]++;
						tmp=a[j];
						s[(tmp>>k)&1]++;
						nxt[lst]=nxt[j];
						break;
					}
					//cout<<((a[j]>>k)&1)<<" "<<s[1]<<endl;
					if ((((a[j]>>k)&1) && s[1]==s1-1) || (!((a[j]>>k)&1) && s[0]==s0-1))
					{
						cnt--;
						printf("%d ",j);
						mp[a[j]]--;
						v[b[a[j]]][0]++;
						tmp=a[j];
						s[(tmp>>k)&1]++;
						nxt[lst]=nxt[j];
						break;
					}
					
			}
			lst=j;
		}
		//cout<<endl;
	}
	return 0;
}
