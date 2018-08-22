#include <bits/stdc++.h>

#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif

#ifdef __WIN32
#define LLFORMAT "I64"
#define Rand() ((rand() << 15) + rand())
#else
#define LLFORMAT "ll"
#define Rand() (rand())
#endif

using namespace std;

const int maxn = 3e5 + 10, maxS = 1 << 30, oo = 2e9;

int n, a[maxn], ans, diff;
deque<pair<int, int> > match[2];
map<int, deque<int> > all;
set<int> lft[2];

struct node { node *ch[2]; node() { memset(ch, 0, sizeof ch); } } *root, *pool; int pool_sz;

node* new_node() {
	if(!pool_sz) pool = new node[pool_sz = 1000000];
	return pool + (--pool_sz);
}

void ins(int x, node* &u = root, int S = maxS) {
	if(!u) u = new_node();
	if(!S) return;
	ins(x, u->ch[(S & x) > 0], S >> 1);
	return;
}

int Q(int x, node* &u = root, int S = maxS) {
	if(!S) return 0;
	int d = (x & S) > 0;
	if(!u->ch[d]) return Q(x, u->ch[!d], S >> 1) | S;
	else return Q(x, u->ch[d], S >> 1);
}

void del(int i) {
	lft[(diff & a[i]) > 0].erase(i);
	all[a[i]].pop_front();
	printf("%d", i);
	return;
}

bool check(int i) {
	int f = (a[i] & diff) > 0;
	if(!(lft[f ^ 1].size())) return 1;
	if(lft[f].size() == 1) return all.find(ans ^ a[i]) != all.end() && all[ans ^ a[i]].size();
	int I = i; bool del = 0;
	auto &T = match[f];
	for(;;) {
		if(!T.size()) {
			if(del) T.push_front(make_pair(I, ans ^ a[I]));
			return 0;
		}
		int i = T[0].first;
		if(I == i) {
			del = 1;
			T.pop_front();
			continue;
		}
		if(lft[f].find(i) == lft[f].end() || all.find(ans ^ a[i]) == all.end() || !all[ans ^ a[i]].size()) { T.pop_front(); continue; }
		if(del) T.push_front(make_pair(I, ans ^ a[I]));
		return 1;
	}
}

int main() {
	scanf("%d", &n);
	bool flag = 1; for (int i = 1; i <= n; ++i) scanf("%d", a + i), flag &= ((i == 1) | (a[i] == a[1]));
	if(flag) { for (int i = 1; i <= n; ++i) printf("%d%c", i, " \n"[i == n]); return 0; }
	for (diff = 1 << 30; ; diff >>= 1) {
		bool f[2] = {0, 0};
		for (int i = 1; i <= n; ++i) f[(a[i] & diff) > 0] = 1;
		if(f[0] && f[1]) break;
	}
	ans = oo;
	for (int t, i = 1; i <= n; ++i) {
		if(!(t = ((a[i] & diff) > 0))) ins(a[i]);
		lft[t].insert(i);
		if(all.find(a[i]) == all.end()) all[a[i]] = deque<int>{};
		all[a[i]].push_back(i);
	}
	for (int i = 1; i <= n; ++i) if(a[i] & diff) ans = min(ans, Q(a[i]));
	for (int i = 1; i <= n; ++i) match[(a[i] & diff) > 0].push_back(make_pair(i, ans ^ a[i]));
	int lst = 1; while(!check(lst)) ++lst; del(lst);
	debug("ans = %d\n", ans);
	for (int i = 2; i <= n; ++i) {
		putchar(' ');
		static vector<int> fuck; fuck.clear();
		if(all.find(ans ^ a[lst]) != all.end() && all[ans ^ a[lst]].size()) fuck.push_back(all[ans ^ a[lst]][0]);
		auto &Set = lft[(a[lst] & diff) > 0];
		auto it = Set.begin();
		if(it != Set.end()) fuck.push_back(*it);
		if(it != Set.end()) { ++it; if(it != Set.end()) fuck.push_back(*it); }
		sort(fuck.begin(), fuck.end());
		for (int x: fuck) if(check(x)) { lst = x; break; }
		del(lst);
	}
	putchar('\n');
	return 0;
}

