int t[MAXN][MAXN], a[MAXN][MAXN];
void add(int x, int y, int d) {
	for(int i = x; i <= n; i += i & -i)
		for(int j = y; j <= n; j += j & -j)
			t[i][j] += d;
}

int sum(int x, int y) {
	int res = 0;
	for(int i = x; i > 0; i -= i & -i)
		for(int j = y; j > 0; j -= j & -j)
			res += t[i][j];
	return res;
}

int sum(int x, int y, int X, int Y) {
	return sum(X, Y) - sum(x, Y) - sum(X, y) + sum(x, y)
}