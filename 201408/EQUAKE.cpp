// Rain Dreamer MODEL
// iSea @ 2014-08-02 10:42
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

const int MAXN = 800000 + 10;

int n, a[MAXN];

int shift(int x, int base) {
	return (x % base) * 10 + x / base;
}

inline int lson(int x) { return (x << 1) + 1; }
inline int rson(int x) { return (x << 1) + 2; }

const int LOOP = 12;

struct segment_tree {
	struct node {
		int a[LOOP];
		int off;

		void init(int x) {
			int base = 1;
			while (base * 10 <= x) {
				base *= 10;
			}

			a[0] = x;
			repf (i, 1, LOOP - 1) {
				a[i] = shift(a[i - 1], base);
			}
		}
		void add_off(int noff) {
			off = (off + noff) % LOOP;
		}
		int get_val(int idx) {
			return a[(idx + off) % LOOP];
		}
		int get_active_val() {
			// printf ("off: %d\n", off);
			// rep (i, LOOP) {
			// 	printf ("%d%c", a[i], i == LOOP - 1? '\n' : ' ');
			// }
			return a[off];
		}
		void merge(node x, node y) {
			rep (i, LOOP) {
				a[i] = max(x.get_val(i), y.get_val(i));
			}
			off = 0;
		}
	};

	node c[MAXN << 2];
	int lazy[MAXN << 2];

	void push_up(int c_id) {
		// printf ("push_up %d\n", c_id);
		c[c_id].merge(c[lson(c_id)], c[rson(c_id)]);
	}

	void push_down(int c_id) {
		// printf ("push_down %d\n", c_id);
		int lson_id = lson(c_id), rson_id = rson(c_id);
		c[lson_id].add_off(lazy[c_id]); lazy[lson_id] += lazy[c_id];
		c[rson_id].add_off(lazy[c_id]); lazy[rson_id] += lazy[c_id];
		lazy[c_id] = 0;
	}

	void build(int l, int r, int c_id = 0) {
		lazy[c_id] = 0;
		if (l == r) {
			c[c_id].init(a[l]);
			return ;
		}
		int mid = (l + r) >> 1;
		build (l, mid, lson(c_id));
		build (mid + 1, r, rson(c_id));
		push_up(c_id);
	}

	void update(int l, int r, int off, int l_cur = 0, int r_cur = n - 1, int c_id = 0) {
		// printf ("update %d %d %d %d %d %d\n", l, r, off, l_cur, r_cur, c_id);
		if (l == l_cur && r == r_cur) {
			c[c_id].add_off(off);
			lazy[c_id] += off;
			return ;
		}
		if (lazy[c_id]) {
			push_down(c_id);
		}
		int mid = (l_cur + r_cur) >> 1;
		if (l <= mid) {
			update(l, min(r, mid), off, l_cur, mid, lson(c_id));
		}
		if (r > mid) {
			update (max(l, mid + 1), r, off, mid + 1, r_cur, rson(c_id));
		}
		push_up(c_id);
	}

	int query(int l, int r, int l_cur = 0, int r_cur = n - 1, int c_id = 0) {
		if (l == l_cur && r == r_cur) {
			return c[c_id].get_active_val();
		}
		if (lazy[c_id]) {
			push_down(c_id);
		}
		int ret = 0;
		int mid = (l_cur + r_cur) >> 1;
		if (l <= mid) {
			ckmax(ret, query(l, min(r, mid), l_cur, mid, lson(c_id)));
		}
		if (r > mid) {
			ckmax(ret, query(max(l, mid + 1), r, mid + 1, r_cur, rson(c_id)));
		}
		return ret;
	}
} st;

int main() {
	scanf ("%d", &n);
	rep (i, n) {
		scanf ("%d", &a[i]);
	}
	st.build(0, n - 1);

	repcase {
		int op, l, r, off;
		scanf ("%d%d%d", &op, &l, &r);
		if (op == 1) {
			printf ("%d\n", st.query(l, r));
		} else {
			scanf ("%d", &off);
			st.update(l, r, off);
		}
	}
	return 0;
}