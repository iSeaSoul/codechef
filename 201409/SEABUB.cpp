// Rain Dreamer MODEL
// iSea @ 2014-09-06 02:22
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

const int MAXN = 100 + 10;

struct tm_node {
	clock_t begin;

	void init() {
		begin = clock();
	}
	void output() {
		fprintf (stderr, "Used Time = %lfs\n", 1.0 * (clock() - begin) / CLOCKS_PER_SEC);
	}
} TN;

double dp[MAXN][MAXN * MAXN / 2];
double dpsum[MAXN][MAXN * MAXN / 2];
double dpsum2[MAXN][MAXN * MAXN / 2];
double dp2[MAXN][MAXN * MAXN / 2];

int main() {
	// TN.init();

	dp[1][0] = 1;
	for (int i = 2; i <= 100; ++i) {
		int maxc = (i - 1) * i / 2;
		int pre_maxc = maxc - (i - 1);
		for (int k = 0; k < i; ++k) {
			for (int s = 0; s <= pre_maxc; s++) {
				dp[i][s + k] += dp[i - 1][s] / i;
			}
		}
		for (int s = 0; s <= maxc; s++) {
			dpsum[i][s + 1] = dpsum[i][s] + dp[i][s] * s;
		}
		for (int s = 0; s <= maxc; s++) {
			dpsum2[i][s + 1] = dpsum2[i][s] + dp[i][s];
		}
		// for (int s = 0; s <= maxc; s++) {
		// 	printf ("%lf%c", dp[i][s], s == maxc? '\n' : ' ');
		// }
		dp2[i][0] = dpsum[i][maxc + 1];
		for (int s = 1; s < maxc; s++) {
			// random left 1
			// for (int st = s; st <= maxc; st++) {
			// 	dp2[i][s] += min(dp2[i][s - 1], (double)st - s) * dp[i][st];
			// }
			int dif = min(maxc, (int)dp2[i][s - 1] + s);
			// [s, dif]
			if (dif >= s) dp2[i][s] += dpsum[i][dif + 1] - dpsum[i][s] - 
				s * (dpsum2[i][dif + 1] - dpsum2[i][s]);
			// [dif + 1, maxc]
			if (maxc > dif) dp2[i][s] += (dpsum2[i][maxc + 1] - dpsum2[i][dif + 1]) * dp2[i][s - 1];
		}

		// for (int s = 0; s <= maxc; s++) {
		// 	printf ("%lf%c", dp2[i][s], s == maxc? '\n' : ' ');
		// }
	}

	int a[MAXN], n;
	long long k;

	repcase {
		scanf ("%d%lld", &n, &k);
		int rev = 0;
		rep (i, n) {
			scanf ("%d", &a[i]);
			rep (j, i) {
				if (a[j] > a[i]) {
					rev += 1;
				}
			}
		}
		if (k >= rev) {
			puts ("0");
			continue ;
		}

		double res = rev - k;
		if (k > 0) {
			ckmin (res, dp2[n][k - 1]);
		}
		printf ("%.8lf\n", res);
	}

	// TN.output();
	return 0;
}