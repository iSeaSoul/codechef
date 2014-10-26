/*
 * Not the fish.
 * iSea @ 2014-10-26 14:46
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

int main() {
	ios::sync_with_stdio(false);

	repcase {
		int n, st = 0;
		string s;
		cin >> n;
		cin >> s;
		rep (i, n) {
			if (s[i] == 'Y') st |= 1;
			else if (s[i] == 'N') st |= 2;
			else if (s[i] == 'I') st |= 4;
		}
		if (st & 1) puts ("NOT INDIAN");
		else if (st & 4) puts ("INDIAN");
		else puts ("NOT SURE");
	}
	return 0;
}