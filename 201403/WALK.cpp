#include <cstdio>

int main() {
	int t, n, k; 
	int *speed = new int[100010];

	for (scanf ("%d", &t); t; --t) {
		scanf ("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf ("%d", &speed[i]);
		}
		int res = speed[n - 1];
		for (int i = n - 2; i >= 0; --i) {
			res = res + 1 >= speed[i]? res + 1 : speed[i];
		}
		printf ("%d\n", res);
	}
	return 0;
}