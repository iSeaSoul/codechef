// Rain Dreamer MODEL
// iSea @ 2014-08-03 00:32
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
	static const double MAX_TM = 0.975;

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

std::vector<pii> cur;

void try_random_swap(int rs_tm) {
	if (!TN.valid()) {
		return;
	}

	cur.clear();
	memcpy (b, a, sizeof(int) * n);
	int clen = 0;

	rep (i, rs_tm) {
		if (!TN.valid()) {
			return ;
		}
		int l = rand() % n, r = rand() % n;
		if (l > r) swap(l, r);
		if (l == r) continue;
		if (r - l + 1 > n) continue;
		if (clen + r - l + 1 > 2 * n) {
			return ;
		}
		do_swap(b, l, r);
		clen += r - l + 1;
		cur.push_back(pii(l + 1, r + 1));
	}
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
			cur.push_back(pii(n / 2 - i, n / 2 + 1 + i));
			clen += tlen;
		}
	}
}

int main() {
	srand (19890410);

	TN.init();

	scanf ("%d", &n);
	rep (i, n) {
		scanf ("%d", &a[i]);
	}

	vector<pii> ans;

	memcpy (b, a, sizeof(int) * n);
	int64 mins;
	int clen = 0;
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
			ans.push_back(pii(n / 2 - i, n / 2 + 1 + i));
			clen += tlen;
		}
	}
	mins = get_s(b);

	rep (i, 33) {
		try_random_swap(i * 3 + 1);
		int64 cs = get_s(b);
		if (cs < mins) {
			mins = cs;
			ans = cur;
		}
	}

	printf ("%d\n", sz(ans));
	rep (i, sz(ans)) {
		printf ("%d %d\n", ans[i].first, ans[i].second);
	}
	return 0;
}