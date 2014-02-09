// Rain Dreamer MODEL
// Create @ 20:42 01-12 2014
// Comment - 

#pragma comment(linker,"/STACK:65536000")

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

const int MAXN = 100000 + 10;
const int MAXM = 300000 + 10;

struct disjoint_set {
    int p[MAXN];
    
    void init(int n) {
        rep (i, n) {
            p[i] = i;
        }
    }
    int find(int x) {
        return x == p[x]? x : p[x] = find(p[x]);
    }
    void join(int x, int y) {
        p[find(x)] = find(y);
    }
};

struct chair_tree {
    struct node {
        int l, r, val;
    };
    
    node n[MAXM * 20];
    int r_cnt, max_right;
    
    void init() {
        r_cnt = 0;
    }
    void set_max_right(int _max_right) {
        max_right = _max_right;
    }
    int build(int l, int r) {
        int curR = r_cnt++;
        n[curR].val = 0;
        if (l != r) {
            n[curR].l = build (l, (l + r) >> 1);
            n[curR].r = build (((l + r) >> 1) + 1, r);
        }
        return curR;
    }
    void update_dif(int cur_root, int root, int val) {
        n[cur_root].val = n[root].val + val;
    }
    int update(int root, int pos, int val) {
        int nextR = r_cnt++;
        int resR = nextR;
        update_dif (nextR, root, val);
        
        int l = 1, r = max_right;
        while (l != r) {
            int mid = (l + r) >> 1;
            if (pos <= mid) {
                n[nextR].l = r_cnt++; n[nextR].r = n[root].r;
                nextR = n[nextR].l; root = n[root].l;
                r = mid;
            } else {
                n[nextR].r = r_cnt++; n[nextR].l = n[root].l;
                nextR = n[nextR].r; root = n[root].r;
                l = mid + 1;
            }
            update_dif (nextR, root, val);      
        }
        
        return resR;
    }
    // query [l_root + 1, r_root] sum[1..pos]
    int query_sum(int l_root, int r_root, int pos) {
        int res = 0;
        
        int l = 1, r = max_right;
        while (true) {
            int mid = (l + r) >> 1;
            if (r == pos) {
                res += n[r_root].val - n[l_root].val;
                break ;
            }
            if (pos <= mid) {
                l_root = n[l_root].l; r_root = n[r_root].l;
                r = mid;
            } else {
                res += n[n[r_root].l].val - n[n[l_root].l].val;
                l_root = n[l_root].r; r_root = n[r_root].r;
                l = mid + 1;
            }
        }
        return res;
    }
};


int n, m;
vector<int> g[MAXN], newg[MAXN];
vector<pii> bridge;

void init_graph() {
    rep (i, n) {
        g[i].clear();
        newg[i].clear();
    }
    bridge.clear();
}

void input_graph() {
    rep (i, m) {
        int u, v;
        scanf ("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

int dfn[MAXN], low[MAXN], tms, back_edge_cnt;
int height[MAXN], begin_bec[MAXN], end_bec[MAXN], becnt[MAXN];
bool vis[MAXN];

int treeID[MAXM];
disjoint_set ds;
chair_tree ct;

void init_bridge_dfs_state() {
    tms = 0;
    clz (dfn); 
    clz (low);
}

// get bridge
void bridge_dfs(int x, int p) {
    dfn[x] = low[x] = ++tms;
    repeach (it, g[x]) {
        if (!dfn[*it]) {
            bridge_dfs(*it, x);
            low[x] = min(low[x], low[*it]);
            if (dfn[x] < low[*it]) {
                bridge.push_back(pii(x, *it));
            }
        } else if (*it != p) {
            low[x] = min(low[x], dfn[*it]);
        }
    }
}

void get_bridge() {
    init_bridge_dfs_state();
    bridge_dfs (0, -1);
}

void rebuild_graph() {
    ds.init(n);
    repeach (it, bridge) {
        ds.join(it->first, it->second);
    }
    
    rep (i, n) {
        repeach (it, g[i]) {
            if (ds.find(i) != ds.find(*it)) {
                newg[ds.find(i)].push_back(ds.find(*it));
            }
        }
    }
}

void init_height_dfs_state() {
    clz (height);
    tms = 0;
}

// get height
void height_dfs(int x, int p) {
    height[x] = (p == -1? 1 : height[p] + 1);
    
    repeach (it, newg[x]) {
        if (!height[*it]) {
            height_dfs(*it, x);
        }
    }
}

void init_buildtree_dfs_state() {
    clz (vis);
    back_edge_cnt = 0;
}

// build tree & get node interval
void buildtree_dfs(int x, int p) {
    vis[x] = true;
    begin_bec[x] = back_edge_cnt;
    repeach (it, newg[x]) {
        if (!vis[*it]) {
            buildtree_dfs(*it, x);
        } else if (*it != p && height[*it] < height[x]) {
            back_edge_cnt++;
            treeID[back_edge_cnt] = ct.update(treeID[back_edge_cnt - 1], height[*it], 1);
        }
    }
    end_bec[x] = back_edge_cnt;
    
    int l_root = treeID[begin_bec[x]], r_root = treeID[end_bec[x]];
    if (p != -1) {
        becnt[x] = ct.query_sum(l_root, r_root, height[p]);
    }
}

void build_chairtree() {
    int root = ds.find(0);
    
    init_height_dfs_state();
    height_dfs(root, -1);
    
    int max_height = *max_element(height, height + n);
    
    ct.init();
    ct.set_max_right(max_height);
    treeID[0] = ct.build(1, max_height);
    
    init_buildtree_dfs_state();
    buildtree_dfs(root, -1);
}

int bsearch_maxh(int l_root, int r_root, int l, int r) {
    int maxsum = ct.query_sum(l_root, r_root, r);
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (ct.query_sum(l_root, r_root, mid) < maxsum) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

vector<int> be_bucket[MAXM];

void init_getans_dfs_state() {
    clz (vis);
}

void getans_dfs(int x, int p, int64& res) {
    vis[x] = true;
    if (p != -1) be_bucket[becnt[x]].push_back(height[x]);
    
    repeach (it, newg[x]) {
        if (!vis[*it]) {
            getans_dfs(*it, x, res);
            res += (becnt[*it] == 1);
            
            int l_root = treeID[begin_bec[*it]], r_root = treeID[end_bec[*it]];
            int maxh = bsearch_maxh(l_root, r_root, 1, height[x]);
            res += be_bucket[becnt[*it]].end() - upper_bound(all(be_bucket[becnt[*it]]), maxh);
        }
    }
    if (p != -1) be_bucket[becnt[x]].pop_back();
}

void get_answer() {
    int64 ans = 0;
    init_getans_dfs_state();
    getans_dfs(ds.find(0), -1, ans);
    //cout << "pre " << ans << endl;
    
    int64 bridge_cnt = sz(bridge);
    ans += ((int64)m * (m - 1) - (m - bridge_cnt) * (m - bridge_cnt - 1)) / 2;
    
    cout << ans << endl;
}

bool input() {
    if (scanf ("%d%d", &n, &m) == EOF) {
        return false;
    }
    
    init_graph();
    input_graph();
    
    return true;
}

void solve() {
    get_bridge();
    rebuild_graph();
    build_chairtree();
    get_answer();
}

int main() {
    //int size = 256 << 20; // 256MB
    //char *p = (char*)malloc(size) + size;
    //__asm__("movl %0, %%esp\n" :: "r"(p));
    
    while (input()) solve(); 
    return 0;
}

