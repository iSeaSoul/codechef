// New Ryan
// Create @ 15:56 11-03 2013
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

struct comp {
    int id;
    comp(int _id): id(_id) {
    }
    
    bool operator()(vector<int> a, vector<int> b) {
        return a[id] < b[id];
    } 
};

const double SINGLE_TM = 0.12200;

const int maxn = 100000;
vector<vector<int> > a;
vector<int> b;
int n, k;

clock_t begin;

int ans = 0;
vector<int> ans_vec;

void try_update(int cur_cnt, vector<int> cur_vec) {
    if (cur_cnt > ans) {
        ans = cur_cnt;
        ans_vec = cur_vec;
    }
}


void try_all() {
    repf (mask, 1, (1 << n) - 1) {
        if (1.0 * (clock() - begin) > 0.05 * CLOCKS_PER_SEC) break;
        int cur_cnt = 0;
        vector<int> cur_vec;
        vector<int> cur(k, 0);
        bool can_make = true;
        
        rep (i, n) {
            if ((mask >> i) & 1) {
                bool flag = true;
                rep (j, k) {
                    cur[j] += a[i][j];
                    if (cur[j] > b[j]) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) {
                    can_make = false;
                    break;
                }
                cur_cnt++;
                cur_vec.push_back(a[i][k]);
            }
        }
        if (can_make) {
            try_update(cur_cnt, cur_vec);
        }
    }
}

void try_single() {
    rep (i, n) {
        bool flag = true;
        rep (j, k) {
            if (a[i][j] > b[j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            vector<int> cur(1, i + 1);
            try_update(1, cur);
        }
    }
}

void try_greedy(int curj = -1) {
    int cur_cnt = 0;
    vector<int> cur_vec;
    vector<int> cur(k, 0);
    rep (i, n) {
        if (curj >= 0 && a[i][curj] > b[curj]) {
            break;
        }
        bool flag = true;
        rep (j, k) {
            if (cur[j] + a[i][j] > b[j]) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;
        rep (j, k) {
            cur[j] += a[i][j];
        }
        cur_cnt++;
        cur_vec.push_back(a[i][k]);
    }
    
    //rep (i, cur_cnt) {
        //printf ("%d%c", cur_vec[i], i == cur_cnt - 1? '\n' : ' ');
    //}
    //rep (j, k) printf ("%d%c", cur[j], j == k - 1? '\n' : ' ');
    //puts ("---");
    try_update(cur_cnt, cur_vec);
}

int main() {
    /*wrte ("SEAVEC.in");
    puts ("10");
    rep (i, 10) {
        int n = 100, k = 1000;
        printf ("%d %d\n", n, k);
        rep (i, n) rep (j, k) {
            printf ("%d%c", rand() % 1000, j == k - 1? '\n' : ' ');
        }
        rep (j, k) {
            printf ("%d%c", 10000 + rand(), j == k - 1? '\n' : ' ');
        }
    }
    return 0; */
        
    //clock_t all_b = clock();
    repcase {
        begin = clock();
        scanf ("%d%d", &n, &k);
        a.clear();
        a.resize(n);
        rep (i, n) {
            a[i].clear();
            a[i].resize(k + 1);
            rep (j, k) {
                scanf ("%d", &a[i][j]);
            }
            a[i][k] = i + 1;
        }
        b.clear();
        b.resize(k);
        rep (j, k) {
            scanf ("%d", &b[j]);
        }
        ans = 0;
        ans_vec.clear();
        
        //try_single();
            
        if (n <= 10) {
            try_all();
        }
        else {
            rep (j, k) {
                if (1.0 * (clock() - begin) > SINGLE_TM * CLOCKS_PER_SEC) break;
                sort (all(a), comp(j));
                try_greedy(j);
            }

            rep (tms, 33) {
                if (1.0 * (clock() - begin) > SINGLE_TM * CLOCKS_PER_SEC) break;
                random_shuffle(all(a));
                try_greedy();
            }
        }
        printf ("%d\n", ans);
        sort (all(ans_vec));
        if (ans) {
            rep (i, ans) {
                printf ("%d%c", ans_vec[i], i == ans - 1? '\n' : ' ');
            }
        }
        puts ("");
    }
    //printf ("Used time = %lfs\n", 1.0 * (clock() - all_b) / CLOCKS_PER_SEC);
    return 0;
}

