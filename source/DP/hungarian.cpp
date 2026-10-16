// Вход:  a — матрица стоимостей n x n (a[i][j] = цена назначить i-го на j-го).
// Выход: пара {минимальная сумма, ans}, где ans[i] — столбец (1..n) для строки i.
// O(n^3)
pair<int, vector<int>> hungarian(const vector<vector<int>>& a) {
    int n = a.size();
    vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
    // u, v — потенциалы; p[j] — какая строка назначена столбцу j; way — для восстановления.
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(n + 1, INF);
        vector<bool> used(n + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1 = 0;
            for (int j = 1; j <= n; ++j)
                if (!used[j]) {
                    int cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta) delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= n; ++j)
                if (used[j]) u[p[j]] += delta, v[j] -= delta;
                else         minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {                       // перекрашиваем цепочку
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    vector<int> ans(n + 1);
    for (int j = 1; j <= n; ++j) ans[p[j]] = j;
    return {-v[0], ans};           // -v[0] = сумма стоимостей
}
