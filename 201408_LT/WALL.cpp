// Rain Dreamer MODEL
// iSea @ 2014-08-31 14:40
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

const int MAXM = 524288 + 10;

int step[MAXM << 1], c[MAXM << 1];
int H, n, m, a, b, ind, d[MAXM];

int main() {
	repcase {
		scanf ("%d", &H);
		scanf ("%d%d", &n, &m);
		scanf ("%d%d%d", &a, &b, &ind);
		rep (i, m) {
			scanf ("%d", &d[i]);
		}
		n -= 1;

		int st, loop_len;
		memset (step, -1, sizeof(step));
		step[ind] = 0;
		c[0] = ind;
		for (st = 1; ; ++st) {
			ind = ((int64)a * ind + b) % m;
			c[st] = ind;
			if (step[ind] != -1) {
				loop_len = st - step[ind];
				break;
			} else {
				step[ind] = st;
			}
		}
		if (n < step[ind]) {
			int64 ret = 0;
			rep (i, n) {
				ret += (int64)d[c[i]] * H;
			}
			cout << ret / 2 << '.' << (ret & 1 == 0? '0' : '5')  << endl;
			continue ;
		}
		int R = (n - step[ind]) / loop_len;
		int left = (n - step[ind]) % loop_len;
		int64 ret = 0;
		repf (i, step[ind], step[ind] + loop_len - 1) {
			ret += (int64)d[c[i]] * H;
		}
		ret *= R;
		repf (i, 0, step[ind] + left - 1) {
			ret += (int64)d[c[i]] * H;
		}
		cout << ret / 2 << '.' << (ret & 1 == 0? '0' : '5') << endl;
	}
	return 0;
}