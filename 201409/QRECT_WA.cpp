// Rain Dreamer MODEL
// iSea @ 2014-09-05 23:47
// Comment - 

#include <bits/stdc++.h>

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

	point(int _x = 0, int _y = 0): x(_x), y(_y) {
	}
	bool operator<(const point &p) const {
		return x == p.x? y < p.y : x < p.x;
	}
	bool operator==(const point &p) const {
		return x == p.x && y == p.y;
	}
};

struct kd_tree {
	struct node {
		int l, r, x1, y1, x2, y2, delta, maxv;
		node(int _x1, int _y1, int _x2, int _y2): 
		l(-1), r(-1), x1(_x1), y1(_y1), x2(_x2), y2(_y2), delta(0), maxv(0) {
		}
	};
	struct less_equal_x : binary_function<point, point, bool> {
		bool operator()(const point& p1, const point& p2) const {
			return p1.x <= p2.x;
		}
	};
	struct less_equal_y : binary_function<point, point, bool> {
		bool operator()(const point& p1, const point& p2) const {
			return p1.y <= p2.y;
		}
	};
	vector<node> nodes;
	void clear() {
		nodes.clear();
	}
	void build(point* p, int from, int to, int id = 0) {
		int min_x = INT_MAX, max_x = INT_MIN, min_y = INT_MAX, max_y = INT_MIN;
		for (int i = from; i < to; ++i) {
			if (p[i].x < min_x)
				min_x = p[i].x;
			if (p[i].x > max_x)
				max_x = p[i].x;
			if (p[i].y < min_y)
				min_y = p[i].y;
			if (p[i].y > max_y)
				max_y = p[i].y;
		}
		nodes.push_back(node(min_x, min_y, max_x, max_y));
		int dx = max_x - min_x, dy = max_y - min_y, mid = -1;
		if (dx == 0 && dy == 0)
			return;
		if (dx > dy) {
			int k = (min_x + max_x) / 2;
			mid = partition(p + from, p + to, bind2nd(less_equal_x(), point(k, 0))) - p;
		} else {
			int k = (min_y + max_y) / 2;
			mid = partition(p + from, p + to, bind2nd(less_equal_y(), point(0, k))) - p;
		}
		if (from < mid) {
			nodes[id].l = nodes.size();
			build(p, from, mid, nodes.size());
		}
		if (mid < to) {
			nodes[id].r = nodes.size();
			build(p, mid, to, nodes.size());
		}
	}
	int add(int x1, int y1, int x2, int y2, int delta, int id = 0) {
		node &v = nodes[id];
		if (x1 > v.x2 || x2 < v.x1 || y1 > v.y2 || y2 < v.y1)
			return 0;
		if (x1 <= v.x1 && x2 >= v.x2 && y1 <= v.y1 && y2 >= v.y2) {
			v.delta += delta;
			return v.maxv + v.delta;
		}
		v.maxv = 0;
		if (v.l != -1)
			ckmax(v.maxv, add(x1, y1, x2, y2, delta, v.l));
		if (v.r != -1)
			ckmax(v.maxv, add(x1, y1, x2, y2, delta, v.r));
		return v.maxv + v.delta;
	}
	int get_maxv(int x1, int y1, int x2, int y2, int id = 0) {
		node &v = nodes[id];
		if (x1 > v.x2 || x2 < v.x1 || y1 > v.y2 || y2 < v.y1)
			return 0;
		if (v.delta != 0) {
			push_down(id);
		}
		if (x1 <= v.x1 && x2 >= v.x2 && y1 <= v.y1 && y2 >= v.y2)
			return v.maxv;
		int res = 0;
		if (v.l != -1)
			ckmax(res, get_maxv(x1, y1, x2, y2, v.l));
		if (v.r != -1)
			ckmax(res, get_maxv(x1, y1, x2, y2, v.r));
		return res;
	}
	void push_down(int id) {
		node &v = nodes[id];
		v.maxv += v.delta;
		if (v.l != -1)
			nodes[v.l].delta += v.delta;
		if (v.r != -1)
			nodes[v.r].delta += v.delta;
		v.delta = 0;
	}
};

const int MAXN = 100000 + 10;

kd_tree kdt;
point p[MAXN << 1];
int pcnt(0), q;

struct Qnode {
	char op;
	int id;
	int x1, y1, x2, y2;

	void input() {
		char buf[2];
		scanf ("%s", buf);
		op = buf[0];

		if (op == 'I') {
			scanf ("%d%d%d%d", &x1, &y1, &x2, &y2);
			p[pcnt++] = point(x1, y1);
			p[pcnt++] = point(x2, y2);
		} else if (op == 'D') {
			scanf ("%d", &id);
			id -= 1;
		} else {
			scanf ("%d%d%d%d", &x1, &y1, &x2, &y2);
			p[pcnt++] = point(x1, y1);
			p[pcnt++] = point(x2, y2);
		}
	}
} Q[MAXN];

int main() {
	scanf ("%d", &q);
	rep (i, q) {
		Q[i].input();
	}

	sort (p, p + pcnt);
	pcnt = unique(p, p + pcnt) - p;
	kdt.clear();
	kdt.build(p, 0, pcnt);

	rep (i, q) {
		if (Q[i].op == 'I') {
			kdt.add(Q[i].x1, Q[i].y1, Q[i].x2, Q[i].y2, 1);
		} else if (Q[i].op == 'D') {
			kdt.add(Q[Q[i].id].x1, Q[Q[i].id].y1, Q[Q[i].id].x2, Q[Q[i].id].y2, -1);
		} else {
			printf ("%d\n", kdt.get_maxv(Q[i].x1, Q[i].y1, Q[i].x2, Q[i].y2));
		}
	}
	return 0;
}