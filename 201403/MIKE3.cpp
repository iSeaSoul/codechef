// Rain Dreamer MODEL
// Create @ 15:00 03-15 2014
// Comment - 

#include <cmath>
#include <ctime>
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
#define RD(x) freopen (x, "r", stdin)
#define WT(x) freopen (x, "w", stdout)
#define clz(x) memset (x, 0, sizeof(x))
#define cln(x) memset (x, -1, sizeof(x))
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

const int MAXN = 20 + 5;
const int maxn = 20000 + 10;

int Kcnt[MAXN], offer[MAXN][maxn], n, m;
bool g[MAXN][MAXN];

bool conflict(int x, int y) {
	int cntx = 0, cnty = 0;
	while (cntx < Kcnt[x]) {
		for (; cnty < Kcnt[y] && offer[y][cnty] < offer[x][cntx]; ++cnty) ;
		if (cnty >= Kcnt[y]) {
			break ;
		}
		if (offer[y][cnty] == offer[x][cntx]) {
			return true;
		}
		++cntx;
	}
	return false;
}

bool valid(int state) {
	rep (i, m) if ((state >> i) & 1) {
		rep (j, i) if ((state >> j) & 1) {
			if (g[i][j]) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	while (scanf ("%d%d", &n, &m) != EOF) {
		rep (i, m) {
			scanf ("%d", &Kcnt[i]);
			rep (j, Kcnt[i]) {
				scanf ("%d", &offer[i][j]);
			}
			rep (j, i) {
				g[i][j] = conflict(i, j);
			}
		}
		int ans = 0;
		rep (st, (1 << m)) {
			if (valid(st)) {
				ckmax (ans, count_bit(st));
			}
		}
		printf ("%d\n", ans);
	}
    return 0;
}

