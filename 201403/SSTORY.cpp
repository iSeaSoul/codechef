// Rain Dreamer MODEL
// Create @ 22:22 03-09 2014
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

const int maxn = 500000 + 10;

struct suffix_array {

    int wa[maxn], wb[maxn], wv[maxn], wc[maxn];
    int sa[maxn], sr[maxn], height[maxn];
    
    // sa : [1, n]   sa[i] - the suffix from sa[i] rank i
    // sr : [0, n)   sr[i] - the suffix from i rank sc[i]
    // height : [2, n]  lcp length of sa[i - 1] and sa[i]

    int cmp(int *r, int a, int b, int l) {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }

    // m indicate the size of characters
    // adjust if it's a number string
    
    void da(char *r, int n, int m = 28) {
        int i, j, p, *x = wa, *y = wb, *t;
        for (i = 0; i < m; i++) wc[i] = 0;
        for (i = 0; i < n; i++) wc[x[i] = r[i]]++;
        for (i = 1; i < m; i++) wc[i] += wc[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--wc[x[i]]] = i;
        for (j = 1, p = 1; p < n; j *= 2, m = p) {
            for (p = 0, i = n - j; i < n; i++) y[p++]=i;
            for (i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i] - j;
            for (i = 0; i < n; i++) wv[i] = x[y[i]];
            for (i = 0; i < m; i++) wc[i] = 0;
            for (i = 0; i < n; i++) wc[wv[i]] ++;
            for (i = 1; i < m; i++) wc[i] += wc[i-1];
            for (i = n - 1; i >= 0; i--) sa[--wc[wv[i]]] = y[i];
            for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++){
                x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
            }
        }
    }

    void cal_height(char *r, int n) {
        int i, j, k = 0;
        for (i = 1; i <= n; i++) sr[sa[i]] = i;
        for (i = 0; i < n; height[sr[i++]] = k) {
            for (k ? k-- : 0, j = sa[sr[i] - 1]; r[i + k] == r[j + k]; k++);
        }
    }
    
    // complexity O(n * logn)
    void process(char *r, int n) {
        da(r, n + 1);
        cal_height(r, n);
    }
};

suffix_array sa;
char buf[maxn], str[maxn];

int belong(int x, int len) {
	if (x == len) return 0;
	return x < len? -1 : 1;
}

int main() {
	while (scanf ("%s", buf) != EOF) {
		int len1 = strlen(buf);
		rep (i, len1) {
			str[i] = buf[i] - 'a' + 2;
		}
		str[len1] = 1;
		scanf ("%s", buf);
		int len2 = strlen(buf);
		rep (i, len2) {
			str[len1 + 1 + i] = buf[i] - 'a' + 2;
		}

		sa.process (str, len1 + len2 + 1);
		int ans = 0, mins;
		repf (i, 2, len1 + len2 + 1) {
			if (belong(sa.sa[i], len1) != belong(sa.sa[i - 1], len1)) {
				if (sa.height[i] > ans) {
					ans = sa.height[i];
					mins = (belong(sa.sa[i], len1) == 1? sa.sa[i] : sa.sa[i - 1]);
				} else if (sa.height[i] == ans) {
					ckmin (mins, belong(sa.sa[i], len1) == 1? sa.sa[i] : sa.sa[i - 1]);
				}
			}
		}
		if (ans != 0) {
			rep (i, ans) putchar ('a' + str[mins + i] - 2);
			puts ("");
		}
		printf ("%d\n", ans);
	}
    return 0;
}

