// Rain Dreamer MODEL
// Create @ 20:39 03-09 2014
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

struct binary_index_tree {
	#define lowbit(x) ((x) & (-(x)))

	vector<int> val, pos;
	vector<int> bit_val, bit_cnt;
	int n;

	void clear() {
		pos.clear();
		val.clear(); 
		bit_val.clear();
		bit_cnt.clear();

		// avoid idx 0
		pos.push_back(-1);
		val.push_back(-1);
	}

	void insert(int p, int v) {
		pos.push_back(p);
		val.push_back(v);
	}

	void update_val(int& gval, int& gcnt, int tval, int tcnt = 1) {
		if (gval < tval) {
			gval = tval;
			gcnt = tcnt;
		} else if (gval == tval) {
			gcnt += tcnt;
		}
	}

	void make_tree() {
		n = sz(pos) - 1;
		bit_val.resize(n + 1);
		bit_cnt.resize(n + 1);

		repf (i, 1, n) {
			bit_val[i] = -1;
			rep (k, lowbit(i)) {
				update_val (bit_val[i], bit_cnt[i], val[i - k]);
			}
		}
	}

	pii query(int l, int r) {
		int max_val = -1, cnt = -1;
		while (l <= r) {
			if (r - lowbit(r) + 1 >= l) {
				update_val (max_val, cnt, bit_val[r], bit_cnt[r]);
				r -= lowbit(r);
			} else {
				update_val (max_val, cnt, val[r]);
				r -= 1;
			}
		}
		return pii(max_val, cnt);
	}

	pii query_by_pos(int l, int r) {
		int idx_l = lower_bound(all(pos), l) - pos.begin();
		int idx_r = upper_bound(all(pos), r) - pos.begin() - 1;
		return query(idx_l, idx_r);
	}
};

int test_bit() {
	binary_index_tree bit;
	bit.clear();

	bit.insert (2, 3);
	bit.insert (3, 8);
	bit.insert (5, 8);
	bit.insert (8, 9);
    
    bit.make_tree();

    printf ("query %d %d -> %d %d\n", 1, 1, bit.query_by_pos(1, 1).first, bit.query_by_pos(1, 1).second);
	printf ("query %d %d -> %d %d\n", 9, 9, bit.query_by_pos(9, 9).first, bit.query_by_pos(9, 9).second);
	printf ("query %d %d -> %d %d\n", 1, 8, bit.query_by_pos(1, 8).first, bit.query_by_pos(1, 8).second);
	printf ("query %d %d -> %d %d\n", 3, 5, bit.query_by_pos(3, 5).first, bit.query_by_pos(3, 5).second);
	printf ("query %d %d -> %d %d\n", 2, 3, bit.query_by_pos(2, 3).first, bit.query_by_pos(2, 3).second);
}

const int MAXN = 100000 + 10;
const int MAXP = 9595;

bool non_prime[MAXN];
int prime[MAXP], p_cnt = 0;
binary_index_tree bit[MAXP];

void gen_prime() {
	repf (i, 2, MAXN - 1) {
		if (!non_prime[i]) {
			prime[p_cnt++] = i;
			for (int j = (i << 1); j < MAXN; j += i) {
				non_prime[j] = true;
			}
		}
	}
}

vector<int> divide(int x) {
	vector<int> res;
	for (int i = 0; prime[i] * prime[i] <= x; ++i) {
		if (x % prime[i] == 0) {
			x /= prime[i];
			res.push_back (i);
			while (x % prime[i] == 0) {
				x /= prime[i];
			}
			if (x == 1) {
				break ;
			}
		}
	}
	if (x != 1) {
		res.push_back (lower_bound(prime, prime + p_cnt, x) - prime);
	}
	return res;
}

int n, m;

void clear_bit() {
	rep (i, p_cnt) {
		bit[i].clear ();
	}
}

void init_bit() {
	rep (i, n) {
		int num;
		scanf ("%d", &num);
		vector<int> dvec = divide(num);
		repeach (it, dvec) {
			bit[*it].insert (i + 1, num);
		}
	}
}

void make_bit() {
	rep (i, p_cnt) {
		bit[i].make_tree ();
	}
}

void query_bit() {
	rep (i, m) {
		int G, l, r;
		scanf ("%d%d%d", &G, &l, &r);
		vector<int> dvec = divide(G);
		pii res = pii(-1, -1);
		repeach (it, dvec) {
			pii cres = bit[*it].query_by_pos (l, r);
			ckmax (res, cres);
		}
		printf ("%d %d\n", res.first, res.second);
	}
}

int main() {
    // test_bit();

    gen_prime ();

    while (scanf ("%d%d", &n, &m) != EOF) {
    	clear_bit ();
    	init_bit ();
    	make_bit ();
    	query_bit ();
    }

    return 0;
}
