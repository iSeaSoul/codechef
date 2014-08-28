// New Ryan
// Create @ 16:13 10-07 2013
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

const int maxn = 102;
const int TMS = 10000;
const int step_dir[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

char s[maxn][maxn], tmp[maxn][maxn];
bool vis[maxn][maxn];
int n, m, c2, c3;

int cdfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || vis[x][y] || s[x][y] != 'B') {
        return 0;
    }
    vis[x][y] = true;
    int res = 1;
    res += cdfs(x + 1, y) + cdfs(x - 1, y);
    res += cdfs(x, y + 1) + cdfs(x, y - 1);
    return res;
}

int dfs(int x, int y) {
    queue<int> q;
    q.push(x), q.push(y);
    vis[x][y] = true;
    int res = 0;
    while (!q.empty()) {
        int cx = q.front(); q.pop();
        int cy = q.front(); q.pop();
        res += 1;
        rep (di, 4) {
            int nx = cx + step_dir[di][0];
            int ny = cy + step_dir[di][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && s[nx][ny] == 'B'
                    && vis[nx][ny] == false) {
                q.push(nx), q.push(ny);
                vis[nx][ny] = true;
            }
        }
    }
    return res;
}

vector<pii> solve2() {
    memcpy (tmp, s, sizeof(tmp));
    
    vector<pii> res;
    int si = -1, sj = -1;
    int bnum = 0;
    rep (i, n) rep (j, m) {
        if (s[i][j] == 'W') {
            if (rand() % 3 == 1 || n * m <= 100) {
                res.push_back(pii(i, j));
                s[i][j] = 'B';
            }
        } else {
            si = i, sj = j;
            bnum += 1;
        }
    }
    if (si == -1) {
        memcpy (s, tmp, sizeof(tmp));
        return res;
    }
    
    int try_tm = 0;
    bool ok = false;
    while (try_tm++ < 10) {
        memset (vis, 0, sizeof(vis));
        if (dfs(si, sj) == bnum + sz(res)) {
            ok = true;
            break;
        }
        memcpy (s, tmp, sizeof(tmp));
        res.clear();
        rep (i, n) rep (j, m) {
            if (s[i][j] == 'W') {
                if (rand() % 3 == 1 || n * m <= 100) {
                    res.push_back(pii(i, j));
                    s[i][j] = 'B';
                }
            } 
        }
    }
    if (!ok) {
        memcpy (s, tmp, sizeof(tmp));
        res.clear();
        rep (i, n) rep (j, m) {
            if (s[i][j] == 'W') {
                res.push_back(pii(i, j));
                s[i][j] = 'B';
            } 
        }
    }
    
    clock_t begin = clock();
    rep (cnt, min(n * m * 10, TMS)) {
        if (1.0 * (clock() - begin) / CLOCKS_PER_SEC > 0.5) {
            break;
        }
        if (sz(res) == 0) {
            break;
        }
        
        random_shuffle(all(res));
        s[res.back().first][res.back().second] = 'W';
        memset (vis, 0, sizeof(vis));
        if (dfs(si, sj) == bnum + sz(res) - 1) {
            //puts ("pop back");
            res.pop_back();
        } else {
            s[res.back().first][res.back().second] = 'B';
        }
    }
    //rep (i, n) puts (s[i]);
    memcpy (s, tmp, sizeof(tmp));
    return res;
}

vector<pii> solve3() {
    vector<pii> res;
    memset (vis, 0, sizeof(vis));
    int max_block = 0;
    int maxi, maxj;
    rep (i, n) rep (j, m) {
        if (!vis[i][j] && s[i][j] == 'B') {
            int block_num = dfs(i, j);
            if (block_num > max_block) {
                max_block = block_num;
                maxi = i; maxj = j;
            }
        }
    }
    if (max_block == 0) {
        return res;
    }
    memset (vis, 0, sizeof(vis));
    dfs(maxi, maxj);
    rep (i, n) rep (j, m) {
        if (s[i][j] == 'B' && !vis[i][j]) {
            res.push_back(pii(i, j));
        }
    }
    return res;
}

int main() {
    //wrte ("gen.out");
    //printf ("100 100 10 30\n");
    //rep (i, 100) rep (j, 100) {
        //printf ("%c", rand() % 2 == 0? 'B' : 'W');
        //if (j == 99) puts ("");
    //}
    //return 0;
    repcase {
        clock_t begin = clock();
        scanf ("%d%d%d%d", &n, &m, &c2, &c3);
        rep (i, n) {
            scanf ("%s", s[i]);
        }
        vector<pii> ci2 = solve2();
        vector<pii> ci3 = solve3();
        if (sz(ci2) * c2 < sz(ci3) * c3) {
            printf ("%d\n", sz(ci2));
            repeach (item, ci2) {
                printf ("2 %d %d\n", item->first + 1, item->second + 1);
            }
        } else {
            printf ("%d\n", sz(ci3));
            repeach (item, ci3) {
                printf ("3 %d %d\n", item->first + 1, item->second + 1);
            }
        }
        //printf ("used: %lf\n", 1.0 * (clock() - begin) / CLOCKS_PER_SEC);
    }
    return 0;
}

