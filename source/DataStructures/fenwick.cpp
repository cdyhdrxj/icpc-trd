// прибавление в элементе
void add(int pos, int x) {
	for (++pos; pos <= n; pos += pos & (-pos)) {
		tF[pos] += x;
	}
}

// сумма на префиксе до r включительно
int sumpref(int r) {
	int sum = 0;
	for (++r; r > 0; r -= r & (-r)) {
		sum += tF[r];
	}
	return sum;
}

// поиск префикса, на котором сумма больше либо равна sum
int binsearch(int sum) {
	int mask = 0;
	for (int k = log[n]; k >= 0; --k) {
		if (mask + (1 << k) <= n && tF[mask + (1 << k)] < sum) {
			sum -= tF[mask + (1 << k)];
			mask += (1 << k);
		}
	}
	return mask;
}

// изменение на отрезке, значение элемента
void query_add() {
	int l, r, x;
	cin >> l >> r >> x;
	--l; --r;
	add(l, x);
	add(r + 1, -x);
}

void solve() {
	cin >> n;
	vector <int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	vector <int> da(n);
	da[0] = a[0];
	for (int i = 1; i < n; ++i) {
		da[i] = a[i] - a[i - 1];
	}
 
	tF.resize(n + 1);
	for (int i = 0; i < n; ++i) {
		add(i, da[i]);
	}
}