int maxN = 1001;
int dp[1001][1001][52];
int opt[1001][1001][52];
 
void solve() {
    int n, k; cin >> n >> k;
    vector <int> a(n);
    vector <int> log(n + 1), log1(n + 1);
    log[1] = 0;
    log1[1] = 0;
    for (int i = 2; i <= n; ++i) {
        log[i] = log[i / 2] + 1;
        if (log[i] != log[i - 1]) log1[i] = log[i];
        else log1[i] = log[i] + 1;
    }
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());
 
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
    for (int s = 0; s <= k; ++s) {
        dp[i][j][s] = INF;
        opt[i][j][s] = -1;
    }
 
    for (int i = 0; i < n; ++i) {
        for (int k1 = 0; k1 <= k; ++k1) {
            dp[i][i][k1] = 0;
            opt[i][i][k1] = i;
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int k1 = 1; k1 <= k; ++k1) {
            dp[i][i + 1][k1] = a[i + 1] - a[i];
            opt[i][i + 1][k1] = i;
        }
    }
 
    for (int len = 3; len <= n; ++len)
    for (int l = 0; l + len - 1 < n; ++l) {
        int r = l + len - 1;
        for (int k1 = 1; k1 <= k; ++k1) {
            dp[l][r][k1] = dp[l][r][k1 - 1];
            opt[l][r][k1] = opt[l][r][k1 - 1];
            int opt1, opt2;
            if (r - 1 >= 0) {
                opt1 = opt[l][r - 1][k1];
            }
            else opt1 = 0;
            if (l + 1 < n) {
                opt2 = opt[l + 1][r][k1];
            }
            else opt2 = n - 2;
            for (int m = max(0, opt1); m <= min(opt2, n - 2); ++m) {
                int left = k1 - 1, right = k1 - 1;
                if (dp[l][m][left] + dp[m + 1][r][right] + a[r] - a[m] < dp[l][r][k1]) {
                    dp[l][r][k1] = dp[l][m][left] + dp[m + 1][r][right] + a[r] - a[m];
                    opt[l][r][k1] = m;  
                }
            }
        }
    }
    
    cout << dp[0][n - 1][k] << endl;
}
