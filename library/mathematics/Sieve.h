void sieve() {
    // primes <= N
    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i)
                is_prime[j] = false;
        }
    }
}
// useful for O(logn) factorization where n <= 1e7
int spf[N];
void linear_sieve() {
    vi pr;

    for (int i = 2; i < N; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] < N; ++j) {
            spf[i * pr[j]] = pr[j];
            if (pr[j] == spf[i]) {
                break;
            }
        }
    }
}

vii factorize(int x) {
    vii fac;
    while (x > 1) {
        int p = spf[x];
        int j = 0;
        while (x % p == 0) {
            x /= p;
            j++;
        }
        fac.push_back({p, j});
    }
    return fac;
}
// without 1
void gen_divs(const vii& fac, int i, int c, int x, vi& divs) {
    if (i == fac.size()) return;
    auto [p, j] = fac[i];
    if (c < j) {
        divs.push_back(x * p);
        gen_divs(fac, i, c + 1, x * p, divs);
    }
    gen_divs(fac, i + 1, 0, x, divs);
}
