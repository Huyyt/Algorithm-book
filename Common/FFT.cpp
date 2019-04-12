#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e7+10;
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const double Pi=acos(-1.0);
struct complex
{
    double x,y;
    complex (double xx=0,double yy=0){x=xx,y=yy;}
}a[MAXN],b[MAXN];
complex operator + (complex a,complex b){ return complex(a.x+b.x , a.y+b.y);}
complex operator - (complex a,complex b){ return complex(a.x-b.x , a.y-b.y);}
complex operator * (complex a,complex b){ return complex(a.x*b.x-a.y*b.y , a.x*b.y+a.y*b.x);}//不懂的看复数的运算那部分 
int N,M;
int l,r[MAXN];
int limit=1;
void fast_fast_tle(complex *A,int type)
{
    for(int i=0;i<limit;i++) 
        if(i<r[i]) swap(A[i],A[r[i]]);//求出要迭代的序列 
    for(int mid=1;mid<limit;mid<<=1)//待合并区间的中点
    {
        complex Wn( cos(Pi/mid) , type*sin(Pi/mid) ); //单位根 
        for(int R=mid<<1,j=0;j<limit;j+=R)//R是区间的右端点，j表示前已经到哪个位置了 
        {
            complex w(1,0);//幂 
            for(int k=0;k<mid;k++,w=w*Wn)//枚举左半部分 
            {
                 complex x=A[j+k],y=w*A[j+mid+k];//蝴蝶效应 
                A[j+k]=x+y;
                A[j+mid+k]=x-y;
            }
        }
    }
}
int main()
{
    int N=read(),M=read();
    for(int i=0;i<=N;i++) a[i].x=read();
    for(int i=0;i<=M;i++) b[i].x=read();
    while(limit<=N+M) limit<<=1,l++;
    for(int i=0;i<limit;i++)
        r[i]= ( r[i>>1]>>1 )| ( (i&1)<<(l-1) ) ;
    // 在原序列中 i 与 i/2 的关系是 ： i可以看做是i/2的二进制上的每一位左移一位得来
    // 那么在反转后的数组中就需要右移一位，同时特殊处理一下复数 
    fast_fast_tle(a,1);
    fast_fast_tle(b,1);
    for(int i=0;i<=limit;i++) a[i]=a[i]*b[i];
    fast_fast_tle(a,-1);
    for(int i=0;i<=N+M;i++)
        printf("%d ",(int)(a[i].x/limit+0.5));
    return 0;
}
