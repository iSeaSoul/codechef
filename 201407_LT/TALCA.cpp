// Rain Dreamer MODEL
// iSea @ 2014-07-27 14:16
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

const int MAXN = 200000 + 10;

vector<int> g[MAXN];
int n, q;

void clear(int n) {
	rep (i, n) {
		g[i].clear();
	}
}

void insert(int u, int v, bool directed = 0) {
	g[u].push_back(v);
	if (!directed) {
		g[v].push_back(u);
	}
}

struct LCA {
	#define MAXLEVEL 19

	int dfn[MAXN], fa[MAXLEVEL][MAXN];

	void dfs(int x, int f) {
		fa[0][x] = f;
		for (vector<int>::iterator it = g[x].begin(); it != g[x].end(); ++it) {
			if (*it != f) {
				dfn[*it] = dfn[x] + 1;
				dfs(*it, x);
			}
		}
	}
	void prepare(int root = 0) {
		dfn[root] = 0;
		dfs (root, -1);
		repf (i, 1, MAXLEVEL - 1) rep (j, n) {
			if (fa[i - 1][j] == -1) {
				fa[i][j] = -1;
			} else {
				fa[i][j] = fa[i - 1][fa[i - 1][j]];
			}
		}
	}
	int query(int x, int y) {
		if (dfn[x] > dfn[y]) {
			swap(x, y);
		}
		// adjust to equal level
		int dif = dfn[y] - dfn[x], cnt = 0;
		while (dif) {
			if (dif & 1) y = fa[cnt][y];
			++cnt; dif >>= 1;
		}
		if (x == y) {
			return x;
		}
		// climb sync
		for (int i = MAXLEVEL - 1; i >= 0; --i) {
			if (fa[i][x] != fa[i][y]) {
				x = fa[i][x], y = fa[i][y];
			}
		}
		return fa[0][x];
	}
};

struct query_node {
	int id;
	int root, u, v;

	void input(int _id) {
		id = _id;
		scanf ("%d%d%d", &root, &u, &v);
		--root, --u, --v;
	}
	bool operator<(const query_node& rhs) const {
		return root < rhs.root;
	}
};

query_node qn[MAXN];
LCA lca;

int ans[MAXN];

int main() {
	while (scanf ("%d", &n) != EOF) {
		clear(n);

		rep (i, n - 1) {
			int u, v;
			scanf ("%d%d", &u, &v);
			insert (--u, --v);
		}
		scanf ("%d", &q);
		// rep (i, q) {
		// 	qn[i].input(i);
		// }

		// sort (qn, qn + q);

		// lca.prepare(qn[0].root);
		// rep (i, q) {
		// 	if (i && qn[i].root != qn[i - 1].root) {
		// 		lca.prepare(qn[i].root);
		// 	}
		// 	ans[qn[i].id] = lca.query(qn[i].u, qn[i].v) + 1;
		// }

		// rep (i, q) {
		// 	printf ("%d\n", ans[i]);
		// }
		lca.prepare();
		rep (i, q) {
			int root, u, v;
			scanf ("%d%d%d", &root, &u, &v);
			--root, --u, --v;

			int ori_c = lca.query(u, v);
			if (lca.query(ori_c, root) != ori_c) {
				printf ("%d\n", ori_c + 1);
			} else {
				int p1 = lca.query(root, u);
				int p2 = lca.query(root, v);
				if (lca.query(p1, p2) == p1) {
					printf ("%d\n", p2 + 1);
				} else {
					printf ("%d\n", p1 + 1);
				}
			}
		}
	}
	return 0;
}