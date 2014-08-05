// Rain Dreamer MODEL
// iSea @ 2014-08-03 14:08
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

bool read_op() {
	for (char ch = getchar(); ch != '0' && ch != '1'; ch = getchar()) {
		return ch == '1';
	}
}

int read_int() {
	char ch;
	for (ch = getchar(); !(ch >= '0' && ch <= '9'); ch = getchar());
	int res = ch - '0';
	for (ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar()) {
		res = res * 10 + ch - '0';
	}
	return res;
}

struct edge {
	int u, v, w;

	void input() {
		scanf ("%d%d%d", &u, &v, &w);
	}
};

struct adj {
	int v, w;

	adj(int _v = 0, int _w = 0): v(_v), w(_w) {
	}
};

const int MAXE = 200000 + 10;
const int MAXN = 100000 + 10;

edge e[MAXE];
vector<adj> g[MAXN];
int n, m;

void prep() {

}

void update_edge(int eid, int nw) {

}

int query_maxflow(int s, int t) {
	
}

int main() {
	scanf ("%d%d", &n, &m);
	rep (i, m) {
		e[i].input();
		g[e[i].v].push_back(adj(e[i].u, e[i].w));
		g[e[i].u].push_back(adj(e[i].v, e[i].w));
	}
	prep();

	repcase {
		bool op = read_op();
		int x = read_int(), y = read_int();
		if (op) {
			printf ("%d\n", query_maxflow(x, y));
		} else {
			update_edge(x, y);
		}
	}

	return 0;
}