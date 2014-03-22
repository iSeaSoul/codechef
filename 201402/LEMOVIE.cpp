// New Ryan
// Create @ 19:08 02-17 2014
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

const int MAXN = 200 + 10;
const int mod = 1000000007;

int fac[MAXN];

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

int rev(int x) {
	return mon(x, mod - 2);
}

int A(int x, int y) { return M(fac[x + y - 1], rev(fac[x - 1])); } // x * (x + 1) * ... * (x + y - 1)

int p[MAXN], n, k;
int cnt[MAXN], sum[MAXN], dp[MAXN][MAXN];

void update(int& x, int y) {
	x = (x + y) % mod;
}

void prepare() {
	fac[0] = 1;
	repf (i, 1, MAXN - 1) {
		fac[i] = M(fac[i - 1], i);
	}
}

void input() {
	scanf ("%d%d", &n, &k);
	rep (i, n) {
		scanf ("%d", p + i);
	}
}

void solve() {
	// count
	clz (cnt);
	rep (i, n) {
		cnt[p[i]] += 1;
	}

	// partial sum
	clz (sum);
	int maxp = *max_element(p, p + n);
	sum[maxp] = 0;
	repd (i, maxp, 1) {
		sum[i] = sum[i + 1] + cnt[i];
	}

	// dp
	clz (dp);
	dp[maxp + 1][0] = 1;
	int last_idx = maxp + 1;
	repd (i, maxp, 1) {
		if (!cnt[i]) continue ;
		int prev_num = sum[i + 1];
		repf (j, 0, maxp - i) {
			if (!dp[last_idx][j]) continue ;
			if (j == 0) {
				update (dp[i][j + 1], M(dp[last_idx][j], fac[cnt[i]]));
			} else {
				// before the prev max
				int ways = M(cnt[i], A(prev_num + 1, cnt[i] - 1));
				update (dp[i][j + 1], M(dp[last_idx][j], ways));
				// after the prev max
				ways = A(prev_num, cnt[i]);
				update (dp[i][j], M(dp[last_idx][j], ways));
			}
		}
		last_idx = i;
	}
    
	// count answer
	int res = 0;
	repf (i, 1, k) {
		update (res, dp[last_idx][i]);
	}
	printf ("%d\n", res);
}

int main() {
	prepare();

	repcase {
		input(); solve();
	}
	return 0;
}

