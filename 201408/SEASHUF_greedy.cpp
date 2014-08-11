// Rain Dreamer MODEL
// iSea @ 2014-08-06 10:58
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
#include <numeric>
#include <cassert>

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
	static const double MAX_TM = 0.955;

	clock_t begin;

	void init() {
		begin = clock();
	}

	bool valid() {
		return 1.0 * (clock() - begin) / CLOCKS_PER_SEC <= MAX_TM;
	}
} TN;

const int MAXN = 100000 + 10;

int n, a[MAXN], b[MAXN], c[MAXN];

void do_swap(int *x, int l, int r) {
	while (l < r) {
		swap(x[l++], x[r--]);
	}
}

int64 get_s(int *x) {
	return abs(accumulate(x, x + n / 2, 0LL) - accumulate(x + n / 2, x + n, 0LL));
}

double rand_double() {
	return (double)rand() / RAND_MAX;
}

int64 base_sc, best_sc;
vector<pii> ans;

void update_sc(int64 csc, vector<pii> res) {
	// printf ("update_sc %I64d %I64d\n", best_sc, csc);
	if (csc < best_sc) {
		best_sc = csc;
		ans = res;
	}
}

void solve_greedy() {
	memcpy (b, a, sizeof(int) * n);
	int clen = 0;
	vector<pii> res;
	rep (i, n / 2) {
		int tlen = (i + 1) * 2;
		if (clen + tlen > 2 * n) {
			break;
		}
		if (!TN.valid()) {
			break;
		}
		memcpy (c, b, sizeof(int) * n);
		do_swap(c, n / 2 - i - 1, n / 2 + i);
		int64 s1 = get_s(b), s2 = get_s(c);
		if (s1 > s2) {
			memcpy (b, c, sizeof(int) * n);
			res.push_back(pii(n / 2 - i, n / 2 + 1 + i));
			clen += tlen;
		}
	}
	update_sc(get_s(b), res);
}

void solve_random() {
	memcpy (b, a, sizeof(int) * n);
	int clen = 0;
	vector<pii> res;
	rep (i, n / 2) {
		int tlen = (i + 1) * 2;
		if (clen + tlen > 2 * n) {
			break;
		}
		if (!TN.valid()) {
			break;
		}
		memcpy (c, b, sizeof(int) * n);
		do_swap(c, n / 2 - i - 1, n / 2 + i);
		int64 s1 = get_s(b), s2 = get_s(c);
		if (s1 > s2 || rand_double() < exp(-(s2 - s1) / (n - (i << 1) + n))) {
			memcpy (b, c, sizeof(int) * n);
			res.push_back(pii(n / 2 - i, n / 2 + 1 + i));
			clen += tlen;
		}
	}
	update_sc(get_s(b), res);
}

void solve_worst() {

}

int main() {
	freopen ("SEASHUF.in", "r", stdin);
	srand (20091120);

	TN.init();

	scanf ("%d", &n);
	rep (i, n) {
		scanf ("%d", &a[i]);
	}

	best_sc = base_sc = get_s(a);

	solve_greedy();
	solve_random();

	while (ans.empty()) {
		solve_random();
	}

	assert (best_sc < base_sc);

	printf ("%d\n", sz(ans));
	rep (i, sz(ans)) {
		printf ("%d %d\n", ans[i].first, ans[i].second);
	}

	return 0;
}