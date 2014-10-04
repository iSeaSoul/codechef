/*
 * Not the fish.
 * iSea @ 2014-10-04 16:14
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

set<pii> allp;
int n;

int solve() {
	n = sz(allp);
	if (n <= 1) {
		return 4 - n;
	}

	int ret = 2;
	for (const pii& p : allp) {
		set<pii> vecs;
		for (const pii& pj : allp) {
			if (pj != p) {
				vecs.insert (pii(pj.first - p.first, pj.second - p.second));
			}
		}
		for (const pii& vec : vecs) {
			pii turn_left = pii(-vec.second, vec.first);
			if (vecs.find(turn_left) != vecs.end()) {
				ckmin (ret, 1);
				pii fourth_p = pii(vec.first - vec.second, vec.first + vec.second);
				if (vecs.find(fourth_p) != vecs.end()) {
					return 0;
				}
			}
		}
	}
	return ret;
}

int main() {
	while (scanf ("%d", &n) != EOF) {
		allp.clear();
		rep (i, n) {
			int x, y;
			scanf ("%d%d", &x, &y);
			allp.insert (pii(x, y));
		}

		printf ("%d\n", solve());
	}
	return 0;
}