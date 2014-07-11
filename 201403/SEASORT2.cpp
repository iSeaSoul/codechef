// Rain Dreamer MODEL
// Create @ 12:55 03-16 2014
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

const int MAXN = 10000 + 10;
const double MAX_TM = 0.50;

struct tm_node {
 
    clock_t begin;
 
    void init() {
    	begin = clock();
    }
 
    bool valid() {
    	return 1.0 * (clock() - begin) / CLOCKS_PER_SEC <= MAX_TM;
    }
} TN;

int n, a[MAXN], num[MAXN], sorted[MAXN];

void try_swap(int l, int r) {
	for (; l < r; ++l, --r) {
		swap (num[l], num[r]);
	}
}

int get_idx(int ind, int x) {
	while (num[ind] != x) ++ind;
	return ind;
}

vector<pii> solve_bf(int &sc) {
	memcpy (num, a, sizeof(a));
	
	vector<pii> res;
	sc = 0;
	rep (i, n) {
		if (num[i] != sorted[i]) {
			int l = i, r = get_idx(i + 1, sorted[i]);
			try_swap(l, r);
			res.push_back(pii(l, r));
			sc += r - l + 1;
		}
	}
	sc += n * sz(res);
	return res;
}

int get_idx_rev(int ind, int x) {
	while (num[ind] != x) --ind;
	return ind;
}

vector<pii> solve_bf_rev(int &sc) {
	memcpy (num, a, sizeof(a));

	vector<pii> res;
	sc = 0;
	repd (i, n - 1, 0) {
		if (num[i] != sorted[i]) {
			int l = get_idx_rev(i - 1, sorted[i]), r = i;
			try_swap(l, r);
			res.push_back(pii(l, r));
			sc += r - l + 1;
		}
	}
	sc += n * sz(res);
	return res;
}

vector<pii> solve_bf_both(int &sc) {
	memcpy (num, a, sizeof(a));

	vector<pii> res;
	sc = 0;
	int ldl = 0, ldr = n - 1;
	while (ldl < ldr) {
		while (num[ldl] == sorted[ldl] && ldl < ldr) ++ldl;
		while (num[ldr] == sorted[ldr] && ldl < ldr) --ldr;
		if (ldl >= ldr) break;

		int l = ldl, r = get_idx(ldl + 1, sorted[ldl]);
		int cl = get_idx_rev(ldr - 1, sorted[ldr]), cr = ldr;

		if (r - l < cl - cr) {
			try_swap(l, r);
			res.push_back(pii(l, r));
			sc += r - l + 1;
			++ldl;
		} else {
			try_swap(cl, cr);
			res.push_back(pii(cl, cr));
			sc += cr - cl + 1;
			--ldr;
		}
	}
	sc += n * sz(res);
	return res;
}

int main() {
	TN.init();

	scanf ("%d", &n);
	rep (i, n) {
		scanf ("%d", &a[i]);
		sorted[i] = a[i];
	}

	sort (sorted, sorted + n);

	int score;
	vector<pii> ans = solve_bf_both(score);

	if (TN.valid()) {
		int sc;
		vector<pii> res = solve_bf_rev(sc);
		if (sc < score) {
			ans = res;
		}
	}
	if (TN.valid()) {
		int sc;
		vector<pii> res = solve_bf(sc);
		if (sc < score) {
			ans = res;
		}
	}

	printf ("%d\n", sz(ans));
	repeach (it, ans) {
		printf ("%d %d\n", it->first + 1, it->second + 1);
	}

    return 0;
}

