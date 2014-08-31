// Rain Dreamer MODEL
// iSea @ 2014-08-31 15:47
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
	int x, y;
	void input() {
		scanf ("%d%d", &x, &y);
	}
};

struct edge {
	int u, v, d;

	bool operator<(const edge& rhs) const {
		return d < rhs.d;
	}
};

const int MAXN = 200000 + 10;

struct disjoint_set {
	int p[MAXN];

	void clear() {
		rep (i, MAXN) p[i] = i;
	}
	int find(int x) {
		return x == p[x]? x : p[x] = find(p[x]);
	}
	bool join(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return false;
		p[x] = y;
		return true;
	}
} ds;

vector<edge> e;
vector<pii> XY1, XY2;
vector<pii> mst[MAXN];
point p[MAXN];
int n;

void add_edge(int u, int v) {
	int dis = abs(p[u].x - p[v].x) + abs(p[u].y - p[v].y);
	e.push_back(edge{u, v, dis});
}

/*
 * Hint: This is a wrong method to build Manhattan MST
 * The right method should be:
 * Process the point i by the order of xi + yi;
 * Find the closest xj - yj > xi - yi in which xj + yj > xi + yi;
 * And the edge
 */
void build_Manhattan_MST() {
	XY1.clear(); XY2.clear(); e.clear();
	rep (i, n) {
		XY1.push_back(pii(p[i].x + p[i].y, i));
		XY2.push_back(pii(p[i].x - p[i].y, i));
	}
	sort (XY1.begin(), XY1.end());
	sort (XY2.begin(), XY2.end());
	int pre1 = 0;
	int pre2 = 0;
	repf (i, 1, n - 1) {
		if (XY1[i].first != XY1[pre1].first) {
			add_edge(XY1[i].second, XY1[pre1].second);
			pre1 = i;
		}
		
		if (XY2[i].first != XY2[pre2].first) {
			add_edge(XY2[i].second, XY2[pre2].second);
			pre2 = i;
		}
	}
	rep (i, n) mst[i].clear();
	sort (e.begin(), e.end());
	ds.clear();
	int nume = n - 1;
	for (auto ei : e) {
		if (ds.join(ei.u, ei.v)) {
			mst[ei.u].push_back(pii(ei.v, ei.d));
			mst[ei.v].push_back(pii(ei.u, ei.d));
			if (--nume == 0) {
				break;
			}
		}
	}
}

void build_LCA() {

}

int get_lca(int x, int y) {
	return 0;
}

int get_maxlen(int px, int x) {
	return 0;
}

bool vis[MAXN];
int cp[MAXN];

int bfs(int x, int y) {
	memset (vis, 0, sizeof(vis));
	queue<int> q;
	q.push(x);
	vis[x] = true; cp[x] = 0;
	if (x == y) return 0;
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (auto next : mst[cur]) {
			if (!vis[next.first]) {
				cp[next.first] = max(cp[cur], next.second);
				if (next.first == y) return cp[next.first];
				q.push(next.first); vis[next.first] = true;
			}
		}
	}
}

int main() {
	repcase {
		scanf ("%d", &n);
		rep (i, n) {
			p[i].input();
		}
		build_Manhattan_MST();

		int q, a, b;
		scanf ("%d", &q);
		while (q--) {
			scanf ("%d%d", &a, &b);
			printf ("%d\n", bfs(--a, --b));
		}
		// build_LCA();

		// int q, a, b;
		// scanf ("%d", &q);
		// while (q--) {
		// 	scanf ("%d%d", &a, &b);
		// 	--a, --b;
		// 	int l = get_lca(a, b);
		// 	printf ("%d\n", max(get_maxlen(l, a), get_maxlen(l, b)));
		// }
	}
	return 0;
}