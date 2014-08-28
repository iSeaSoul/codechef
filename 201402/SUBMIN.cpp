// Rain Dreamer MODEL
// iSea @ 2014-08-29 00:28
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

const int MAXN = 50 + 5;

int st[MAXN], top;
int a[MAXN], lf[MAXN];
map<int, int> ans;

int main() {
	int n, m, q;
	while (scanf ("%d", &n) != EOF) {
		top = -1;
		rep (i, n) {
			scanf ("%d", &a[i]);
			while (top != -1 && a[st[top]] >= a[i]) top -= 1;
			if (top == -1) {
				lf[i] = i + 1;
			} else {
				lf[i] = i - st[top];
			}
			st[++top] = i;
		}
		// memset (ans, 0, sizeof(ans));
		ans.clear();
		top = -1;
		repd (i, n - 1, 0) {
			while (top != -1 && a[st[top]] > a[i]) top -= 1;
			int rt = (top == -1? n - i : st[top] - i);
			ans[a[i]] += lf[i] * rt;
			st[++top] = i;
		}
		for (scanf ("%d", &m); m; --m) {
			scanf ("%d", &q);
			printf ("%d\n", ans[q]);
		}
	}
	return 0;
}

/*
5
3 3 3 3 3
1
3
*/