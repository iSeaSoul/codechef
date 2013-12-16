// New Ryan
// Create @ 12:59 12-16 2013
// Comment - 

#include <cmath>
#include <cstdio>
#include <cassert>
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
#define clz(x) memset (x, 0, sizeof(x))
#define read(x) freopen (x, "r", stdin)
#define wrte(x) freopen (x, "w", stdout)
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (scanf ("%d", &t); t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

typedef long long int64;
typedef pair<int, int> pii;
typedef pair<int64, int64> pll;
typedef pair<double, double> pdd;

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void ckmin(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void ckmax(T &a, const T b) { if (b > a) a = b; }

// Self Template Code END

const int MAXN = 1000 + 10;

int n, c[MAXN][MAXN];
bool vis[MAXN][MAXN];

struct op {
	int lx, ly, rx, ry, c;

	op(int _0, int _1, int _2, int _3, int _4):
		lx(_0), ly(_1), rx(_2), ry(_3), c(_4) {}

	void print() const {
		printf ("%d %d %d %d %d\n", c, lx + 1, rx + 1, ly + 1, ry + 1);
	}
};

vector<op> ans;

void try_paint_h(int x, int y) {
	int max_x = x;
	while (max_x < n && !vis[max_x][y] && c[max_x][y] == c[x][y]) {
		max_x += 1;
	}
	max_x -= 1;
	repf (i, x, max_x) {
		vis[i][y] = true;
	}
	ans.push_back(op(x, y, max_x, y, c[x][y]));
}

void try_paint_v(int x, int y) {
	int max_y = y;
	while (max_y < n && !vis[x][max_y] && c[x][max_y] == c[x][y]) {
		max_y += 1;
	}
	max_y -= 1;
	repf (i, y, max_y) {
		vis[x][i] = true;
	}
	ans.push_back(op(x, y, x, max_y, c[x][y]));
}

void try_paint(int x, int y) {
	int max_y = y;
	while (max_y < n && !vis[x][max_y] && c[x][max_y] == c[x][y]) {
		max_y += 1;
	}
	max_y -= 1;
	int max_x = x;
	while (max_x < n && !vis[max_x][y] && c[max_x][y] == c[x][y]) {
		max_x += 1;
	}
	max_x -= 1;
	if (max_x - x >= max_y - y) {
		repf (i, x, max_x) {
			vis[i][y] = true;
		}
		ans.push_back(op(x, y, max_x, y, c[x][y]));
	}
	else {
		repf (i, y, max_y) {
			vis[x][i] = true;
		}
		ans.push_back(op(x, y, x, max_y, c[x][y])); 
	}
}

void solve() {
	ans.clear(); clz(vis);
	rep (i, n) rep (j, n) {
		if (!vis[i][j] && c[i][j]) {
			try_paint_h(i, j);
		}
	}
	vector<op> pre_ans = ans;
	/*rep (i, sz(ans)) {
		pre_ans.push_back(ans[i]);
	}*/

	ans.clear(); clz(vis);
	rep (i, n) rep (j, n) {
		if (!vis[i][j] && c[i][j]) {
			try_paint_v(i, j);
		}
	}

	if (sz(ans) < sz(pre_ans)) {
		pre_ans = ans;
	}

	ans.clear(); clz(vis);
	rep (i, n) rep (j, n) {
		if (!vis[i][j] && c[i][j]) {
			try_paint(i, j);
		}
	}

	printf ("%d\n", sz(ans));

	rep (i, sz(ans)) {
		ans[i].print();
	}
}

int main() {
	while (~scanf ("%d", &n)) {
		rep (i, n) rep (j, n) {
			scanf ("%d", &c[i][j]);
		}
		solve();
	}
    return 0;
}

