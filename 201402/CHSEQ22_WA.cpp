// New Ryan
// Create @ 20:21 02-17 2014
// Comment - 

#include <cmath>
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

const int MAXN = 100000  + 10;
const int mod = 1000000007;

int M(int x, int y) { return (int64)x * y % mod; } // x * y

int mon(int a, int p) {
	int res = 1;
	while (p) {
		if (p & 1) res = M(res, a);
		a = M(a, a);
		p >>= 1;
	}
	return res;
}

int n, m;
set<int> seg_ends[MAXN];

bool input() {
	if (scanf ("%d%d", &n, &m) == EOF) {
		return false;
	}
	rep (i, m) {
		int l, r;
		scanf ("%d%d", &l, &r);
		seg_ends[r].insert (l);
	}
	return true;
}

void solve() {
	int cnt = 0;
	repd (i, n, 1) {
		int cursz = sz(seg_ends[i]);
		if (cursz == 0) continue ;
		cnt += 1;
        
		if (cursz == 1) {
			seg_ends[i].clear();
			continue ;
		}

		set<int>::reverse_iterator it = seg_ends[i].rbegin();
		set<int>::reverse_iterator jt = (it++);
		while (true) {
			seg_ends[(*jt - 1)].insert (*it);
			if (it == seg_ends[i].rend()) {
				break ;
			}
			++it; ++jt;
		}
		seg_ends[i].clear();
	}

	printf ("%d\n", mon(2, cnt));
}

int main() {
	while (input()) solve();
	return 0;
}

