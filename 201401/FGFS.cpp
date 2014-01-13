// New Ryan
// Create @ 20:24 01-03 2014
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

const int MAXN = 100000 + 10;

struct interval {
    int s, t;
    
    void input() {
        scanf ("%d%d", &s, &t);
    }
    bool operator<(const interval rhs) const {
        return t < rhs.t;
    }
};

map<int, int> room_ids;
int room_cnt;
vector<interval> itv[MAXN];
int n, k;

int get_room_cnt(int room_id) {
    if (room_ids.find(room_id) == room_ids.end()) {
        itv[room_cnt].clear();
        return room_ids[room_id] = room_cnt++;
    }
    return room_ids[room_id];
}

void hash_clear() {
    room_ids.clear();
    room_cnt = 0;
}

int main() {
    repcase {
        hash_clear();
        
        scanf ("%d%d", &n, &k);
        rep (i, n) {
            interval tmp;
            int room_id;
            
            tmp.input();
            scanf ("%d", &room_id);
            room_id = get_room_cnt(room_id);
            itv[room_id].push_back(tmp);
        }
        
        int res = 0;
            
        rep (i, room_cnt) {
            sort (all(itv[i]));
            int room_res = 1;
            int cur_end = itv[i][0].t;
            repf (j, 1, sz(itv[i]) - 1) {
                if (itv[i][j].s >= cur_end) {
                    room_res += 1;
                    cur_end = itv[i][j].t;
                }
            }
            res += room_res;
        }
        printf ("%d\n", res);
    }
    return 0;
}

