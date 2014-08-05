// Rain Dreamer MODEL
// iSea @ 2014-07-27 16:00
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

char buf[300010];
string s[300010];
int n;

const int BLEN = 500;

int main() {
	// freopen ("TAEDITOR.in", "r", stdin);
	while (scanf ("%d", &n) != EOF) {
		int cnt = 0;
		s[cnt++] = "";

		while (n--) {
			char op[2];
			int pos, len;
			scanf ("%s%d", op, &pos);
			if (op[0] == '+') {
				scanf ("%s", buf);
				int idx = 0;
				while (idx < cnt - 1 && sz(s[idx]) < pos) {
					pos -= sz(s[idx++]);
				}
				s[idx] = s[idx].substr(0, pos) + string(buf) + s[idx].substr(pos);
				while (sz(s[idx]) > BLEN) {
					for (int i = cnt; i > idx + 1; --i) {
						s[i] = s[i - 1];
					}
					int lenc = sz(s[idx]) - BLEN;
					s[idx + 1] = s[idx].substr(lenc);
					s[idx] = s[idx].substr(0, lenc);
					cnt ++;
				}
			} else {
				scanf ("%d", &len);
				pos --;

				int idx = 0;
				while (idx < cnt - 1 && sz(s[idx]) < pos) {
					pos -= sz(s[idx++]);
				}

				while (sz(s[idx]) - pos < len) {
					printf ("%s", s[idx].substr(pos).c_str());
					pos = 0;
					len -= sz(s[idx]) - pos;
					idx ++;
				}
				printf ("%s\n", s[idx].substr(pos, len).c_str());
			}
		}
	}
		
	return 0;
}