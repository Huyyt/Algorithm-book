//Hungary
#define N 202
int useif[N];   //��¼y�нڵ��Ƿ�ʹ�� 0��ʾû�з��ʹ���1Ϊ���ʹ�
int link[N];   //��¼��ǰ��y�ڵ�������x�Ľڵ�
int mat[N][N]; //��¼����x��y�ıߣ����i��j֮���б���Ϊ1������Ϊ0
int gn,gm;    //����ͼ��x��y�е����Ŀ
int can(int t)
{
    int i;
    for(i=1;i<=gm;i++)
    {
       if(useif[i]==0 && mat[t][i])
       {
           useif[i]=1;
           if(link[i]==-1 || can(link[i]))
           {
              link[i]=t;
              return 1;
           }
       }
    }
    return 0;
}
int MaxMatch()
{
    int i,num;
    num=0;
    memset(link,0xff,sizeof(link));
    for(i=1;i<=gn;i++)
    {
      memset(useif,0,sizeof(useif));
       if(can(i)) num++;
    }
    return num;
}
