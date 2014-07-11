// Rain Dreamer MODEL
// Create @ 00:17 03-16 2014
// Comment - Tedious SegmentTree with discret

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

const int MAXN = 600000 + 10;

inline int lson(int x) { return (x << 1) + 1; }
inline int rson(int x) { return (x << 1) + 2; }

struct segment_tree_max {
	int idx[MAXN], len;

	void insert_idx(int x) {
		idx[len++] = x;
	}
	void make() {
		sort(idx, idx + len);
		len = unique(idx, idx + len) - idx;
	}
	int get_pos(int k) {
		return lower_bound(idx, idx + len, k) - idx;
	}
	int get_val(int x) {
		return idx[x];
	}

	int64 vl[MAXN << 2], vr[MAXN << 2];
	bool lazy[MAXN << 2];

	void clear() {
		len = 0;
		clz (vl); clz (vr); clz (lazy);
	}

	void combine(int l, int r, int64 cl, int64 cr, int c_id) {
		if (!lazy[c_id]) {
			vl[c_id] = cl; vr[c_id] = cr;
			lazy[c_id] = true;
			return ;
		}
		if (vl[c_id] <= cl && vr[c_id] <= cr) {
			vl[c_id] = cl; vr[c_id] = cr;
			return ;
		}
		if (vl[c_id] >= cl && vr[c_id] >= cr) {
			vl[c_id] = vl[c_id]; vr[c_id] = vr[c_id];
			return ;
		}

		int64 cd = (cr - cl) / (get_val(r) - get_val(l));
		int64 d = (vr[c_id] - vl[c_id]) / (get_val(r) - get_val(l));
		int t_l = l, t_r = r;
		while (t_l <= t_r) {
			int t_mid = (t_l + t_r) >> 1;
			int64 cur_new = cd * (get_val(t_mid) - get_val(l)) + cl;
			int64 cur_old = d * (get_val(t_mid) - get_val(l)) + vl[c_id];
			if ((cur_new >= cur_old) != (cl >= vl[c_id])) {
				t_r = t_mid - 1;
			} else {
				t_l = t_mid + 1;
			}
		}

		int break_p = t_r + 1;
		if (vl[c_id] >= cl) {
			int64 next_cl = vl[c_id], next_cr = d * (get_val(break_p - 1) - get_val(l)) + vl[c_id];
			vl[c_id] = vr[c_id] = lazy[c_id] = 0;

			update (l, break_p - 1, next_cl, next_cr, l, r, c_id);
			update (break_p, r, cd * (get_val(break_p) - get_val(l)) + cl, cr, l, r, c_id);
		} else {
			int64 next_cl = d * (get_val(break_p) - get_val(l)) + vl[c_id], next_cr = vr[c_id];
			vl[c_id] = vr[c_id] = lazy[c_id] = 0;

			update (l, break_p - 1, cl, cd * (get_val(break_p - 1) - get_val(l)) + cl, l, r, c_id);
			update (break_p, r, next_cl, next_cr, l, r, c_id);
		}
	}

	void push_down(int l_cur, int r_cur, int c_id) {
		int mid = (l_cur + r_cur) >> 1;
		int64 d = (vr[c_id] - vl[c_id]) / (get_val(r_cur) - get_val(l_cur));

		combine (l_cur, mid, vl[c_id], (get_val(mid) - get_val(l_cur)) * d + vl[c_id], lson(c_id));
		combine (mid + 1, r_cur, (get_val(mid + 1) - get_val(l_cur)) * d + vl[c_id], vr[c_id], rson(c_id));

		vl[c_id] = vr[c_id] = lazy[c_id] = 0;
	}

	void update(int l, int r, int64 cl, int64 cr, int l_cur, int r_cur, int c_id = 0) {
		//printf ("MAX update %d %d %I64d %I64d %d %d %d\n", l, r, cl, cr, l_cur, r_cur, c_id);
		if (l == l_cur && r == r_cur) {
			combine (l, r, cl, cr, c_id);
			return ;
		}
		if (lazy[c_id]) {
			push_down(l_cur, r_cur, c_id);
		}
		int mid = (l_cur + r_cur) >> 1;
		if (r <= mid) {
			update (l, r, cl, cr, l_cur, mid, lson(c_id));
		} else if (l > mid) {
			update (l, r, cl, cr, mid + 1, r_cur, rson(c_id));
		} else {
			int64 d = (cr - cl) / (get_val(r) - get_val(l));
			int64 new_cl = (get_val(mid + 1) - get_val(l)) * d + cl;
			int64 new_cr = (get_val(mid) - get_val(l)) * d + cl;
			update (l, mid, cl, new_cr, l_cur, mid, lson(c_id));
			update (mid + 1, r, new_cl, cr, mid + 1, r_cur, rson(c_id));
		}
	}

	pair<bool, int64> query(int x, int l_cur, int r_cur, int c_id = 0) {
		if (l_cur == r_cur) {
			return pair<bool, int64>(lazy[c_id], vl[c_id]);
		}
		if (lazy[c_id]) {
			push_down(l_cur, r_cur, c_id);
		}
		int mid = (l_cur + r_cur) >> 1;
		if (x <= mid) {
			return query (x, l_cur, mid, lson(c_id));
		}
		return query (x, mid + 1, r_cur, rson(c_id));
	}

	void cover(int l, int r, int64 a, int64 b) {
		update (get_pos(l), get_pos(r), a, (r - l) * b + a, 0, len - 1);
	}
	pair<bool, int64> query_max(int x) {
		return query(get_pos(x), 0, len - 1);
	}
};

struct segment_tree_sum {
	int idx[MAXN], len;

	void insert_idx(int x) {
		idx[len++] = x;
	}
	void make() {
		sort(idx, idx + len);
		len = unique(idx, idx + len) - idx;
	}
	int get_pos(int k) {
		return lower_bound(idx, idx + len, k) - idx;
	}
	int get_val(int x) {
		return idx[x];
	}

	int64 vl[MAXN << 2], vr[MAXN << 2];
	bool lazy[MAXN << 2];

	void clear() {
		len = 0;
		clz (vl); clz (vr); clz (lazy);
	}

	void push_down(int l_cur, int r_cur, int c_id) {
		int mid = (l_cur + r_cur) >> 1;
		int lson_id = lson(c_id), rson_id = rson(c_id);
		int64 d = (vr[c_id] - vl[c_id]) / (get_val(r_cur) - get_val(l_cur));

		vl[lson_id] += vl[c_id];
		vr[lson_id] += (get_val(mid) - get_val(l_cur)) * d + vl[c_id];
		vl[rson_id] += (get_val(mid + 1) - get_val(l_cur)) * d + vl[c_id];
		vr[rson_id] += vr[c_id];
		lazy[lson_id] = lazy[rson_id] = true;

		vl[c_id] = vr[c_id] = lazy[c_id] = 0;
	}

	void update(int l, int r, int64 cl, int64 cr, int l_cur, int r_cur, int c_id = 0) {
		//printf ("SUM update %d %d %I64d %I64d %d %d %d\n", l, r, cl, cr, l_cur, r_cur, c_id);
		if (l == l_cur && r == r_cur) {
			vl[c_id] += cl; vr[c_id] += cr;
			lazy[c_id] = true;
			return ;
		}
		if (lazy[c_id]) {
			push_down(l_cur, r_cur, c_id);
		}
		int mid = (l_cur + r_cur) >> 1;
		if (r <= mid) {
			update (l, r, cl, cr, l_cur, mid, lson(c_id));
		} else if (l > mid) {
			update (l, r, cl, cr, mid + 1, r_cur, rson(c_id));
		} else {
			int64 d = (cr - cl) / (get_val(r) - get_val(l));
			int64 new_cl = (get_val(mid + 1) - get_val(l)) * d + cl;
			int64 new_cr = (get_val(mid) - get_val(l)) * d + cl;
			update (l, mid, cl, new_cr, l_cur, mid, lson(c_id));
			update (mid + 1, r, new_cl, cr, mid + 1, r_cur, rson(c_id));
		}
	}

	int64 query(int x, int l_cur, int r_cur, int c_id = 0) {
		if (l_cur == r_cur) {
			return vl[c_id];
		}
		if (lazy[c_id]) {
			push_down(l_cur, r_cur, c_id);
		}
		int mid = (l_cur + r_cur) >> 1;
		if (x <= mid) {
			return query (x, l_cur, mid, lson(c_id));
		}
		return query (x, mid + 1, r_cur, rson(c_id));
	}

	void cover(int l, int r, int64 a, int64 b) {
		update (get_pos(l), get_pos(r), a, (r - l) * b + a, 0, len - 1);
	}
	int64 query_sum(int x) {
		return query(get_pos(x), 0, len - 1);
	}
};

struct operation {
	int a, b, c, d;
	int op_type;

	void input() {
		scanf ("%d", &op_type);
		if (op_type == 3) {
			scanf ("%d", &a);
		} else {
			scanf ("%d%d%d%d", &a, &b, &c, &d);
		}
	}
};

segment_tree_sum st_sum;
segment_tree_max st_max;
operation op[MAXN];
int n, m;

bool input() {
	if (scanf ("%d%d", &n, &m) == EOF) {
		return false;
	}
	rep (i, m) {
		op[i].input();
	}
	return true;
}

void make_tree() {
	st_sum.clear(); st_max.clear();
	rep (i, m) {
		if (op[i].op_type == 3) {
			st_sum.insert_idx(op[i].a);
			st_max.insert_idx(op[i].a);
		} else if (op[i].op_type == 2) {
			st_sum.insert_idx(op[i].a);
			st_sum.insert_idx(op[i].b);
		} else {
			st_max.insert_idx(op[i].a);
			st_max.insert_idx(op[i].b);
		}
	}
	st_sum.insert_idx(1); st_sum.insert_idx(n); st_sum.make(); 
	st_max.insert_idx(1); st_max.insert_idx(n); st_max.make();
}

void solve() {
	make_tree();

	rep (i, m) {
		if (op[i].op_type == 3) {
			pair<bool, int64> res = st_max.query_max(op[i].a);
			if (res.first == false) {
				puts ("NA");
			} else {
				int64 ans = st_sum.query_sum(op[i].a) + res.second;
				printf ("%lld\n", ans);
			}
		} else if (op[i].op_type == 2) {
			st_sum.cover(op[i].a, op[i].b, op[i].d, op[i].c);
		} else {
			st_max.cover(op[i].a, op[i].b, op[i].d, op[i].c);
		}
	}
}

int main() {
	while (input()) solve();
	return 0;
}
