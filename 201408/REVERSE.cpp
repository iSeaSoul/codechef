// Rain Dreamer MODEL
// iSea @ 2014-08-01 18:04
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

const int MAXN = 100000 + 10;

vector<pii> g[MAXN];
int dis[MAXN], n, m;

struct node {
	int x, d;

	bool operator<(const node& rhs) const {
		return d > rhs.d;
	}
};

int main() {
	while (scanf ("%d%d", &n, &m) != EOF) {
		rep (i, n) {
			g[i].clear();
		}
		rep (i, m) {
			int u, v;
			scanf ("%d%d", &u, &v);
			g[u].push_back(pii(v, 0));
			g[v].push_back(pii(u, 1));
		}
		memset (dis, -1, sizeof(dis));
		priority_queue<node> pq;
		pq.push(node{1, 0});
		dis[1] = 0;
		while (!pq.empty()) {
			node c = pq.top(); pq.pop();
			if (c.x == n) {
				break;
			}
			repeach (it, g[c.x]) {
				int nd = c.d + it->second;
				if (dis[it->first] == -1 || dis[it->first] > nd) {
					dis[it->first] = nd;
					pq.push(node{it->first, nd});
				}
			}
		}
		printf ("%d\n", dis[n]);
	}
	return 0;
}