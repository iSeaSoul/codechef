// New Ryan
// Create @ 16:34 12-15 2013
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

int same[2][MAXLEN][MAXLEN][MAXLEN];
int sameX[2][MAXLEN][MAXLEN][MAXLEN];
int sameY[2][MAXLEN][MAXLEN][MAXLEN];
int sameZ[2][MAXLEN][MAXLEN][MAXLEN];
int sameXY[2][MAXLEN][MAXLEN][MAXLEN];
int sameYZ[2][MAXLEN][MAXLEN][MAXLEN];
int sameXZ[2][MAXLEN][MAXLEN][MAXLEN];

//#define GEN

int main() {
	#ifdef GEN
	wrte ("CUBE.in");

	printf ("%d\n", 10);
	rep (i, 10) {
		int p = 40;
		printf ("%d 100\n", p);
		rep (i, p * p * p) {
			putchar ('a' + (rand() % 2));
		}
		puts ("");
		rep (i, p * p * p) {
			putchar ('a' + (rand() % 2));
		}
		puts ("");
	}

	return 0;
	#endif

	repcase {
		int n, percent;

		scanf ("%d%d", &n, &percent);
		scanf ("%s%s", sa, sb);
		//gets(sa);
		//gets(sb);

		/*int len = n * n * n;
		char buf[102];
		gets (buf);
		rep (i, len) sa[i] = getchar ();
		gets (buf);
		rep (i, len) sb[i] = getchar ();
		sa[len] = sb[len] = 0;*/

		int anslen = -1, ansnum = 0;

		rep (i, n) rep (j, n) rep (k, n) {
			sr[i][j][k] = same[1][i][j][k] = (get_cube_char(sa, n, i, j, k) == get_cube_char(sb, n, i, j, k)? 1 : 0);
			sameX[1][i][j][k] = sameY[1][i][j][k] = sameZ[1][i][j][k] = same[1][i][j][k];
			sameXY[1][i][j][k] = sameYZ[1][i][j][k] = sameXZ[1][i][j][k]= same[1][i][j][k];

			if (sr[i][j][k]) {
				anslen = 1; ansnum += 1;
			}
		}

		repf (all_clen, 2, n) {
			int totnum = percent * all_clen * all_clen * all_clen;
			rep (i, n) rep (j, n) rep (k, n) {
				int clen = (all_clen & 1);
				sameXY[clen][i][j][k] = sameYZ[clen][i][j][k] = sameXZ[clen][i][j][k] = 0;

				if (k + all_clen <= n) {
					sameXY[clen][i][j][k] += sameXY[!clen][i][j][k + 1] + sr[i][j][k];
				}
				if (j + all_clen <= n) {
					sameXZ[clen][i][j][k] += sameXZ[!clen][i][j + 1][k] + sr[i][j][k];
				}
				if (i + all_clen <= n) {
					sameYZ[clen][i][j][k] += sameYZ[!clen][i + 1][j][k] + sr[i][j][k];
				}

				if (k + all_clen <= n && j + all_clen <= n) {
					int res = 0;
					res = sameX[!clen][i][j + 1][k + 1];
					res += sameXY[clen][i][j][k];
					res += sameXZ[!clen][i][j + 1][k];
					sameX[clen][i][j][k] = res;
				}
				if (k + all_clen <= n && i + all_clen <= n) {
					int res = 0;
					res = sameY[!clen][i + 1][j][k + 1];
					res += sameXY[clen][i][j][k];
					res += sameYZ[!clen][i + 1][j][k];
					sameY[clen][i][j][k] = res;
				}
				if (i + all_clen <= n && j + all_clen <= n) {
					int res = 0;
					res = sameZ[!clen][i + 1][j + 1][k];
					res += sameXZ[clen][i][j][k];
					res += sameYZ[!clen][i + 1][j][k];
					sameZ[clen][i][j][k] = res;
				}
				if (i + all_clen <= n && j + all_clen <= n && k + all_clen <= n) {
					int res = 0; 
					res = same[!clen][i + 1][j + 1][k + 1];
					res += sameX[clen][i][j][k];
					res += sameY[clen][i][j][k];
					res += sameZ[clen][i][j][k];

					res -= sameXY[!clen][i][j][k + 1];
					res -= sameXZ[!clen][i][j + 1][k];
					res -= sameYZ[!clen][i + 1][j][k];
					res -= 2 * sr[i][j][k];

					same[clen][i][j][k] = res;

					if (same[clen][i][j][k] * 100 >= totnum) {
						//printf ("here %d %d %d %d\n", i, j, k, all_clen);
						if (anslen == all_clen) {
							ansnum += 1;
						} else {
							anslen = all_clen;
							ansnum = 1;
						}
					}
				}
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