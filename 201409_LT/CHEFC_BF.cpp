// Rain Dreamer MODEL
// iSea @ 2014-09-28 14:56
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

const int MAXN = 100000 + 10;

int n, m, a[MAXN], b[MAXN];

void solveSmall() {
	rep (mi, m) {
		int op, l, r;
		scanf ("%d%d%d", &op, &l, &r);
		--l; --r;

		if (op == 1) {
			int ret = 1;
			repf (i, l + 1, r) {
				ret += (a[i] != a[i - 1]);
			}
			printf ("%d\n", ret);
		} else {
			repf (i, l, r) {
				b[i - l] = a[i];
			}
			rep (i, l) {
				b[r - l + i + 1] = a[i];
			}
			rep (i, r + 1) {
				a[i] = b[i];
			}
		}
	}
}

int sum[MAXN];

void solveNaive() {
	repf (i, 1, n - 1) {
		sum[i] = sum[i - 1] + (a[i] == a[i - 1]);
	}
	rep (mi, m) {
		int op, l, r;
		scanf ("%d%d%d", &op, &l, &r);
		--l; --r;

		if (op == 1) {
			int ret = r - l + 1;
			ret -= (sum[r] - sum[l]);
			printf ("%d\n", ret);
		}
	}
}

int main() {
	repcase {
		scanf ("%d", &n);
		rep (i, n) {
			scanf ("%d", &a[i]);
		}
		scanf ("%d", &m);
		if (m <= 1000 && n <= 100) {
			solveSmall();
		} else {
			solveNaive();
		}
	}
	return 0;
}