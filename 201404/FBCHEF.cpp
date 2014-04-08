// Rain Dreamer MODEL
// Create @ 21:10 04-08 2014
// Comment - 

#pragma comment(linker,"/STACK:65536000")

#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bitset>
#include <queue>
#include <map>
#include <set>

using namespace std;

// Self Template Code BGEIN

#define sz(x) ((int)((x).size()))
#define out(x) printf(#x" %d\n", x)
#define all(x) (x).begin(), (x).end()
#define RD(x) freopen (x, "r", stdin)
#define WT(x) freopen (x, "w", stdout)
#define clz(x) memset (x, 0, sizeof(x))
#define cln(x) memset (x, -1, sizeof(x))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (scanf ("%d", &t); t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

typedef long long int64;
typedef pair<int, int> pii;

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void ckmin(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void ckmax(T &a, const T b) { if (b > a) a = b; }

// Self Template Code END

#define lowbit(x) ((x) & (-(x)))

const int MAXN = 100000 + 10;
const int INF = (-1u) >> 1;
const int ROOT = 1;

int n, val[MAXN];
vector<int> g[MAXN];

int pa[MAXN], level_id[MAXN], level_rev_id[MAXN];
int level_lcnt[MAXN], level_rcnt[MAXN];

void make_level_tree() {
	queue<int> q;
	cln (pa);
	q.push(ROOT); pa[ROOT] = 0;

	int cnt = 1;
	level_rev_id[cnt] = ROOT;
	level_id[ROOT] = cnt++; 

	while (!q.empty()) {
		int cur = q.front(); q.pop();
		int cur_idx = level_id[cur];
		level_lcnt[cur_idx] = cnt;

		repeach (it, g[cur]) {
			if (pa[*it] == -1) {
				q.push(*it); pa[*it] = cur;
				level_rev_id[cnt] = *it;
				level_id[*it] = cnt++;
			}
		}

		level_rcnt[cur_idx] = (cnt - 1);
	}
}

pii get_son_level_interval(int l, int r) {
	return pii(level_lcnt[l], level_rcnt[r]);
}

pii get_son_level_interval(pii cur) {
	return get_son_level_interval(cur.first, cur.second);
}

int dfs_id[MAXN], dfs_rev_id[MAXN], dfs_out_id[MAXN], dfs_tms;

void dfs(int x) {
	dfs_rev_id[dfs_tms] = x;
	dfs_id[x] = dfs_tms++;
	repeach (it, g[x]) {
		if (dfs_id[*it] == -1) {
			dfs (*it);
		}
	}
	dfs_out_id[x] = dfs_tms - 1;
}

void make_dfs_tree() {
	cln (dfs_id); 
	dfs_tms = 1;
	dfs (ROOT);
}

pii get_sub_tree_interval(int x) {
	return pii(dfs_id[x], dfs_out_id[x]);
}

struct binary_index_tree {
	int a[MAXN];

	void clear(int _n) {
		n = _n;
		memset (a, 0, sizeof(int) * n);
	}
	void update(int x, int y = 1) {
		for (; x <= n; x += lowbit(x)) {
			a[x] += y;
		}
	}
	int getsum(int x) {
		int res = 0;
		for (; x; x -= lowbit(x)) {
			res += a[x];
		}
		return res;
	}
	int getsum(int L, int R) {
		return getsum(R) - getsum(L - 1);
	}
};

binary_index_tree bit;

inline int lson(int x) { return (x << 1) + 1; }
inline int rson(int x) { return (x << 1) + 2; }

struct segment_tree {
	int minv[MAXN << 2], minid[MAXN << 2], lazy[MAXN << 2];

	void init() {
		build (1, n);
	}

	void build(int l_cur, int r_cur, int c_id = 0) {
		lazy[c_id] = 0;
		if (l_cur == r_cur) {
			minv[c_id] = val[l_cur]; minid[c_id] = l_cur;
			return ;
		}
		int mid = (l_cur + r_cur) >> 1;
		build (l_cur, mid, lson(c_id));
		build (mid + 1, r_cur, rson(c_id));
		push_up(c_id);
	}

	void push_up(int c_id) {
		int lson_id = lson(c_id), rson_id = rson(c_id);
		if (minv[lson_id] > minv[rson_id]) {
			minv[c_id] = minv[rson_id]; minid[c_id] = minid[rson_id];
		} else {
			minv[c_id] = minv[lson_id]; minid[c_id] = minid[lson_id];
		}
	}

	void push_down(int l_cur, int r_cur, int c_id) {
		int mid = (l_cur + r_cur) >> 1;
		int lson_id = lson(c_id), rson_id = rson(c_id);
		minv[lson_id] += lazy[c_id]; lazy[lson_id] += lazy[c_id];
		minv[rson_id] += lazy[c_id]; lazy[rson_id] += lazy[c_id];
		lazy[c_id] = 0;
	}

	void update(int l, int r, int x, int l_cur = 1, int r_cur = n, int c_id = 0) {
		if (l == l_cur && r == r_cur) {
			if (minv[c_id] != INF) {
				minv[c_id] += x; lazy[c_id] += x;
			}
			return ;
		}
		if (lazy[c_id] != 0) {
			push_down (l_cur, r_cur, c_id);
		}
		int mid = (l_cur + r_cur) >> 1;
		if (l <= mid) {
			update (l, min(r, mid), x, l_cur, mid, lson(c_id));
		}
		if (r > mid) {
			update (max(l, mid + 1), r, x, mid + 1, r_cur, rson(c_id));
		}
		push_up(c_id);
	}

	void cleanup(int idx, int l_cur = 1, int r_cur = n, int c_id = 0) {
		if (l_cur == r_cur) {
			minv[c_id] = INF; minid[c_id] = l_cur;
			return ;
		}
		if (lazy[c_id] != 0) {
			push_down (l_cur, r_cur, c_id);
		}
		int mid = (l_cur + r_cur) >> 1;
		if (idx <= mid) {
			cleanup (idx, l_cur, mid, lson(c_id));
		} else {
			cleanup (idx, mid + 1, r_cur, rson(c_id));
		}
		push_up(c_id);
	}

	bool has_nag() {
		return minv[0] <= 0;
	}

	int get_gmin_id_with_cleanup() {
		int res = minid[0];
		cleanup(res);
		return res;
	}
};

segment_tree st;

void throw_down(int w, int x) {
	pii c_interval = pii(level_id[w], level_id[w]);
	int flag = x > 0? 1 : -1;
	for (x = abs(x); x; x >>= 1) {
		if (c_interval.first > c_interval.second) {
			// no more son node
			break ;
		}
		st.update(c_interval.first, c_interval.second, - flag * x);
		c_interval = get_son_level_interval(c_interval);
	}
}

void throw_up(int w, int x) {
	if (w != ROOT && x >= 2) {
		throw_down(w, x);
		if (x >= 4) {
			throw_down(w, -(x >> 2));
		}
		throw_up(pa[w], (x >> 1));
	} else {
		throw_down(w, x);
	}
}

void throw_bomb(int w, int x) {
	throw_up(w, x);

	while (st.has_nag()) {
		int idx = st.get_gmin_id_with_cleanup();
		bit.update(dfs_id[level_rev_id[idx]]);
	}
}

int get_survived(int w) {
	pii sub_w = get_sub_tree_interval(w);
	return bit.getsum(sub_w.first, sub_w.second);
}

void query() {
	int Qnum, op, w, x;
	for (scanf ("%d", &Qnum); Qnum; Qnum--) {
		scanf ("%d", &op);
		if (op == 1) {
			scanf ("%d%d", &w, &x);
			throw_bomb(w, x);
		} else {
			scanf ("%d", &w);
			printf ("%d\n", get_survived(w));
		}
	}
}

bool input() {
	if (scanf ("%d", &n) == EOF) {
		return false;
	}
	repf (i, 1, n) {
		scanf ("%d", &val[i]);
		g[i].clear();
	}
	rep (i, n - 1) {
		int u, v;
		scanf ("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	return true;
}

void solve() {
	make_level_tree();
	make_dfs_tree();
	bit.clear(n);
	st.init();

	query();
}

int main() {
	while (input()) solve();
	return 0;
}
