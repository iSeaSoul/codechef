// Rain Dreamer MODEL
// iSea @ 2014-08-02 00:22
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

const int mod = 1000000009;
const int MAXD = 8000000 + 10;
const int MAXN = 1000000 + 10;

int nag_fix(int x) {
	return x < 0? x + mod : x;
}

int mild_fix(int x) {
	return x >= mod? x - mod : x;
}

int pos[MAXD], a[MAXN], dif[MAXN], dpsum[MAXN], n;
int global_pos[MAXD];

int readInt() {
	char ch;
	for (ch = getchar(); !(ch == '-' || (ch >= '0' && ch <= '9')); ch = getchar());
	int sign = 1;
	if (ch == '-') {
		sign = -1;
		ch = getchar();
	}
	int res = ch - '0';
	for (ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar()) {
		res = res * 10 + (ch - '0');
	}
	return res * sign;
}

int main() {
	repcase {
		// scanf ("%d", &n);
		n = readInt();
		rep (i, n) {
			// scanf ("%d", &a[i]);
			a[i] = readInt();
		}
		rep (i, n - 1) {
			dif[i + 1] = a[i + 1] - a[i];
		}
		int maxdif = *max_element(dif + 1, dif + n);
		int mindif = *min_element(dif + 1, dif + n);
		// memset (pos, -1, sizeof(int) * (maxdif - mindif + 1));

		repf (i, 1, n - 1) {
			int dif_posid = dif[i] - mindif;
			if (global_pos[dif_posid] != Case) {
				dpsum[i] = mild_fix(dpsum[i - 1] + 1);
			} else {
				dpsum[i] = nag_fix(dpsum[i - 1] - dpsum[pos[dif_posid] - 1]);
			}
			dpsum[i] = mild_fix(dpsum[i] + dpsum[i - 1]);
			pos[dif_posid] = i;
			global_pos[dif_posid] = Case;
		}
		printf ("%d\n", dpsum[n - 1]);

		++Case;
	}
	return 0;
}