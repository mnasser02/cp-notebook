ll rho(ll n, ll c) {
    ll x = 2, y = 2, i = 1, k = 2, d;
    while (true) {
        x = mult(x, x, n) + c;
        if (x >= n) x -= n;
        d = gcd(x - y, n);
        if (d > 1) return d;
        if (++i == k) y = x, k <<= 1;
    }
    return n;
}
void pollard_rho(ll n, vll& f) {  // O(n^1/4)
    if (n == 1)
        return;

    if (is_prime(n)) {
        f.push_back(n);
        return;
    }
    ll d = n;
    for (int i = 2; d == n; i++) {
        d = rho(n, i);
    }
    pollard_rho(d, f);
    pollard_rho(n / d, f);
}
