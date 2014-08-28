// New Ryan
// Create @ 13:52 11-03 2013
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

const int maxn = 1000000 + 10;

bool f[maxn], flag[maxn];
int prime[78888], cnt = 0;

void gen_prime() {
    for (int i = 2; i < maxn; ++i) {
        if (!f[i]) {
            prime[cnt++] = i;
            for (int j = (i << 1); j < maxn; j += i) {
                f[j] = true;
            }
        }
    }
}

int main() {
    gen_prime();
    
    repcase { 
        int64 L, R;
        cin >> L >> R;
        if (L == 1) ++L;
        int64 len = R - L + 1;
        memset (flag, 0, sizeof(flag));
        
        int ans = 0;
        rep (i, cnt) {
            if (prime[i] > R) break;
            int64 minc = ((L + prime[i] - 1) / prime[i]) * prime[i];
            if (minc == prime[i]) {
                minc <<= 1;
            }
            for (int j = minc - L; j < len; j += prime[i]) {
                if (j >= 0) {
                    flag[j] = true;
                }
            }
            int64 sqr = (int64)prime[i] * prime[i];
            int pow_cnt = 3;
            while (sqr <= R) {
                if (!f[pow_cnt] && sqr >= L) {
                    ++ans;
                }
                if (R / prime[i] < sqr) {
                    break;
                }
                sqr *= prime[i];
                pow_cnt++;
            }
        }
        rep (i, len) {
            if (!flag[i]) {
                ++ans;
            }
        }
        
        cout << ans << endl;
    }
    return 0;
}

