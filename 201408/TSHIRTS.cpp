// Rain Dreamer MODEL
// iSea @ 2014-08-01 18:30
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

const int MAXN = (1 << 10) + 10;
const int mod = 1000000007;

int st[MAXN], dp[110][MAXN], n;
char buf[65533];

void update(int& x, int y) {
	x = (x + y) % mod;
}

int main() {
	repcase {
		scanf ("%d", &n);
		gets (buf);
		memset (st, 0, sizeof(st));
		memset (dp, 0, sizeof(dp));
		rep (i, n) {
			gets (buf);
			string str(buf);
			stringstream ss(str);

			int id;
			while (ss >> id) {
				st[id - 1] |= (1 << i);
			}
		}
		int maxmask = (1 << n);
		dp[0][0] = 1;
		rep (i, 100) {
			rep (j, maxmask) {
				if (!dp[i][j]) continue;
				update (dp[i + 1][j], dp[i][j]);
				rep (k, n) {
					if (((j >> k) & 1) == 0 && ((st[i] >> k) & 1) == 1) {
						update(dp[i + 1][j | (1 << k)], dp[i][j]);
					}
				}
			}
		}
		printf ("%d\n", dp[100][maxmask - 1]);
	}
	return 0;
}