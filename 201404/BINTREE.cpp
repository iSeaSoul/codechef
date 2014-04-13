#include <cstdio>

int level(int x) {
	return x == 1? 1 : level(x >> 1) + 1;
}

int solve(int x, int y) {
	if (x == y) return 0;
	int level_x = level(x), level_y = level(y);
	if (level_x == level_y) {
		return solve(x >> 1, y >> 1) + 2;
	}
	if (level_x > level_y) {
		return solve(x >> 1, y) + 1;
	}
	return solve(x, y >> 1) + 1;
}

int main() {
	int t, x, y; 
	for (scanf ("%d", &t); t; --t) {
		scanf ("%d%d", &x, &y);
		printf ("%d\n", solve(x, y));
	}
	return 0;
}