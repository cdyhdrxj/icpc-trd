typedef vector< vector<double> > matrix;

vector<double> gauss(matrix a) {
    int n = (int) a.size();
    for (int i = 0; i < n; i++) {
        // находим опорный элемент
        int best = i;
        for (int j = i + 1; j < n; j++)
            if (abs(a[j][i]) > abs(a[best][i]))
                best = j;
        // меняем строчки местами
        swap(a[best], a[i]);
        // нормализуем i-тую строчку (слева нули, с ними ничего делать не надо)
        for (int j = n; j >= i; j--)
            a[i][j] /= a[i][i];
        // зануляем все остальные ячейки в i-том столбце
        for (int j = 0; j < n; j++)
            if (j != i)
                // слева только нули, так что можно пройтись только по правой части
                for (int k = n; k >= i; k--)
                    a[j][k] -= a[i][k] * a[j][i];
    }
    vector<double> ans(n);
    for (int i = 0; i < n; i++)
        ans[i] = a[i][n];
    return ans;
}