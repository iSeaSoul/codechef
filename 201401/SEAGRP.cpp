// New Ryan
// Create @ 19:54 01-03 2014
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

const int maxn = 100 + 10;

struct graph {
    int n, match[maxn];
    bool adj[maxn][maxn];
    void clear() {
        memset (adj, 0, sizeof(adj));
        n = 0;
    }
    void insert(int u, int v) {
        n = max(n, max(u, v) + 1);
        adj[u][v] = adj[v][u] = true;
    }
    int max_match() {
        memset (match, -1, sizeof(match));
        int ans = 0;
        for (int i = 0; i < n; ++i)
            if (match[i] == -1){
                ans += bfs(i);
            }
        return ans;
    }
    int Q[maxn], pre[maxn], base[maxn];
    bool hash[maxn], in_blossom[maxn];
    int bfs (int p) {
        memset (pre, -1, sizeof(pre));
        memset (hash, 0, sizeof(hash));
        for (int i = 0; i < n; ++i)
            base[i] = i;
        Q[0] = p;
        hash[p] = 1;
        for (int s = 0, t = 1; s < t; ++s) {
            int u = Q[s];
            for (int v = 0; v < n; ++v) {
                if (adj[u][v] && base[u] != base[v] && v != match[u]) {
                    if (v == p || (match[v] != -1 && pre[match[v]] != -1)) {
                        int b = contract(u, v);
                        for (int i = 0; i < n; ++i) {
                            if (in_blossom[base[i]]) {
                                base[i] = b;
                                if (hash[i] == 0) {
                                    hash[i] = 1;
                                    Q[t++] = i;
                                }
                            }
                        }
                    } else if (pre[v] == -1) {
                        pre[v] = u;
                        if (match[v] == -1) {
                            argument(v);
                            return 1;
                        } else {
                            Q[t++] = match[v];
                            hash[match[v]] = 1;
                        }
                    }
                }
            }
        }
        return 0;
    }
    void argument (int u)  {
        while (u != -1) {
            int v = pre[u], k = match[v];
            match[u] = v;
            match[v] = u;
            u = k;
        }
    }
    void change_blossom (int b, int u) {
        while (base[u] != b) {
            int v = match[u];
            in_blossom[base[v]] = in_blossom[base[u]] = true;
            u = pre[v];
            if (base[u] != b) pre[u] = v;
        }
    }
    int contract (int u, int v) {
        memset (in_blossom, 0, sizeof(in_blossom));
        int b = find_base(base[u], base[v]);
        change_blossom(b, u);
        change_blossom(b, v);
        if (base[u] != b) pre[u] = v;
        if (base[v] != b) pre[v] = u;
        return b;
    }
    int find_base (int u, int v) {
        bool in_path[maxn] = {};
        while (true) {
            in_path[u] = true;
            if (match[u] == -1) break;
            u = base[pre[match[u]]];
        }
        while (!in_path[v])
            v = base[pre[match[v]]];
        return v;
    }
};

graph g;

int main() {
    repcase {
        int n, m, u, v;
        scanf ("%d%d", &n, &m);
        g.clear();
        rep (i, m) {
            scanf ("%d%d", &u, &v);
            g.insert (u, v);
        }
        if (n % 2 == 0 && g.max_match() == n / 2) {
            puts ("YES");
        } else {
            puts ("NO");
        }
    }
    return 0;
}

