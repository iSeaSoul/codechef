#include <cstdio>

int end[555], n, m;

int main() {
    freopen ("TANGDIV.in", "r", stdin);
	int t;
	for (scanf ("%d", &t); t; --t) {
		scanf ("%*d%d%d", &n, &m);
		for (int i = 0; i < n; ++i) {
			scanf ("%*d%d", &end[i]);
		}
		bool all_found = true;
		for (int i = 0; i < m; ++i) {
			int c_end;
			scanf ("%*d%d", &c_end);
			bool can_found = false;
			for (int j = 0; j < n; ++j) {
				if (end[j] == c_end) {
					can_found = true;
					break;
				}
			}
			all_found &= can_found;
		}
		puts (all_found? "Yes" : "No");
	}
	return 0;
}
