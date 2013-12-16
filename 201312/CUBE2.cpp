// New Ryan
// Create @ 12:18 12-16 2013
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

char get_cube_char(char *s, int len, int i, int j, int k) {
	return s[len * len * i + len * j + k];
}

const int MAXLEN = 40 + 2;

char sa[MAXLEN * MAXLEN * MAXLEN];
char sb[MAXLEN * MAXLEN * MAXLEN];

int sr[MAXLEN][MAXLEN][MAXLEN];
int sum[MAXLEN][MAXLEN][MAXLEN];

int get_sum(int lx, int ly, int lz, int rx, int ry, int rz) {
	return sum[rx][ry][rz] - sum[lx - 1][ry][rz] - sum[rx][ly - 1][rz] - sum[rx][ry][lz - 1]
		+ sum[lx - 1][ly - 1][rz] + sum[lx - 1][ry][lz - 1] + sum[rx][ly - 1][lz - 1]
		- sum[lx - 1][ly - 1][lz - 1];
}

int main() {
	read ("cube.in");

	repcase {
		int n, percent;

		scanf ("%d%d", &n, &percent);
		scanf ("%s%s", sa, sb);

		/*int len = n * n * n;
		char buf[102];
		gets (buf);
		rep (i, len) sa[i] = getchar ();
		gets (buf);
		rep (i, len) sb[i] = getchar ();
		sa[len] = sb[len] = 0;*/

		clz (sum);

		rep (i, n) rep (j, n) rep (k, n) {
			sr[i + 1][j + 1][k + 1] = (get_cube_char(sa, n, i, j, k) == get_cube_char(sb, n, i, j, k)? 1 : 0);
		}

		repf (i, 1, n) repf (j, 1, n) repf (k, 1, n) {
			sum[i][j][k] = sr[i][j][k] + sum[i - 1][j][k] + sum[i][j - 1][k] + sum[i][j][k - 1] -
				sum[i - 1][j - 1][k] - sum[i - 1][j][k - 1] - sum[i][j - 1][k - 1] + sum[i - 1][j - 1][k - 1];
		}

		int anslen = -1, ansnum = 0;
		repd (clen, n, 1) {
			int totnum = percent * clen * clen * clen;
			bool has_sol = false;
			repf (i, 1, n - clen + 1) repf (j, 1, n - clen + 1) repf (k, 1, n - clen + 1) {
				int curnum = get_sum(i, j, k, i + clen - 1, j + clen - 1, k + clen - 1);
				//printf ("%d %d %d %d = %d\n", i, j, k, clen, curnum);
				if (curnum * 100 >= totnum) {
					anslen = clen;
					ansnum += 1;
					has_sol = true;
				}
			}
			if (has_sol) {
				break ;
			}
		}
		if (anslen == -1) {
			puts ("-1");
		} else {
			printf ("%d %d\n", anslen, ansnum);
		}
	}
    return 0;
}

