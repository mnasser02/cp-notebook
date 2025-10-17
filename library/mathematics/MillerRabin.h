ll mult(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}
ll mod_pow(ll b, ll p, ll mod) {
    ll ans = 1;
    while (p) {
        if (p & 1) ans = mult(ans, b, mod);
        b = mult(b, b, mod);
        p >>= 1;
    }
    return ans;
}
bool is_prime(ll n, int trials = 5) {
    if (n == 2) return 1;
    if (n < 2 || !(n & 1)) return 0;

    ll q = n - 1;
    int k = 0, b = 0;
    while (!(q & 1)) {
        q >>= 1;
        k++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        // ll a = rand() % (n - 4) + 2;
        if (n == a) {
            return 1;  //
        }

        ll t = mod_pow(a, q, n);
        bool ok = (t == 1) || (t == n - 1);
        if (ok) continue;

        for (int i = 1; i < k; i++) {
            t = mult(t, t, n);
            if (t == n - 1) {
                ok = 1;
                break;
            }
        }
        if (!ok)
            return 0;
    }
    return 1;
}
