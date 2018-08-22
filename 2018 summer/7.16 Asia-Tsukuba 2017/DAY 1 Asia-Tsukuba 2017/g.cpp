#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define double long double
const double PI = acos(-1.0);
struct point {
    double x, y;
    int num;
    point operator +(const point &p)const {
        return { x + p.x, y + p.y };
    }
    point operator -(const point &p)const {
        return { x - p.x, y - p.y };
    }
    point Rotate(double Angle) {
        Angle = Angle*PI / 180;
        double ss = sinl(Angle), cc = cosl(Angle);
        return { x*cc - y*ss, x*ss + y*cc };
    }
    point operator *(const double &k)const {
        return { x*k,y*k };
    }
}P[4], RD, LD, RR;
point Get() {
    char p[3];
    int d, l;
    scanf("%s%d%d", p,&d,&l);
    if (strcmp(p, "BC") == 0) {
        return P[1].Rotate(d)*l;
    }
    if (strcmp(p, "BD") == 0) {
        return P[1].Rotate(-d)*l;
    }
    if (strcmp(p, "CB") == 0) {
        return P[2].Rotate(-d)*l;
    }
    if (strcmp(p, "CD") == 0) {
        return P[2].Rotate(d)*l;
    }
    if (strcmp(p, "DB") == 0) {
        return (P[0]-P[3]).Rotate(d)*l;
    }
    if (strcmp(p, "DC") == 0) {
        return P[3].Rotate(-d)*l;
    }
}
double ccw(point a, point b, point c) {
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}
bool Inside(point a, point b, point c, point d) {
    if (ccw(a, b, d) < 0 && ccw(b, c, d) < 0 && ccw(c, a, d) < 0)return true;
    if (ccw(a, b, d) > 0 && ccw(b, c, d) > 0 && ccw(c, a, d) > 0)return true;
    return false;
}
int Loc(point a) {
    int i, j, k;
    for (i = 0; i < 30; i+=2) {
        for (j = 0; j < 30; j += 2) {
            for (k = -30; k <= 30; k += 2) {
                point tp = P[0] + RR * k + RD * i + LD * j;
                point P1 = tp;
                point P2 = tp+RR;
                point P3 = tp+RR+RR;
                point P4 = tp+RD;
                point P5 = tp+RD+RR;
                point P6 = tp + RD + RR+RR;
                point P7 = tp+RD+RD;
                point P8 = tp+RD+RD+RR;
                point P9 = tp + RD + RD + RR + RR;
                if (Inside(P1, P2, P4, a) || Inside(P6, P8, P9, a))return 1;
                if (Inside(P2, P3, P5, a) || Inside(P5, P7, P8, a))return 2;
                if (Inside(P2, P4, P5, a) || Inside(P5, P6, P8, a))return 3;
                if (Inside(P3, P5, P6, a) || Inside(P4, P5, P7, a))return 4;
            }
        }
    }
    return 0;
}
int main() {
    RD = { 0.5 , -sqrtl(3)*0.5L };
    LD = { -0.5 , -sqrtl(3)*0.5L };
    RR = { 1.0, 0.0 };
    P[0] = { 0.0, 0.0 };
    P[1] = P[0] + LD;
    P[2] = P[0] + RD;
    P[3] = P[0] + RR;
    point A = Get(), B = Get();
    if (Loc(A) == Loc(B))printf("YES\n");
    else printf("NO\n");
}
