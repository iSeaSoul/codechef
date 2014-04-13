// Rain Dreamer MODEL
// Create @ 21:19 04-13 2014
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

struct tm_node {
	double MAX_TM;

	clock_t begin;
 
	void init() {
		begin = clock();
	}
 
	bool valid() {
		return 1.0 * (clock() - begin) / CLOCKS_PER_SEC <= MAX_TM;
	}

	void set_TM(double tm) {
		MAX_TM = tm;
	}
} TN;

const int MAXN = 2000 + 10;

int n, k, s, a[MAXN], sum[MAXN], id[MAXN], resid[MAXN];
int64 ans;

void init() {
	TN.init();

	scanf ("%d%d%d", &n, &k, &s);
	repf (i, 1, n) {
		scanf ("%d", &a[i]);
		id[i] = i;
	}
}

int64 judge(int *cid) {
	repf (i, 1, n) {
		sum[i] = sum[i - 1] + a[cid[i]];
	}
	int64 res = 0;
	repf (i, 1, k) {
		if (a[cid[i]] > s) {
			res += s;
		} else {
			int preSum = sum[i - 1];
			int x = upper_bound(sum + i, sum + n + 1, preSum + s) - sum - 1;
			int maxSum = sum[x] - preSum;
			res += s - maxSum;
		}
	}
	return res;
}

bool comp_bigger(int x, int y) {
	return a[x] < a[y];
}

void update_ans() {
	int64 res = judge(id);
	if (res < ans) {
		ans = res;
		memcpy (resid, id, sizeof(int) * (n + 1));
	}
}

void print_ans() {
	repf (i, 1, n) {
		printf ("%d%c", resid[i], i == n? '\n' : ' ');
	}
}

void solve_gen() {
	set<pii> x;
	repf (i, 1, n) x.insert(pii(a[i], i));
	int cursum = 0, cid = 1;
    int st = 1;
	while (cid <= k) {
		int needsum = s - cursum;
		set<pii>::iterator it = x.lower_bound(pii(needsum, -1));
		if (it == x.end()) --it;
		if (needsum < it->first) {
			if (cursum == 0) {
				break ;
			}
            reverse (id + st, id + cid);
            st = cid;
			cursum = 0;
			continue ;
		} else {
			cursum += it->first;
			id[cid++] = it->second;
			x.erase(*it);
		}
	}
	repeach (it, x) {
		id[cid++] = it->second;
	}

	update_ans();
}

void solve() {
	ans = (-1ull) >> 1;

	solve_gen();

	sort (id + 1, id + 1 + n, comp_bigger);
	update_ans();

	int cnt = n;
	while (a[id[cnt]] > s && cnt >= 1) cnt--;
	int fixed = 1;
	while (a[id[cnt]] == s && a[id[fixed]] != a[id[cnt]] && fixed < cnt) {
		swap (id[fixed++], id[cnt--]);
	}

	update_ans();
	int useful_idx = min(k, cnt);
	if (useful_idx <= fixed) {
		print_ans();
		return ;
	}
	
	reverse (id + fixed + 1, id + 1 + useful_idx);
	update_ans();

	while (TN.valid()) {
		//random_shuffle (id + fixed + 1, id + 1 + useful_idx);
		int lim = useful_idx - fixed;
		rep (t, rand() % 100) {
			int x = rand() % lim, y = rand() % lim;
			swap (id[fixed + 1 + x], id[fixed + 1 + y]);
		}
		update_ans();
	}

	print_ans();
}

int main() {

	int CaseNum;
	scanf ("%d", &CaseNum);
	TN.set_TM(0.9 / CaseNum);

	while (CaseNum--) {
		init(); solve();
	}

	return 0;
}
