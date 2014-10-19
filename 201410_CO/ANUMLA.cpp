/*
 * Not the fish.
 * iSea @ 2014-10-20 01:49
 */

#include <bits/stdc++.h>

using namespace std;

// SELF TEMPLATE CODE BGEIN

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

template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

multiset<int> s;

int n, ans[16];

inline void E(int x) { s.erase(s.find(x)); }

int main() {
	ios::sync_with_stdio(false);

	repcase {
		scanf ("%d", &n);
		int tn = (1 << n);

		s.clear();
		rep (i, tn) {
			int foo;
			scanf ("%d", &foo);
			s.insert (foo);
		}
		E(0);

		if (n == 1) {
			printf ("%d\n", *s.begin());
			continue ;
		}

		int ct = 2;
		ans[0] = *s.begin(); E(ans[0]);
		ans[1] = *s.begin(); E(ans[1]);
		E(ans[0] + ans[1]);

		repf (i, ct, n - 1) {
			ans[i] = *s.begin();
			// E(ans[i]);
			rep (st, (1 << i)) {
				int sum = ans[i];
				rep (j, i) {
					if ((st >> j) & 1) {
						sum += ans[j];
					}
				}
				E(sum);
			}
		}

		rep (i, n) {
			printf ("%d%c", ans[i], " \n"[i == n - 1]);
		}
	}
	return 0;
}