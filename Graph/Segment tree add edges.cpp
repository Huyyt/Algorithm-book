//Segment tree add edges
struct E
{
        int value, modvalue;
} a[MAXN << 3];
pair<int, int> b[MAXN];
int root, l[MAXN << 3], r[MAXN << 3], tot;
int build(int a, int b)
{
        int x;
        if (a == b)
        {
                x =::b[a].second;
        }
        else
        {
                x = ++tot;
        }
        if (a == b)
        {
                return x;
        }
        int mid = (a + b) >> 1;
        l[x] = build(a, mid);
        r[x] = build(mid + 1, b);
        addedge(x, l[x]);
        addedge(x, r[x]);
        return x;
}
void ins(int x, int a, int b, int c, int d, int p)
{
        if (d < c)
        {
                return ;
        }
        if (c <= a && b <= d)
        {
                addedge(p, x);
                return;
        }
        int mid = (a + b) >> 1;
        if (c <= mid)
        {
                ins(l[x], a, mid, c, d, p);
        }
        if (d > mid)
        {
                ins(r[x], mid + 1, b, c, d, p);
        }
}
int main()
{
        read(n), read(m);
        for (i = 1; i <= n; i++)
        {
                read(a[i].p), read(a[i].r), read(a[i].c);
                b[i] = P(a[i].p, i);
        }
        sort(b + 1, b + n + 1);
        tot = n;
        root = build(1, n);
        for (i = 1; i <= n; i++)
        {
                int l = askl(a[i].p - a[i].r);
                int r = askr(a[i].p + a[i].r);
                ins(root, 1, n, l, r, i);
        }
}
