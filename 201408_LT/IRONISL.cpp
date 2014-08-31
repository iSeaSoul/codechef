// Rain Dreamer MODEL
// iSea @ 2014-08-31 15:20
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

const int MAXN = 1000 + 10;

set<int> g[MAXN];
int n, q;
int dis[MAXN];

int bfs(int x) {
	memset (dis, -1, sizeof(dis));
	queue<int> q;
	q.push(x); dis[x] = 0;
	int ret = 0;
	int cnt = 1;
	while (!q.empty()) {
		int c = q.front(); q.pop();
		int cdis = dis[c];
		if (cnt == n) {
			return ret ;
		}
		// printf ("%d: %d\n", c, cdis);
		for (auto next: g[c]) {
			if (dis[next] == -1) {
				q.push(next); dis[next] = cdis + 1;
				ret += dis[next];
				cnt++;
			}
		}
	}
	return ret;
}

int main() {
	repcase {
		scanf ("%d", &n);
		rep (i, n) {
			char buf[1010];
			scanf ("%s", buf);
			g[i].clear();
			rep (j, n) if (buf[j] == '1') {
				g[i].insert (j);
			}
		}
		scanf ("%d", &q);
		while (q--) {
			int v, m, a, b;
			scanf ("%d%d", &v, &m);
			--v;
			rep (i, m) {
				scanf ("%d%d", &a, &b);
				--a, --b;
				if (!g[a].insert(b).second) {
					g[a].erase(b);
				}
			}
			printf ("%d\n", bfs(v));
		}
	}
	return 0;
}