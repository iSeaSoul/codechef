// Rain Dreamer MODEL
// iSea @ 2014-09-05 22:52
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

const int MAXN = 200000 + 10;

int a[MAXN], b[MAXN], un;
int n, m;

int get_id(int x) {
	return lower_bound(b, b + un, x) - b + 1;
}

struct persist_st {
	struct node {
		int l, r, val;
	};
	
	node n[MAXN * 40];
	int r_cnt;
	
	void init() {
		r_cnt = 0;
	}
	int build(int l, int r) {
		int curR = r_cnt++;
		n[curR].val = 0;
		if (l != r) {
			n[curR].l = build (l, (l + r) >> 1);
			n[curR].r = build (((l + r) >> 1) + 1, r);
		}
		return curR;
	}
	void update_dif(int cur_root, int root) {
		n[cur_root].val = n[root].val + 1;
	}
	int update(int root, int pos) {
		int nextR = r_cnt++;
		int resR = nextR;
		update_dif (nextR, root);
		
		int l = 1, r = un;
		while (l != r) {
			int mid = (l + r) >> 1;
			if (pos <= mid) {
				n[nextR].l = r_cnt++; n[nextR].r = n[root].r;
				nextR = n[nextR].l; root = n[root].l;
				r = mid;
			} else {
				n[nextR].r = r_cnt++; n[nextR].l = n[root].l;
				nextR = n[nextR].r; root = n[root].r;
				l = mid + 1;
			}
			update_dif (nextR, root);      
		}
		
		return resR;
	}
	int getsum(int l_root, int r_root, int pos, bool can_equal = false) {
		// [l_root...r_root] < pos
		int cnt = 0;
		int l = 1, r = un;
		while (l != r) {
			int mid = (l + r) >> 1;
			if (pos <= mid) {
				l_root = n[l_root].l;
				r_root = n[r_root].l;
				r = mid;
			} else {
				cnt += (n[n[r_root].l].val - n[n[l_root].l].val);
				l_root = n[l_root].r;
				r_root = n[r_root].r;
				l = mid + 1;
			}
		}
		if (can_equal) {
			cnt += n[r_root].val - n[l_root].val;
		}
		return cnt;
	}
};

persist_st pst;
int root_id[MAXN];

int main() {
	while (scanf ("%d%d", &n, &m) != EOF) {
		rep (i, n) {
			scanf ("%d", &a[i]);
			b[i] = a[i];
		}
		sort (b, b + n);
		un = unique(b, b + n) - b;

		int64 ret = 0;
		pst.init();
		root_id[0] = pst.build(1, un);
		rep (i, n) {
			int numidx = get_id(a[i]);
			ret += i - pst.getsum(root_id[0], root_id[i], numidx, true);
			root_id[i + 1] = pst.update(root_id[i], numidx);
		}

		rep (i, m) {
			int u, v;
			scanf ("%d%d", &u, &v);
			--u, --v;
			if (a[u] == a[v]) {
				printf ("%lld\n", ret);
				continue ;
			}
			if (u > v) swap(u, v);
			int dif = pst.getsum(root_id[u + 1], root_id[v], get_id(a[v]), true) +
				pst.getsum(root_id[u + 1], root_id[v], get_id(a[v])) -
				pst.getsum(root_id[u + 1], root_id[v], get_id(a[u]), true) -
				pst.getsum(root_id[u + 1], root_id[v], get_id(a[u]));
			if (a[u] < a[v]) dif += 1;
			else dif -= 1;
			printf ("%lld\n", ret + dif);
		}
	}
	return 0;
}