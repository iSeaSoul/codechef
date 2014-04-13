// Rain Dreamer MODEL
// Create @ 23:37 04-08 2014
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

const int MAXN = 100000 + 10;
const int MAXMOD = 100 + 2;
const int MOD = 1000000009;

int n, q, mod, val[MAXN], num_inv[MAXN];
int dp[MAXMOD][MAXMOD], sum[MAXMOD][MAXMOD];

int fix(int x) { return (x % mod + mod) % mod; }
int M(int x, int y) { return (int64)x * y % MOD; }

int read() {
    char ch;
    for (ch = getchar(); !(ch == '-' || (ch >= '0' && ch <= '9')); ch = getchar());
    int flag = 1;
    if (ch == '-') {
        flag = -1;
        ch = getchar();
    }
    int res = ch - '0';
    for (ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar()) {
        res = (res * 10) + (ch - '0');
    }
    return res * flag;
}

void update(int& x, int y) {
	x = (x + y) % MOD;
}

int mon(int a, int p) {
	int res = 1;
	while (p) {
		if (p & 1) res = M(res, a);
		a = M(a, a);
		p >>= 1;
	}
	return res;
}

int inv(int x) {
	return mon(x, MOD - 2);
}

int query() {
	vector<int> num(mod, 0);
	rep (i, n) {
		num[fix(val[i])]++;
	}
	clz (sum);
	rep (i, mod) {
		int c_com = 1LL;
		repf (k, 0, num[i]) {
			update (sum[i][k % mod], c_com);
			c_com = M(c_com, num[i] - k);
			c_com = M(c_com, num_inv[k + 1]);
		}
	}
	clz (dp);
	dp[0][0] = 1;
	rep (i, mod) rep (j, mod) {
		if (!dp[i][j]) continue;
		rep (k, mod) {
			update (dp[i + 1][fix(k * i + j)], M(dp[i][j], sum[i][k]));
		}
	}
	return dp[mod][0];
}

struct tm_node {
 
    clock_t begin;
 
    void init() {
    	begin = clock();
    }
 
    //bool valid() {
    	//return 1.0 * (clock() - begin) / CLOCKS_PER_SEC <= MAX_TM;
    //}

    void show() {
    	printf ("USED TIME = %lfs\n", 1.0 * (clock() - begin) / CLOCKS_PER_SEC);
    }
} TN;

int main() {
	//TN.init();
    //WT ("ANUCBC.in");
    //printf ("1\n100000 30\n");
    //rep (i, 100000) printf ("%d%c", rand(), i == 99999? '\n' : ' ');
    //rep (i, 30) printf ("%d%c", (i + 1) * 2 + 30, i == 29? '\n' : ' ');
    //return 0;
    
    repf (i, 1, MAXN - 1) num_inv[i] = inv(i);
	//TN.show();
    
	repcase {
		//scanf ("%d%d", &n, &q);
        n = read(); q = read();
		rep (i, n) {
			//scanf ("%d", &val[i]);
            val[i] = read();
		}
		rep (i, q) {
			//scanf ("%d", &mod);
            mod = read();
			printf ("%d\n", query());
		}
	}
	//TN.show();
	return 0;
}
