/*
 * Not the fish.
 * iSea @ 2014-10-04 17:20
 */

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

const int MAXN = 1000000 + 10;

struct suffix_array {

	int wa[MAXN], wb[MAXN], wv[MAXN], wc[MAXN];
	int sa[MAXN], sr[MAXN], height[MAXN];
	
	// sa : [1, n]   sa[i] - the suffix from sa[i] rank i
	// sr : [0, n)   sr[i] - the suffix from i rank sc[i]
	// height : [2, n]  lcp length of sa[i - 1] and sa[i]

	int cmp(int *r, int a, int b, int l) {
		return r[a] == r[b] && r[a + l] == r[b + l];
	}

	// m indicate the size of characters
	// adjust if it's a number string
	
	void da(char *r, int n, int m = 28) {
		int i, j, p, *x = wa, *y = wb, *t;
		for (i = 0; i < m; i++) wc[i] = 0;
		for (i = 0; i < n; i++) wc[x[i] = r[i]]++;
		for (i = 1; i < m; i++) wc[i] += wc[i - 1];
		for (i = n - 1; i >= 0; i--) sa[--wc[x[i]]] = i;
		for (j = 1, p = 1; p < n; j *= 2, m = p) {
			for (p = 0, i = n - j; i < n; i++) y[p++]=i;
			for (i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i] - j;
			for (i = 0; i < n; i++) wv[i] = x[y[i]];
			for (i = 0; i < m; i++) wc[i] = 0;
			for (i = 0; i < n; i++) wc[wv[i]] ++;
			for (i = 1; i < m; i++) wc[i] += wc[i-1];
			for (i = n - 1; i >= 0; i--) sa[--wc[wv[i]]] = y[i];
			for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++){
				x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
			}
		}
	}

	void cal_height(char *r, int n) {
		int i, j, k = 0;
		for (i = 1; i <= n; i++) sr[sa[i]] = i;
		for (i = 0; i < n; height[sr[i++]] = k) {
			for (k ? k-- : 0, j = sa[sr[i] - 1]; r[i + k] == r[j + k]; k++);
		}
	}
	
	// complexity O(n * logn)
	void process(char *r, int n) {
		da(r, n + 1);
		cal_height(r, n);
	}
};

struct persist_st {
	struct node {
		int l, r, val;
	};

	node n[MAXN * 40];
	int r_cnt, N;

	void init(int _n) {
		r_cnt = 0;
		N = _n;
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
	void update_dif(int cur_root, int root) {
		n[cur_root].val = n[root].val + 1;
	}
	int update(int root, int pos) {
		// printf ("update %d %d\n", root, pos);
		int nextR = r_cnt++;
		int resR = nextR;
		update_dif (nextR, root);

		int l = 1, r = N;
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
			update_dif (nextR, root);
		}
		
		// printf ("update root %d\n", resR);
		return resR;
	}
	int get_kth_num_pos(int l_root, int r_root, int cnt) {
		// printf ("query pos %d %d %d\n", l_root, r_root, cnt);
		if (n[r_root].val - n[l_root].val < cnt) {
			return -1;
		}
		int l = 1, r = N;
		while (l != r) {
			// printf ("go %d %d\n", l, r);
			int mid = (l + r) >> 1;
			if (n[n[r_root].l].val - n[n[l_root].l].val >= cnt) {
				l_root = n[l_root].l;
				r_root = n[r_root].l;
				r = mid;
			} else {
				cnt -= n[n[r_root].l].val - n[n[l_root].l].val;
				l_root = n[l_root].r;
				r_root = n[r_root].r;
				l = mid + 1;
			}
		}
		// printf ("query res %d\n", l);
		return l;
	}
	int get_index(int l_root, int r_root, int pos) {
		int cnt = 0;
		int l = 1, r = N;
		while (l != r) {
			int mid = (l + r) >> 1;
			if (pos <= mid) {
				l_root = n[l_root].l;
				r_root = n[r_root].l;
				r = mid;
			} else {
				cnt += (n[n[r_root].l].val - n[n[l_root].l].val);
				l_root = n[l_root].r;
				r_root = n[r_root].r;
				l = mid + 1;
			}
		}
		cnt += n[r_root].val - n[l_root].val;
		return cnt;
	}
};

int plog2[MAXN];

struct RMQ {
	int dp[MAXN][20];

	void init(int* val, int n) {
		for (int i = 1; i <= n; ++i) {
			dp[i][0] = val[i];
		}
		int maxk = plog2[n];
		for (int k = 1; k <= maxk; ++k) {
			for (int i = 1; i + (1 << (k - 1)) <= n; ++i) {
				dp[i][k] = min(dp[i][k - 1], dp[i + (1 << (k - 1))][k - 1]);
			}
		}
	}
	int query(int a, int b) {
		int k = plog2[b - a + 1];
		return min(dp[a][k], dp[b - (1 << k) + 1][k]);
	}
};

persist_st pst;
suffix_array sa;
RMQ rmq;

char s[MAXN];
int root_id[MAXN];
long long psum[MAXN];

int main() {
	repf (i, 1, MAXN - 1) {
		plog2[i] = (int)(log((double)(i)) / log(2.0));
	}

	while (scanf ("%s", s) != EOF) {
		// build sa
		int n = strlen(s);
		rep (i, n) {
			s[i] = (s[i] - 'a') + 2;
		}
		sa.process(s, n);

		// build pst
		pst.init(n);
		root_id[0] = pst.build(1, n);
		repf (i, 1, n) {
			root_id[i] = pst.update(root_id[i - 1], sa.sa[i] + 1);
		}

		// build lcp_rmq
		rmq.init(sa.height, n);

		// build partial sum
		repf (i, 1, n) {
			int num_distinct_substring = n - sa.sa[i] - sa.height[i];
			psum[i] = psum[i - 1] + num_distinct_substring;
			// printf ("%I64d\n", psum[i]);
		}

		int cl = 0, cr = 0, M;
		scanf ("%d", &M);
		while (M--) {
			char op[10];
			long long k;
			int l, r;
			scanf ("%s", op);

			if (strcmp(op, "Select") == 0) {
				scanf ("%lld%d", &k, &r);
				int pos = lower_bound(psum + 1, psum + n + 1, k) - psum;
				k -= psum[pos - 1];

				int anslen = sa.height[pos] + k;
				int L = pos + 1, R = n;
				while (L <= R) {
					int mid = (L + R) >> 1;
					if (rmq.query(pos + 1, mid) >= anslen) {
						L = mid + 1;
					} else {
						R = mid - 1;
					}
				}

				// printf ("getmin %d %d\n", pos, L - 1);
				int cl = pst.get_kth_num_pos(root_id[pos - 1], root_id[L - 1], r);
				int cr = cl + anslen - 1;
				printf ("%d %d\n", cl, cr);
			} else {
				scanf ("%d%d", &l, &r);

				int pos = sa.sr[l - 1];
				int anslen = r - l + 1;

				int L = pos + 1, R = n;
				while (L <= R) {
					int mid = (L + R) >> 1;
					if (rmq.query(pos + 1, mid) >= anslen) {
						L = mid + 1;
					} else {
						R = mid - 1;
					}
				}
				int curr = L - 1;
				L = 1, R = pos - 1;
				while (L <= R) {
					int mid = (L + R) >> 1;
					if (rmq.query(mid + 1, pos) >= anslen) {
						R = mid - 1;
					} else {
						L = mid + 1;
					}
				}
				int curl = R + 1;

				k = psum[curl - 1] + (anslen - sa.height[curl]);
				int rank = pst.get_index(root_id[curl - 1], root_id[curr], l);

				printf ("%lld %d\n", k, rank);
			}
		}
	}
	return 0;
}