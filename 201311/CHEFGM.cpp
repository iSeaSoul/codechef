// New Ryan
// Create @ 12:12 11-03 2013
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

const char *ans_str[3] = {"EVEN", "DON\'T PLAY", "ODD"};

int pow_cnt[50], num[50];
int k, n;

int judge() {
    int max_non_zero_bit_flag = 0;
    repd (i, 45, 1) {
        int flag = (pow_cnt[i] >= 0? 1 : -1);
        pow_cnt[i - 1] += flag * (abs(pow_cnt[i]) / 2);
        pow_cnt[i] = flag * (abs(pow_cnt[i]) % 2);
        
        if (pow_cnt[i] != 0) {
            max_non_zero_bit_flag = pow_cnt[i];
        }
    }
            
    if (pow_cnt[0] == 0) {
        return max_non_zero_bit_flag;
    }
    return pow_cnt[0] >= 0? 1 : -1;
}

int main() {
    repcase {
        scanf ("%d", &k);
        clz (pow_cnt);
        
        rep (k_group, k) {
            scanf ("%d", &n);
            rep (i, n) scanf ("%d", num + i); 
            sort (num, num + n);
            
            int id = 0;
            
            while (id < n && (num[id] & 1) == (num[0] & 1)) {
                pow_cnt[0] += ((num[id] & 1) == 1? 1 : -1);
                id += 1;
            }
            int pow_id = 1;
            for (; id < n; ++id, ++pow_id) {
                pow_cnt[pow_id] += ((num[id] & 1) == 1? 1 : -1);
            }
        }
        
        puts (ans_str[judge() + 1]);
    }
    return 0;
}

