// New Ryan
// Create @ 18:41 12-15 2013
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

const int MAXN = 100000 + 10;

int n, k, num[MAXN];
int64 dp[MAXN], maxdp[MAXN], revdp[MAXN];

int main() {
	repcase {
		scanf ("%d%d", &n, &k);
		rep (i, n) {
			scanf ("%d", num + i);
			dp[i] = max(0LL, i > 0? dp[i - 1] : 0LL) + num[i];
			if (i > 0) {
				maxdp[i] = max(maxdp[i - 1], dp[i]);
			} else {
				maxdp[i] = dp[i];
			}
		}
		int64 res = -(int64)(1e15);

		repd (i, n - 1, 0) {
			revdp[i] = max(0LL, i == n - 1? 0LL : revdp[i + 1]) + num[i];
			if (i - k - 1 >= 0) {
				ckmax (res, revdp[i] + maxdp[i - k - 1]);
			}
		}
		printf ("%lld\n", res);
	}
    return 0;
}

