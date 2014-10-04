/*
 * Not the fish.
 * iSea @ 2014-10-04 15:47
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

const int MAXN = 100000 + 10;
const int OFFSET = 102;

char S[MAXN], W[MAXN];
int a, b, k;
int dp[2][2 * OFFSET];

void update(int& x, int y) {
	if (y > k) return ;
	if (x == -1 || x > y) {
		x = y;
	}
}

int dp_diff() {
	int len1 = strlen(S), len2 = strlen(W);
	int diff = len2 - len1;

	if (abs(diff) * a > k) {
		return -1;
	}

	memset (dp, -1, sizeof(dp));
	dp[1][OFFSET] = 0;

	int maxoff = (k / a);
	int flag = 0;

	rep (i, len1) {
		memset (dp[flag], -1, sizeof(dp[flag]));
		repf (j, OFFSET - maxoff, OFFSET + maxoff) {
			if (j + 1 <= OFFSET + maxoff && dp[!flag][j + 1] != -1) {
				update (dp[flag][j], dp[!flag][j + 1] + a);
			}
			if (j - 1 >= OFFSET - maxoff && dp[!flag][j - 1] != -1) {
				update (dp[flag][j], dp[!flag][j - 1] + a);
			}
			if (dp[!flag][j] != -1) {
				update (dp[flag][j], dp[!flag][j] + (S[i] == W[i + (j - OFFSET)]? 0 : b));
			}
			// printf ("%d %d -> %d\n", i, j - OFFSET, dp[flag][j]);
		}
		flag = !flag;
	}
	return dp[!flag][OFFSET + diff];
}

void init() {
	scanf ("%s%s", S, W);
	scanf ("%d%d%d", &a, &b, &k);
}

void solve() {
	if (a == 0) {
		// all delete
		puts ("0");
		return ;
	}

	printf ("%d\n", dp_diff());
}

int main() {
	repcase {
		init();
		solve();
	}
	return 0;
}