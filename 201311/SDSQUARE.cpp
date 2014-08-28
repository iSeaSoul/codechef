// New Ryan
// Create @ 15:23 11-03 2013
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

const int pnum[4] = {0, 1, 4, 9};
vector<int64> all_num;

bool is_sqr(int64 num) {
    int64 num_sqrt = (int64)(sqrt(num) + 1e-8);
    repf (off, -1, 1) {
        if ((num_sqrt + off) * (num_sqrt + off) == num) {
            return true;
        }
    }
    return false;
}

int main() {
    rep (mask, (1 << 20)) {
        int64 num = 0;
        int64 base = 1L;
        for (int i = 0; i < 20; i += 2, base *= 10) {
            num += pnum[((mask >> i) & 1) + (((mask >> (i + 1)) & 1) << 1)] * base;
        }
        if (is_sqr(num)) {
            all_num.push_back(num);
        }
    }
    all_num.push_back(10000000000LL);
    
    repcase {
        int64 L, R;
        cin >> L >> R;
        cout << upper_bound(all(all_num), R) - lower_bound(all(all_num), L) << endl;
    }
    return 0;
}

