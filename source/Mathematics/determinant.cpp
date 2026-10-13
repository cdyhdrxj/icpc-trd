int det () {
  int sign = 1;
  for (int i = 0; i < n; i++) {
    int row = i;
    while (row < n && !m[row][i]) row++;
    if (row == n) return 0; // Is it really zero ?
    if (row != i) {
      sign *= -1;
      for (int j = 0; j < n; j++)
        swap (m[i][j], m[row][j]);
    }
    for (int j = 0; j < n; j++) {
      if (j == i) continue;
      int mul = mult (m[j][i], binpow (m[i][i], MOD - 2));
      mul = mult (mul, MOD - 1);
      for (int l = 0; l < n; l++)
        add (m[j][l], mult (m[i][l], mul));
    }
  }
  int res = (MOD + sign) % MOD;
  for (int i = 0; i < n; i++)
    res = mult (res, m[i][i]);
  return res;
}