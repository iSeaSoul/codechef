// Rain Dreamer MODEL
// Create @ 18:22 01-12 2014
// Comment - 

#include <cmath>
#include <ctime>
#include <cstdio>
#include <cassert>
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

struct point {
    double x, y;
    
    void input() {
        scanf ("%lf%lf", &x, &y);
    }
    void print() const {
        printf ("-- %lf %lf\n", x, y);
    }
    point(double _x = 0, double _y = 0): x(_x), y(_y) {
    }
};

point operator-(const point& p1, const point& p2) {
    return point(p1.x - p2.x, p1.y - p2.y);
}
double operator^(const point& p1, const point& p2) {
    return p1.x * p2.x + p1.y * p2.y;
}
double operator*(const point& p1, const point& p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

bool get_intersection(const point& p1, const point& p2, const point& p3, const point& p4) {
    double d1 = (p2 - p1) * (p3 - p1), d2 = (p2 - p1) * (p4 - p1);
    double d3 = (p4 - p3) * (p1 - p3), d4 = (p4 - p3) * (p2 - p3);
    int s1 = sgn(d1), s2 = sgn(d2), s3 = sgn(d3), s4 = sgn(d4);
    if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0)
        return false;
    point c = point((p3.x * d2 - p4.x * d1) / (d2 - d1), (p3.y * d2 - p4.y * d1) / (d2 - d1));
    //if (s1 * s2 <= 0 && s3 * s4 <= 0) {
        //printf ("(%lf, %lf) (%lf, %lf) (%lf, %lf) (%lf, %lf) -> ", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
        //c.print();
    //}
    return s1 * s2 <= 0 && s3 * s4 <= 0;
}

const int MAXN = 50 + 10;

int n;
point p[MAXN];
char g[MAXN][MAXN];
bool vis[MAXN][MAXN], v[MAXN];
int left_edge_cnt[MAXN], id[MAXN];

int SOLVE_TYPE;

bool comp(int x, int y) {
    return left_edge_cnt[x] > left_edge_cnt[y];
}

void mark(int x, int y) {
    v[x] = v[y] = true;
    vis[x][y] = vis[y][x] = true;
    left_edge_cnt[x]--;
    left_edge_cnt[y]--;
}

bool check_cross(vector<int> res, int cur, int next) {
    repf (i, 1, sz(res) - 2) {
        if (get_intersection(p[res[i - 1]], p[res[i]], p[cur], p[next])) {
            return false;
        }
    }
    return true;
}

void dfs(vector<int>& res, int cur) {
    if (SOLVE_TYPE == 1) sort (id, id + n, comp);
    else random_shuffle(id, id + n);
    
    rep (i, n) {
        int x = id[i];
        if (!v[x] && g[cur][x] == 'Y' && !vis[cur][x]) {
            if (check_cross(res, cur, x)) {
                res.push_back(x);
                mark (cur, x);
                dfs (res, x);
                
                return ;
            }
        }
    }
}

bool check_cross_last(vector<int> res, int cur, int next) {
    repf (i, 2, sz(res) - 2) {
        if (get_intersection(p[res[i - 1]], p[res[i]], p[cur], p[next])) {
            return false;
        }
    }
    return true;
}

vector<int> try_dfs(int x, int next) {
    vector<int> res;
    res.push_back(x);
    res.push_back(next);
    
    clz(v);
    mark (x, next);
    
    dfs(res, next);
    
    int cur = res[sz(res) - 1], cnext = res[0];
    if (g[cur][cnext] == 'Y' && !vis[cur][cnext] && check_cross_last(res, cur, cnext)) {
        mark (cur, cnext);
        res.push_back(cnext);
    }
    
    return res;
}

void init() {
    rep (i, n) {
        p[i].input();
    }
    rep (i, n) {
        scanf ("%s", g[i]);
    }
}

vector<vector<int> > solve_strict() {
    SOLVE_TYPE = 1;
    
    srand((unsigned)(time(NULL) * 100213));
    clz (left_edge_cnt);
    
    rep (i, n) rep (j, n) {
        vis[i][j] = (g[i][j] == 'N');
        if (g[i][j] == 'Y') {
            ++left_edge_cnt[i];
        }
    }
    
    vector<vector<int> > ans;
    while (true) {
        sort (id, id + n, comp);
        reverse (id, id + n);
        int start_id = id[0];
        int now_id = start_id;
        bool found = false;
        rep (i, n) id[i] = i;
        
        do {
            sort (id, id + n, comp);
            reverse (id, id + n);
            
            rep (i, n) {
                int x = id[i];
                if (g[now_id][x] == 'Y' && !vis[now_id][x]) {
                    found = true;
                    // try dfs to find ans
                    ans.push_back(try_dfs(now_id, x));
                    break;
                }
            }
            now_id = (now_id + 1) % n;
        } while (now_id != start_id && !found);
        
        if (!found) break ;
    };
    
    return ans;
}

vector<vector<int> > solve_random() {
    SOLVE_TYPE = 1;
    
    srand((unsigned)(time(NULL) * 100213));
    clz (left_edge_cnt);
    
    rep (i, n) rep (j, n) {
        vis[i][j] = (g[i][j] == 'N');
        if (g[i][j] == 'Y') {
            ++left_edge_cnt[i];
        }
    }
    
    vector<vector<int> > ans;
    while (true) {
        int start_id = rand() % n;
        int now_id = start_id;
        bool found = false;
        rep (i, n) id[i] = i;
        
        do {
            sort (id, id + n, comp);
            
            rep (i, n) {
                int x = id[i];
                if (g[now_id][x] == 'Y' && !vis[now_id][x]) {
                    found = true;
                    // try dfs to find ans
                    ans.push_back(try_dfs(now_id, x));
                    break;
                }
            }
            now_id = (now_id + 1) % n;
        } while (now_id != start_id && !found);
        
        if (!found) break ;
    };
    
    return ans;
}

vector<vector<int> > solve_random_2() {
    SOLVE_TYPE = 1;
    
    srand((unsigned)(time(NULL) * 100213));
    clz (left_edge_cnt);
    
    rep (i, n) rep (j, n) {
        vis[i][j] = (g[i][j] == 'N');
        if (g[i][j] == 'Y') {
            ++left_edge_cnt[i];
        }
    }
    
    vector<vector<int> > ans;
    while (true) {
        int start_id = rand() % n;
        int now_id = start_id;
        bool found = false;
        rep (i, n) id[i] = i;
        
        do {
            sort (id, id + n, comp);
            if (rand() % 2 == 0) reverse (id, id + n);
            
            rep (i, n) {
                int x = id[i];
                if (g[now_id][x] == 'Y' && !vis[now_id][x]) {
                    found = true;
                    // try dfs to find ans
                    ans.push_back(try_dfs(now_id, x));
                    break;
                }
            }
            now_id = (now_id + 1) % n;
        } while (now_id != start_id && !found);
        
        if (!found) break ;
    };
    
    return ans;
}

vector<vector<int> > solve_more_random() {
    SOLVE_TYPE = 2;
    
    srand((unsigned)(time(NULL) * 100213));
    clz (left_edge_cnt);
    
    rep (i, n) rep (j, n) {
        vis[i][j] = (g[i][j] == 'N');
        if (g[i][j] == 'Y') {
            ++left_edge_cnt[i];
        }
    }
    
    vector<vector<int> > ans;
    while (true) {
        int start_id = rand() % n;
        int now_id = start_id;
        bool found = false;
        rep (i, n) id[i] = i;
        
        do {
            random_shuffle(id, id + n);
            
            rep (i, n) {
                int x = id[i];
                if (g[now_id][x] == 'Y' && !vis[now_id][x]) {
                    found = true;
                    // try dfs to find ans
                    ans.push_back(try_dfs(now_id, x));
                    break;
                }
            }
            now_id = (now_id + 1) % n;
        } while (now_id != start_id && !found);
        
        if (!found) break ;
    };
    
    return ans;
}

const int TMS = 3000;
const double CASE_TM = 0.74747;

void solve() {
    clock_t begin = clock();
    vector<vector<int> > ans = solve_strict();
    
    rep (cnt, n * TMS) {
        if (1.0 * (clock() - begin) / CLOCKS_PER_SEC > CASE_TM) {
            break;
        }
        vector<vector<int> > tmp = solve_random();
        //printf ("sz %d\n", sz(tmp));
        if (sz(tmp) < sz(ans)) {
            ans = tmp;
        }
        tmp = solve_random_2();
        if (sz(tmp) < sz(ans)) {
            ans = tmp;
        }
        tmp = solve_random_2();
        if (sz(tmp) < sz(ans)) {
            ans = tmp;
        }
    }
    //printf ("USED time = %lfs\n", 1.0 * (clock() - begin) / CLOCKS_PER_SEC);
    while (1.0 * (clock() - begin) / CLOCKS_PER_SEC < CASE_TM) {
        vector<vector<int> > tmp = solve_more_random();
        //printf ("sz %d\n", sz(tmp));
        if (sz(tmp) < sz(ans)) {
            ans = tmp;
        }
    }
    //printf ("USED time = %lfs\n", 1.0 * (clock() - begin) / CLOCKS_PER_SEC);
    
    printf ("%d\n", sz(ans));
    rep (i, sz(ans)) {
        printf ("%d", sz(ans[i]) - 1);
        rep (j, sz(ans[i])) {
            printf (" %d", ans[i][j]);
        }
        puts ("");
    }
}

int main() {
    while (scanf ("%d", &n) != EOF) {
        init();
        solve();
    }
    return 0;
}

