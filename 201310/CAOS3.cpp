// New Ryan
// Create @ 14:39 10-07 2013
// Comment - SG func

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

const int maxn = 22;
const int step_dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

char mp[maxn][maxn];
vector<int> CPC[maxn];
int sg[maxn][maxn][maxn][maxn], n, m;

bool is_empty(int x, int y) {
    return x >= 0 && x < n & y >= 0 && y < m && mp[x][y] == '^';
}

bool judge_CPC(int x, int y) {
    if (mp[x][y] == '#') {
        return false;
    }
    rep (dir, 4) {
        repf (step, 1, 2) {
            if (!is_empty(x + step_dir[dir][0] * step, y + step_dir[dir][1] * step)) {
                return false;
            }
        }
    }
    return true;
}

int solve(int lx, int ly, int rx, int ry) {
    if (sg[lx][ly][rx][ry] != -1) {
        return sg[lx][ly][rx][ry];
    }
    set<int> all_suc;
    repf (i, lx, rx) {
        repeach (item, CPC[i]) {
            int j = *item;
            if (j < ly || j > ry) continue;
            int LU = solve(lx, ly, i - 1, j - 1);
            int LR = solve(lx, j + 1, i - 1, ry);
            int RU = solve(i + 1, ly, rx, j - 1);
            int RR = solve(i + 1, j + 1, rx, ry);
            all_suc.insert (LU ^ LR ^ RU ^ RR);
        }
    }
    int idx = 0;
    repeach (suc_item, all_suc) {
        if (*suc_item != idx) {
            break;
        }
        ++idx;
    }
    //printf ("cal SG %d %d %d %d = %d\n", lx, ly, rx, ry, idx);
    return sg[lx][ly][rx][ry] = idx;
}

int main() {
    repcase {
        // init
        scanf ("%d%d", &n, &m);
        rep (i, n) {
            scanf ("%s", mp[i]);
            CPC[i].clear();
        }
        rep (i, n) rep (j, m) {
            if (judge_CPC(i, j)) {
                CPC[i].push_back(j);
            }
        }
        
        // calc SG
        memset (sg, -1, sizeof(sg));
        puts (solve(0, 0, n - 1, m - 1)? "Asuna" : "Kirito");
    }
    return 0;
}

