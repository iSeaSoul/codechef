/*
 * Not the fish.
 * iSea @ 2014-10-20 00:55
 */

#include <bits/stdc++.h>

using namespace std;

// SELF TEMPLATE CODE BGEIN

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

template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

const int LIM = (int)1e8;

int fib[50];
vector<int> allg;
set<int> good;
map<int, int> fibpos;

inline void output_dot(int num) {
	rep (i, num) putchar ('.');
}

void divide(int x) {
	// printf ("divide %d\n", x);
	if (fibpos.find(x) != fibpos.end()) {
		output_dot(fibpos[x]);
		return ;
	}
	repf (i, 3, 39) {
		if (x % fib[i] == 0 && good.find(x / fib[i]) != good.end()) {
			output_dot(fibpos[fib[i]]);
			putchar ('#');
			divide(x / fib[i]);
			return ;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);

	fibpos[1] = 1;
	fib[1] = fib[2] = 1;
	for (int i = 3; fib[i - 1] <= LIM; ++i) {
		fib[i] = fib[i - 1] + fib[i - 2];
		// cout << i << ' ' << fib[i] << endl;
		fibpos[fib[i]] = i;
	}

	queue<int> goods;
	for (int i = 3; fib[i] <= LIM; ++i) {
		goods.push(fib[i]);
		good.insert(fib[i]);
	}

	allg.push_back(1);
	while (!goods.empty()) {
		int cur = goods.front(); goods.pop();
		allg.push_back(cur);
		for (int i = 3; fib[i] <= LIM; ++i) {
			if (LIM >= (long long)cur * fib[i]) {
				int next = fib[i] * cur;
				// printf ("next %d %d %d\n", fib[i], cur, next);
				if (next <= LIM && good.insert(next).second) {
					goods.push(next);
				}
			}
		}
	}

	sort (allg.begin(), allg.end());

	repcase {
		int L, R, N;
		scanf ("%d%d%d", &L, &R, &N);

		if (L == 0) {
			if (N == 1) {
				printf ("0 .##.\n");
				continue ;
			}
			N -= 1;
			// L += 1;
		}

		int lid = lower_bound(allg.begin(), allg.end(), L) - allg.begin();
		int rid = upper_bound(allg.begin(), allg.end(), R) - allg.begin();

		if (rid - lid < N) {
			puts ("-1");
			continue ;
		}

		int ret = allg[lid + N - 1];
		printf ("%d ", ret);
		divide(ret);
		puts("");
	}
	return 0;
}