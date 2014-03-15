// Rain Dreamer MODEL
// Create @ 15:52 03-15 2014
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

const int maxn = 3000000 + 10;
const int mod = 1000000;

int M(int x, int y) { return (int64)x * y % mod; }

int n, a, b, c, d, prev, cur;
bool cnt[mod];

int main() {
	repcase {
		scanf ("%d%d%d%d%d", &n, &a, &b, &c, &d);
		clz (cnt);
		cnt[prev = d] += 1;
		repf (i, 1, n - 1) {
			cur = a * M(prev, prev) % mod + b * prev % mod + c;
			cur %= mod;
			cnt[cur] = !cnt[cur];
			prev = cur;
		}
		int64 ans = 0;
		bool flag = true;
		repd (i, mod - 1, 1) {
			if (cnt[i]) {
				ans += flag? i : -i;
				flag = !flag;
			}
		}
		cout << abs(ans) << endl;
	}
	return 0;
}

