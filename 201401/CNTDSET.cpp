// New Ryan
// Create @ 13:03 01-07 2014
// Comment - 

#include <cmath>
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
#define clz(x) memset (x, 0, sizeof(x))
#define read(x) freopen (x, "r", stdin)
#define wrte(x) freopen (x, "w", stdout)
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (scanf ("%d", &t); t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

typedef long long int64;
typedef pair<int, int> pii;
typedef pair<int64, int64> pll;
typedef pair<double, double> pdd;

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void ckmin(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void ckmax(T &a, const T b) { if (b > a) a = b; }

// Self Template Code END

const int mod = 1000000007;

int64 fix(int64 x, int m = mod) {
    return (x % m + m) % m;
}

int64 mon(int64 a, int64 p, int m = mod) {
    int res = 1;
    while (p > 0) {
        if (p & 1) res = res * a % m;
        a = a * a % m;
        p >>= 1;
    }
    return res;
}

const int MAXN = 1000 + 10;

int com[MAXN][MAXN];

int64 cal(int n, int p) {
    if (n == 0) {
        return 1;
    }
    
    int64 res = 0;
    repf (T, 0, p) {
        int64 pow = mon(n, T, mod - 1);
        int64 other = fix(mon(n + 1, p - T, mod - 1) - mon(n, p - T, mod - 1), mod - 1);
        int64 num = fix(com[p][T] * mon(2, fix(pow * other, mod - 1)));
        if (T & 1) {
            num = fix(-num);
        }
        
        res = fix(res + num);
    }
    return fix(res * mon(2, mon(n, p, mod - 1)));
}

int64 solve(int n, int p) {
    return fix(cal(n, p) - cal(n - 1, p));
}

int main() {
    repf (i, 1, 1000) {
        com[i][0] = com[i][i] = 1;
        repf (j, 1, i - 1) {
            com[i][j] = fix(com[i - 1][j - 1] + com[i - 1][j]);
        }
    }
    
    repcase {
        int n, p;
        scanf ("%d%d", &p, &n);
        printf ("%d\n", (int)solve(n, p));
    }
    return 0;
}

