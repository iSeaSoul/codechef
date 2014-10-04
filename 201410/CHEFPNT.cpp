/*
 * Not the fish.
 * iSea @ 2014-10-04 19:33
 */

#include <bits/stdc++.h>

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

struct tm_node {
	const double MAXTM = 2.50;

	clock_t begin;

	void init() {
		begin = clock();
	}
	void output() {
		fprintf (stderr, "Used Time = %lfs\n", 1.0 * (clock() - begin) / CLOCKS_PER_SEC);
	}
	bool valid() {
		return 1.0 * (clock() - begin) / CLOCKS_PER_SEC < MAXTM;
	}
} tnode;

struct op {int x, y, d; };

const int MAXN = 100 + 3;

int n, m, k;
bool st[MAXN][MAXN];
bool tst[MAXN][MAXN];
vector<op> res;

int valid(int x, int y, bool mz[][MAXN]) {
	return x >= 1 && x <= n && y >= 1 && y <= m && !mz[x][y];
}

int get_empty_num(bool mz[][MAXN], int x, int y, int dx, int dy) {
	int ret;
	for (ret = 0; valid(x + ret * dx, y + ret * dy, mz); ret++) ;
	return ret;
}

void paint(bool (*mz)[MAXN], int x, int y, int dx, int dy) {
	// printf ("paint %d %d %d %d\n", x, y, dx, dy);
	for (int k = 0; valid(x + k * dx, y + k * dy, mz); k++) {
		mz[x + k * dx][y + k * dy] = true;
	}
	for (int k = 1; valid(x - k * dx, y - k * dy, mz); k++) {
		mz[x - k * dx][y - k * dy] = true;
	}
}

void paint(bool (*mz)[MAXN], op c) {
	if (c.d == 0) {
		paint(mz, c.x, c.y, 0, 1);
	} else {
		paint(mz, c.x, c.y, 1, 0);
	}
}

void update_ans(const vector<op>& cres) {
	if (sz(res) == 0 || sz(cres) < sz(res)) {
		res = cres;
	}
}

void solve_greed(bool withRandom = false, bool onlyC = false, bool onlyR = false) {
	memcpy (tst, st, sizeof(tst));
	vector<op> cres;

	while (true) {
		int maxp = 0;
		op maxop;
		if (!onlyC) {
			repf (i, 1, n) {
				int j = 1;
				while (j <= m) {
					while (j <= m && !valid(i, j, tst)) ++j;
					if (j > m) break;
					int k = get_empty_num(tst, i, j, 0, 1);
					if (k > maxp) {
						maxp = k; maxop = {i, j, 0};
					} else if (withRandom && k >= maxp - 1) {
						if (rand() % 3 != 0) {
							maxop = {i, j, 0};
						}
					}
					j += k;
				}
			}
		}
		if (!onlyR) {
			repf (j, 1, m) {
				int i = 1;
				while (i <= n) {
					while (i <= n && !valid(i, j, tst)) ++i;
					if (i > n) break;
					int k = get_empty_num(tst, i, j, 1, 0);
					if (k > maxp) {
						maxp = k; maxop = {i, j, 1};
					} else if (withRandom && k >= maxp - 1) {
						if (rand() % 3 != 0) {
							maxop = {i, j, 1};
						}
					}
					i += k;
				}
			}
		}

		if (maxp == 0) {
			break;
		}

		paint(tst, maxop);
		cres.push_back(maxop);
	}
	update_ans(cres);
}

int main() {
	srand (19890410);

	tnode.init();
	while (scanf ("%d%d%d", &n, &m, &k) != EOF) {
		memset (st, 0, sizeof(st));
		rep (i, k) {
			int x, y;
			scanf ("%d%d", &x, &y);
			st[x][y] = true;
		}

		res.clear();
		solve_greed();
		solve_greed(false, true, false);
		solve_greed(false, false, true);
		rep (rd, 50) {
			if (!tnode.valid()) {
				break;
			}
			solve_greed(true);
		}

		printf ("%d\n", sz(res));
		for (const auto& p : res) {
			printf ("%d %d %d\n", p.x, p.y, p.d);
		}
	}

	return 0;
}