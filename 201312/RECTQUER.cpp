// New Ryan
// Create @ 18:53 12-15 2013
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

const int MAXN = 300 + 10;

int n, q, num[MAXN][MAXN];
int cnt[12][MAXN][MAXN];

void calc(int x) {
	repf (i, 1, n) repf (j, 1, n) {
		cnt[x][i][j] = (num[i - 1][j - 1] == x? 1 : 0);
		cnt[x][i][j] += cnt[x][i - 1][j] + cnt[x][i][j - 1];
		cnt[x][i][j] -= cnt[x][i - 1][j - 1];
	}
}

int main() {
	while (scanf ("%d", &n) != EOF) {
		rep (i, n) rep (j, n) {
			scanf ("%d", &num[i][j]);
			num[i][j] -= 1;
		}
		clz (cnt);
		rep (k, 10) {
			calc (k);
		}
		scanf ("%d", &q);
		while (q--) {
			int x1, y1, x2, y2, res = 0;
			scanf ("%d%d%d%d", &x1, &y1, &x2, &y2);
			rep (k, 10) {
				int num = cnt[k][x2][y2] + cnt[k][x1 - 1][y1 - 1];
				num -= cnt[k][x2][y1 - 1] + cnt[k][x1 - 1][y2];
				if (num) {
					res += 1;
				}
			}
			printf ("%d\n", res);
		}
	}
    return 0;
}

