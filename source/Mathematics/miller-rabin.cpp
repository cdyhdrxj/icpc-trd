bool check_prime(ll n) {
    ll m = n - 1, k = 0;
    while (m % 2 == 0) {
        m /= 2;
        k++;
    }
    ll S = 50; // error_prob <= 1/4^S
    for (int i = 0; i < S; i++) {
        ll a = random(1, n - 1);
        ll x = binpow(a, m, n);
        for (int j = 0; j < k; j++) {
            ll y = x * x % n;
            if (y == 1 && x != 1 && x != n - 1)
                return false;
            x = y;
        }
        if (x != 1)
        return false;
    }
    return true;
}