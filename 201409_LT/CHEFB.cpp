// Rain Dreamer MODEL
// iSea @ 2014-09-28 13:59
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

const int MAXN = 1000000 + 10;
const int MAXF = 80000;

int prime[MAXF], cnt(0);
bool non_prime[MAXN];

void gen_prime() {
	for (int i = 2; i < MAXN; ++i) {
		if (!non_prime[i]) {
			prime[cnt++] = i;
			for (int j = i + i; j < MAXN; j += i) {
				non_prime[j] = true;
			}
		}
	}
}

int pfactor_maxt[MAXF];

void divide(int X) {
	for (int i = 0; prime[i] * prime[i] <= X && X != 1; ++i) {
		if (X % prime[i] == 0) {
			int ct = 0;
			while (X % prime[i] == 0) {
				ct += 1;
				X /= prime[i];
			}
			ckmax(pfactor_maxt[i], ct);
		}
	}
	if (X != 1) {
		ckmax(pfactor_maxt[lower_bound(prime, prime + cnt, X) - prime], 1);
	}
}

int main() {
	gen_prime();

	int n, ai;
	repcase {
		scanf ("%d", &n);
		memset (pfactor_maxt, 0, sizeof(pfactor_maxt));
		rep (i, n) {
			scanf ("%d", &ai);
			divide(ai);
		}
		int res = 0;
		rep (i, MAXF) {
			res += pfactor_maxt[i];
		}
		printf ("%d\n", res);
	}
	return 0;
}