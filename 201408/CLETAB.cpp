// Rain Dreamer MODEL
// iSea @ 2014-08-02 13:45
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
#include <deque>
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

const int MAXN = 400 + 10;

deque<int> pos[MAXN];
set<int> cache;
int n, m, a[MAXN];

int main() {
	repcase {
		scanf ("%d%d", &n, &m);
		rep (i, m) {
			scanf ("%d", &a[i]);
			pos[a[i]].push_back(i);
		}
		cache.clear();
		int res = 0;
		rep (i, m) {
			pos[a[i]].pop_front();
			
			if (cache.find(a[i]) != cache.end()) {
				continue;
			}
			if (sz(cache) == n) {
				int max_next_pos = i;
				int max_np_id;

				repeach (it, cache) {
					if (sz(pos[*it]) == 0) {
						max_next_pos = m;
						max_np_id = *it;
					} else if (pos[*it][0] > max_next_pos) {
						max_next_pos = pos[*it][0];
						max_np_id = *it;
					}
				}
				cache.erase(max_np_id);
			}
			cache.insert(a[i]);
			res++;
		}
		printf ("%d\n", res);
	}
	return 0;
}