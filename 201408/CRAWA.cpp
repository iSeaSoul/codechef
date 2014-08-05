// Rain Dreamer MODEL
// iSea @ 2014-08-01 18:47
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

bool check(int x, int y) {
	if (x == 0 && y == 0) {
		return true;
	}
	// up
	if (y > 0 && y % 2 == 0) {
		int left = -y, right = y - 1;
		if (x >= left && x <= right) {
			return true;
		}
	}
	// down
	if (y < 0 && y % 2 == 0) {
		int left = y, right = 1 - y;
		if (x >= left && x <= right) {
			return true;
		}
	}
	// left
	if (x < 0 && x % 2 == 0) {
		int left = x, right = -x;
		if (y >= left && y <= right) {
			return true;
		}
	}
	// right
	if (x > 0 && x % 2 == 1) {
		int left = 1 - x, right = 1 + x;
		if (y >= left && y <= right) {
			return true;
		}
	}
	return false;
}

int main() {
	repcase {
		int x, y;
		scanf ("%d%d", &x, &y);
		puts (check(x, y)? "YES" : "NO");
	}
	return 0;
}