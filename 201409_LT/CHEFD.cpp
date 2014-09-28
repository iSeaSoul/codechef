// Rain Dreamer MODEL
// iSea @ 2014-09-28 14:17
// Comment - 

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

const int facs[3] = {2, 3, 5};
const int MAXN = 100000 + 10;

int n, m, a[MAXN];

inline int lson(int x) { return (x << 1) + 1; }
inline int rson(int x) { return (x << 1) + 2; }

struct segmentTree {

	int lazy[MAXN << 2][3];
	int num[MAXN << 2];

	void build(int l, int r, int c_id = 0) {
		rep (i, 3) lazy[c_id][i] = 0;
		if (l == r) {
			num[c_id] = a[l];
			return ;
		}
		int mid = (l + r) >> 1;
		build (l, mid, lson(c_id));
		build (mid + 1, r, rson(c_id));
	}

	void pushDown(int c_id) {
		int lson_id = lson(c_id), rson_id = rson(c_id);
		rep (i, 3) {
			if (lazy[c_id][i]) {
				lazy[lson_id][i] += lazy[c_id][i];
				lazy[rson_id][i] += lazy[c_id][i];
				lazy[c_id][i] = 0;
			}
		}
	}

	void update(int l, int r, int fid, int l_cur = 0, int r_cur = n - 1, int c_id = 0) {
		if (l == l_cur && r == r_cur) {
			lazy[c_id][fid] += 1;
			return ;
		}
		pushDown(c_id);
		int mid = (l_cur + r_cur) >> 1;
		if (l <= mid) {
			update (l, min(r, mid), fid, l_cur, mid, lson(c_id));
		}
		if (r > mid) {
			update (max(l, mid + 1), r, fid, mid + 1, r_cur, rson(c_id));
		}
	}

	void updateVal(int x, int val, int l_cur = 0, int r_cur = n - 1, int c_id = 0) {
		if (l_cur == r_cur) {
			rep (i, 3) lazy[c_id][i] = 0;
			num[c_id] = val;
			return ;
		}
		pushDown(c_id);
		int mid = (l_cur + r_cur) >> 1;
		if (x <= mid) {
			updateVal (x, val, l_cur, mid, lson(c_id));
		}
		if (x > mid) {
			updateVal (x, val, mid + 1, r_cur, rson(c_id));
		}
	}

	int queryVal(int x, int l_cur = 0, int r_cur = n - 1, int c_id = 0) {
		if (l_cur == r_cur) {
			return getVal(c_id);
		}
		pushDown(c_id);
		int mid = (l_cur + r_cur) >> 1;
		if (x <= mid) {
			return queryVal (x, l_cur, mid, lson(c_id));
		}
		if (x > mid) {
			return queryVal (x, mid + 1, r_cur, rson(c_id));
		}
	}

	int getVal(int c_id) {
		int ret = num[c_id];
		rep (i, 3) {
			int fac = facs[i];
			int maxt = lazy[c_id][i];
			rep (j, maxt) {
				if (ret % fac == 0) {
					ret /= fac;
				} else {
					break;
				}
			}
		}
		return ret;
	}	
} st;

int main() {
	while (scanf ("%d", &n) != EOF) {
		rep (i, n) {
			scanf ("%d", &a[i]);
		}
		st.build(0, n - 1);

		scanf ("%d", &m);
		rep (i, m) {
			int op, l, r, facp, pos, num;

			scanf ("%d", &op);

			if (op == 1) {
				scanf ("%d%d%d", &l, &r, &facp);
				if (facp == 2) facp = 0;
				else if (facp == 3) facp = 1;
				else facp = 2;

				st.update(l - 1, r - 1, facp);
			} else {
				scanf ("%d%d", &pos, &num);

				st.updateVal(pos - 1, num);
			}
		}

		rep (i, n) {
			printf ("%d%c", st.queryVal(i), " \n"[i == n - 1]);
		}
	}
	return 0;
}