// New Ryan
// Create @ 19:06 12-15 2013
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

const int MAXN = 1000000 + 10;

#define lowbit(x) ((x) & (-(x)))

struct BIT {
	int64 a[MAXN];
	int n;

	void init(int _n) {
		clz (a);
		n = _n;
		repf (i, 1, n) {
			int num;
			scanf ("%d", &num);
			add (i, num);
		}
	}

	void add(int x, int y) {
		for (; x <= n; x += lowbit(x)) {
			a[x] += y;
		}
	}

	int64 getsum(int x) {
		int64 res = 0;
		for (; x; x -= lowbit(x)) {
			res += a[x];
		}
		return res;
	}
};

BIT bit;
int n, q;

int main() {
	while (scanf ("%d%d", &n, &q) != EOF) {
		bit.init(n);
		rep (i, q) {
			int x, y;
			char op[2];
			scanf ("%s%d%d", op, &x, &y);

			if (op[0] == 'S') {
				cout << bit.getsum(y + 1) - bit.getsum(x) << endl;
			} else if (op[0] == 'G') {
				bit.add(x + 1, y);
			} else if (op[0] == 'T') {
				bit.add(x + 1, -y);
			}
		}
	}
    return 0;
}

