// New Ryan
// Create @ 14:39 11-03 2013
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

int fast_mod(int64 a, int64 k, int m) {
    int64 res = 1LL;
    while (k) {
        if (k & 1LL) res = res * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return res;
}

int main() {
    repcase {
        int64 m;
        cin >> m;
        int64 pow_num = 0;
        int64 bit_num = 1L;
        while (m) {
            if (m & 1LL) pow_num = (pow_num + bit_num) % (mod - 1);
            bit_num = bit_num * 10LL % (mod - 1);
            m >>= 1;
        }
        cout << fast_mod(2LL, pow_num << 1, mod) << endl;
    }
    return 0;
}

