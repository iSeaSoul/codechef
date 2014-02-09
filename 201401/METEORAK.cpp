// Rain Dreamer MODEL
// Create @ 23:11 01-04 2014
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

const int MAXN = 1000 + 10;

int n, m, k;
vector<int> bps[MAXN];
int val[MAXN][MAXN];

void input() {
    repf (i, 1, m) {
        bps[i].clear();
    }
    rep (i, k) {
        int x, y;
        scanf ("%d%d", &x, &y);
        bps[y].push_back(x);
    }
    repf (i, 1, m) {
        sort(all(bps[i]));
    }
}

void calculate() {
    clz (val); 
    
    repf (i, 1, n) {
        // get line breaker
        vector<int> breaker[MAXN];
        repf (j, 1, m) {
            int id = lower_bound(all(bps[j]), i) - bps[j].begin();
            if (id < sz(bps[j])) {
                breaker[bps[j][id]].push_back(j);
            }
        }
        // swap line
        set<pii> all_seg;
        multiset<int> all_seg_len;
        all_seg.insert(pii(1, m));
        all_seg_len.insert(m);
        repf (j, i, n) {
            repeach (it, breaker[j]) {
                set<pii>::iterator seg = all_seg.lower_bound(pii(*it, MAXN));
                if (seg != all_seg.begin()) --seg;
                if (seg->first != *it) {
                    all_seg.insert(pii(seg->first, *it - 1));
                    all_seg_len.insert(*it - seg->first);
                }
                if (seg->second != *it) {
                    all_seg.insert(pii(*it + 1, seg->second));
                    all_seg_len.insert(seg->second - *it);
                }
                all_seg_len.erase(all_seg_len.find(seg->second - seg->first + 1));
                all_seg.erase(seg);
            }
            if (!all_seg_len.empty()) {
                val[i][j] = *all_seg_len.rbegin() * (j - i + 1);
            }
            //printf ("%d %d -> %d\n", i, j, val[i][j]);
        }
    }
    repf (len, 2, n) {
        repf (i, 1, n) {
            ckmax (val[i][i + len - 1], val[i][i + len - 2]);
            ckmax (val[i][i + len - 1], val[i + 1][i + len - 1]);
        }
    }
}

void output() {
    repcase {
        int l, r;
        scanf ("%d%d", &l, &r);
        printf ("%d\n", val[l][r]);
    }
}

int main() {
    clock_t begin = clock();
    
    while (scanf ("%d%d%d", &n, &m, &k) != EOF) {
        input();
        calculate();
        output();
    }
    
    printf ("used: %lf\n", 1.0 * (clock() - begin) / CLOCKS_PER_SEC);
    return 0;
}

