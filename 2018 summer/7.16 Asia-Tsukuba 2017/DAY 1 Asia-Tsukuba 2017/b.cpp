#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cfloat>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <time.h>
typedef long long int ll;
typedef unsigned long long int ull;
#define BIG_NUM 2000000000
#define MOD 1000000007
#define EPS 0.000000001
using namespace std;
 
 
struct Point{
    double x,y;
};
Point point[16];
 
struct Data{
    double slope;
    int count;
};
Data data[8];
 
enum Type{
    FROM,
    TO,
};
 
int M;
int ans = 0;
 
double calc_slope(int a,int b){
 
    if(point[a].x == point[b].x){
        return DBL_MAX;
    }else{
        return (point[b].y-point[a].y)/(point[b].x-point[a].x);
    }
}
 
void recursive(int array[16],int pair[8][2],int num,Type type){
 
    if(num == M/2){
 
        int index = 0;
        double tmp_slope;
 
        bool FLG;
 
        for(int i = 0; i < M/2; i++){
            tmp_slope = calc_slope(pair[i][0],pair[i][1]);
 
            FLG = false;
            for(int k = 0; k < index; k++){
                if(fabs(data[k].slope-tmp_slope) < EPS){
                    data[k].count++;
                    FLG = true;
                    break;
                }
            }
            if(FLG)continue;
 
            data[index].slope = tmp_slope;
            data[index].count = 1;
            index++;
        }
 
        int tmp_count = 0;
        for(int i = 0; i < index; i++){
            tmp_count += (data[i].count*(data[i].count-1))/2;
        }
 
        ans = max(ans,tmp_count);
 
        return;
    }
 
    if(type == FROM){
        for(int i = 0; i < M; i++){
            if(array[i] == -1){
                int next_array[16];
                for(int k = 0; k < M; k++)next_array[k] = array[k];
                next_array[i] = 1;
                int next_pair[8][2];
                for(int k = 0; k < num; k++){
                    next_pair[k][0] = pair[k][0];
                    next_pair[k][1] = pair[k][1];
                }
                next_pair[num][0] = i;
                recursive(next_array,next_pair,num,TO);
                break;
            }
        }
    }else{ //type == TO
        for(int i = 0; i < M; i++){
            if(array[i] == -1){
                int next_array[16];
                for(int k = 0; k < M; k++)next_array[k] = array[k];
                next_array[i] = 1;
                int next_pair[8][2];
                for(int k = 0; k <= num; k++){
                    next_pair[k][0] = pair[k][0];
                    next_pair[k][1] = pair[k][1];
                }
                next_pair[num][1] = i;
                recursive(next_array,next_pair,num+1,FROM);
            }
        }
    }
}
 
 
int main(){
 
    scanf("%d",&M);
 
    for(int i = 0; i < M; i++){
        scanf("%lf %lf",&point[i].x,&point[i].y);
    }
 
    int first_array[16],first_pair[8][2];
    for(int i = 0; i < M; i++)first_array[i] = -1;
 
    recursive(first_array,first_pair,0,FROM);
 
    printf("%d\n",ans);
}
