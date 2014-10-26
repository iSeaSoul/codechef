/*
 * Not the fish.
 * iSea @ 2014-10-26 14:33
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

map<pair<int, int>, pair<int, int> > objs;

int main() {
	ios::sync_with_stdio(false);

	int n, m;
	while (cin >> n >> m) {
		rep (i, n) {
			int x, y, val, pri;
			cin >> x >> y >> val >> pri;
			auto obj = make_pair(x, y);
			if (objs.count(obj) == 0 || objs[obj].second <= pri) {
				objs[obj] = make_pair(val, pri);
			}
		}
		rep (i, m) {
			int x, y;
			cin >> x >> y;
			cout << objs[make_pair(x, y)].first << endl;
		}
	}
	return 0;
}