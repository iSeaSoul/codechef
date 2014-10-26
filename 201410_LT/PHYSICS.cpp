/*
 * Not the fish.
 * iSea @ 2014-10-26 14:13
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

int N, F;
unordered_map<int, int> num;

int main() {
	ios::sync_with_stdio(false);

	repcase {
		cin >> N >> F;
		num.clear();
		int maxh = 0;
		rep (i, N) {
			int bar;
			cin >> bar;
			num[bar] += 1;
			to_max(maxh, bar);
		}
		int ret = 0;
		for (const auto& p : num) {
			ret += (p.second - 1) * p.second / 2;
			int h = p.first;
			while ((long long)h * F <= maxh) {
				h *= F;
				if (num.find(h) != num.end()) {
					ret += p.second * num[h];
				}
			}
		}
		cout << ret << endl;
	}
	return 0;
}