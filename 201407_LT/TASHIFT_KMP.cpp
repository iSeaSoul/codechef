// Rain Dreamer MODEL
// iSea @ 2014-07-27 15:30
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

const int maxn = 2000000 + 10;

char s1[maxn], s2[maxn];
int n, next[maxn];

void get_next(char *s, int n) {
	next[0] = -1;
	for (int i = 0, j = -1; i < n; ) {
		while (j != -1 && s[i] != s[j]) {
			j = next[j];
		}
		next[++i] = ++j;
	}
}

int main() {
	// freopen ("TASHIFT.in", "r", stdin);
	while (scanf ("%d", &n) != EOF) {
		scanf ("%s%s", s1, s2);
		rep (i, n) {
			s2[i + n] = s2[i];
		}
		get_next(s1, n);

		int maxc = 0, minp = 0;
		for (int i = 0, j = 0; i < 2 * n; ++i) {
			while (j != -1 && s2[i] != s1[j]) {
				j = next[j];
			}
			int cur_len = ++j;
			if (cur_len > maxc) {
				maxc = cur_len;
				minp = i - cur_len + 1;
			} else if (cur_len == maxc) {
				ckmin (minp, i - cur_len + 1);
			}
		}
		printf ("%d\n", minp);
	}
	return 0;
}