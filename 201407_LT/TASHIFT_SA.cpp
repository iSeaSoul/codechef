// Rain Dreamer MODEL
// iSea @ 2014-07-27 13:46
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

const int maxn = 3000000 + 10;

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

char s1[maxn / 3], s2[maxn / 3], s[maxn];
int n, len;
suffix_array sa;

int main() {
	while (scanf ("%d", &n) != EOF) {
		scanf ("%s%s", s1, s2);
		rep (i, n) {
			s[i] = s1[i] - 'a' + 2;
		}
		s[n] = 1;
		rep (i, n) {
			s[n + 1 + i] = s[2 * n + 1 + i] = s2[i] - 'a' + 2;
		}
		len = 3 * n + 1;
		sa.process (s, len);

		int maxc = 0, minp = 0;
		int begin_idx = sa.sr[0];
		int nowc = sa.height[begin_idx + 1];
		repf (i, begin_idx + 1, len) {
			ckmin (nowc, sa.height[i]);
			if (sa.sa[i] > n && sa.sa[i] <= 2 * n) {
				if (nowc > maxc) {
					maxc = nowc;
					minp = sa.sa[i] - n - 1;
				} else if (nowc == maxc) {
					ckmin (minp, sa.sa[i] - n - 1);
				}
			}
		}
		nowc = sa.height[begin_idx];
		repd (i, begin_idx, 2) {
			ckmin (nowc, sa.height[i]);
			if (sa.sa[i] > n && sa.sa[i] <= 2 * n) {
				if (nowc > maxc) {
					maxc = nowc;
					minp = sa.sa[i] - n - 1;
				} else if (nowc == maxc) {
					ckmin (minp, sa.sa[i] - n - 1);
				}
			}
		}
		printf ("%d\n", minp);
	}
	return 0;
}