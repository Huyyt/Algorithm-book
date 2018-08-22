#include<bits/stdc++.h>
using namespace std;
const long long inf=1e18;
struct SA
{
	int n,l;
	int sa[100010],rank[100010],height[100010],a[100010],b[100010],sum[100010],cnt;
	int f[100010][25];
	void buildsa(char s[100010])
	{
		s[l]=0;
		n=l+1;
		int m=130;
		for (int i=0;i<n;i++)
		{
			a[i]=s[i];
		}
		for (int i=0;i<m;i++)
		{
			sum[i]=0;
		}
		for (int i=0;i<n;i++)
		{
			sum[a[i]]++;
		}
		for (int i=1;i<m;i++)
		{
			sum[i]+=sum[i-1];
		}
		for (int i=n-1;i>=0;i--)
		{
			sum[a[i]]--;
			sa[sum[a[i]]]=i;
		}
		for (int j=1;j<=n;j<<=1)
		{
			int cnt=0;
			for (int i=n-j;i<n;i++)
			{
				b[cnt]=i;
				cnt++;
			}
			for (int i=0;i<n;i++)
			{
				if (sa[i]>=j)
				{
					b[cnt]=sa[i]-j;
					cnt++;
				}
			}
			cnt=0;
			for (int i=0;i<m;i++)
			{
				sum[i]=0;
			}
			for (int i=0;i<n;i++)
			{
				sum[a[b[i]]]++;
			}
			for (int i=1;i<m;i++)
			{
				sum[i]+=sum[i-1];
			}
			for (int i=n-1;i>=0;i--)
			{
				sum[a[b[i]]]--;
				sa[sum[a[b[i]]]]=b[i];
			}
			swap(a,b);
			cnt=0;
			a[sa[0]]=0;
			for (int i=1;i<n;i++)
			{
				if (b[sa[i]]==b[sa[i-1]] && b[sa[i]+j]==b[sa[i-1]+j])
				{
					a[sa[i]]=cnt;
				}
				else
				{
					cnt++;
					a[sa[i]]=cnt;
				}
			}
			if (cnt>=n-1)
			{
				return;
			}
			m=cnt+1;
		}
	}
	void buildheight(char s[100010])
	{
		for (int i=0;i<n;i++)
		{
			rank[sa[i]]=i;
		}
		int k=0;
		for (int i=0;i<n-1;i++)
		{
			if (k)
			{
				k--;
			}
			while (s[i+k]==s[sa[rank[i]-1]+k])
			{
				k++;
			}
			height[rank[i]]=k;
		}
		for (int i=1;i<n;i++)
		{
			f[i][0]=height[i+1];
		}
		for (int j=1;j<=20;j++)
		{
			for (int i=1;i+(1<<j)-1<n;i++)
			{
				f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
			}
		}
	}
	void build(char s[100010])
	{
		l=strlen(s);
		buildsa(s);
		buildheight(s);
	}
	int query(int l,int r)
	{
		if (l==r)
		{
			return n-l;
		}
		l=rank[l];
		r=rank[r];
		if (l>r)
		{
			swap(l,r);
		}
		r--;
		int k=log2(r-l+1);
		return min(f[l][k],f[r-(1<<k)+1][k]);
	}
}sa,sb;
int t,A,B,tot,sum[100010];
long long f[100010],g[100010],w[100010];
bool used[2000010];
char s[100010];
vector<pair<int,int> > v[100010];
void solve()
{
	scanf("%d%d",&A,&B);
	scanf("%s",s+1);
	int len=strlen(s+1);
	sa.build(s+1);
	reverse(s+1,s+len+1);
	sb.build(s+1);
	reverse(s+1,s+len+1);
	for (int i=1;i<=len/2;i++)
	{
		sum[i]=sum[i-1]+len/i-1;
	}
	for (int i=1;i<=len;i++)
	{
		v[i].clear();
	}
	memset(used,false,sizeof(used));
	tot=0;
	for (int i=1;i<=len/2;i++)
	{
		int l,r;
		l=r=0;
		for (int j=i;j+i<=len;j+=i)
		{
			if (j<=r)
			{
				continue;
			}
			int l1,l2;
			l1=sa.query(j-1,j+i-1);
			l2=sb.query(len-j,len-j-i);
			//cout<<i<<" "<<j<<" "<<l1<<" "<<l2<<endl;
			if (l1+l2-1<i)
			{
				continue;
			}
			l=j-l2+1;
			r=j+l1-1;
			if (used[sum[i-1]+j/i])
			{
				continue;
			}
			for (int k=2*i;l+2*k-1<=r+i;k+=i)
			{
				used[sum[k-1]+(l+k-1)/k]=true;
			}
			int now=tot;
			for (int k=l;k<=r-i+1;k++)
			{
				if (k<l+i)
				{
					tot++;
					g[tot]=inf;
					w[tot]=1LL*i*A+B;
				}
				v[k+i+i-1].push_back(make_pair(k-1,(k-l)%i+now+1));
			}
		}
	}
	long long mn=0;
	for (int i=1;i<=len;i++)
	{
		f[i]=mn+A+B;
		for (int j=0;j<v[i].size();j++)
		{
			int y=v[i][j].second;
			g[y]=min(g[y],f[v[i][j].first]+w[y]);
			f[i]=min(f[i],g[y]);
		}
		mn=min(mn+A,f[i]);
		//cout<<f[i]<<endl;
	}
	printf("%lld\n",f[len]);
}
int main()
{
	scanf("%d",&t);
	while (t--)
	{
		solve();
	}
	return 0;
}
