/*
 * Not the fish.
 * iSea @ 2014-10-26 13:40
 */

#include <bits/stdc++.h>

using namespace std;

// SELF TEMPLATE CODE BGEIN

#define sz(x) ((int)((x).size()))
#define out(x) printf(#x" %d\n", x)
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (cin >> t; t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

typedef long long int64;
typedef pair<int, int> pii;

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

const int MOD = (int)1e9 + 9;

long long n;
int k, dp[64][2][2], len;
vector<bool> bits;

int calc(int x, int t1, int t2) {
	if (x == len) {
		return t1 == 0 && t2 == 0;
	}
	int &ret = dp[x][t1][t2];
	if (ret != -1) {
		return ret;
	}
	ret = 0;

	for (int num = bits[x] ^ t2; num <= k; num += 2) {
		int now = (num + t2) >> 1;
		int pt2 = t1 + (now & 1);
		int pt1 = (now >> 1);
		if (pt2 == 2) {
			pt1 += 1; pt2 = 0;
		}
		ret += calc(x + 1, pt1, pt2);
		if (ret >= MOD) ret -= MOD;
	}
	// printf ("calc %d %d %d %d\n", x, t1, t2, ret);
	return ret;
}

int main() {
	ios::sync_with_stdio(false);

	repcase {
		cin >> k >> n;

		bits.clear();
		while (n) {
			bits.push_back(n & 1LL);
			n >>= 1;
		}
		len = sz(bits);

		memset (dp, -1, sizeof(dp));
		cout << calc(0, 0, 0) << endl;
	}
	return 0;
}