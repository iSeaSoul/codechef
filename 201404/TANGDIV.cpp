// Rain Dreamer MODEL
// Create @ 21:58 04-12 2014
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

struct seg {
	int l, r;

	void input() {
		scanf ("%d%d", &l, &r);
	}
	bool contains(const seg& s) {
		if (r < l) {
			if (s.r < s.l) {
				return l <= s.l && s.r <= r;
			}
			return s.r <= r;
		}
		if (s.r < s.l) {
			return false;
		}
		return l <= s.l && s.r <= r;
	}
};

const int MAXN = 500 + 10;

seg a[MAXN], b[MAXN];
int n, m;

void input() {
	scanf ("%*d%d%d", &n, &m);
	rep (i, n) a[i].input();
	rep (i, m) b[i].input();
}

void solve() {
	bool all_contain = true;
	rep (i, n) {
		bool can_contain = false;
		rep (j, m) {
			can_contain |= b[j].contains(a[i]);
			if (can_contain) break;
		}
		all_contain &= can_contain;
		if (!all_contain) break;
	}
	puts (all_contain? "Yes" : "No");
}

int main() {
	repcase {
		input(); solve();
	}
	return 0;
}

