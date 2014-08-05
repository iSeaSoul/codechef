// Rain Dreamer MODEL
// iSea @ 2014-07-27 15:02
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
// char s[300010], s2[300010];
// string str;
int n, clen;

int main() {
	while (scanf ("%d", &n) != EOF) {
		// str = "";
		s[clen = 0] = 0;
		while (n--) {
			char op[2];
			int pos, len;
			scanf ("%s%d", op, &pos);
			if (op[0] == '+') {
				scanf ("%s", buf);
				// int blen = strlen(buf);
				// memcpy (s2, s + pos, clen - pos);
				// memcpy (s + pos, buf, blen);
				// memcpy (s + pos + blen, s2, clen - pos);
				// clen += blen;
				// str = str.substr(0, pos) + string(buf) + str.substr(pos);
				str.insert (pos, buf);
			} else {
				scanf ("%d", &len);
				// char tmp = s[pos + len - 1];
				// s[pos + len - 1] = 0;
				// puts (s + pos - 1);
				// s[pos + len - 1] = tmp;
				puts (str.substr(pos - 1, len).c_str());
			}
		}
	}
	return 0;
}