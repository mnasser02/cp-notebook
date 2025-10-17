const int N = 3e5 + 10;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
struct StringHash {
    const int p, M;
    int P[N], iP[N];

    StringHash(int _M) : p(uniform_int_distribution<int>(0, _M - 1)(rng)), M(_M) {
        P[0] = 1;
        for (int i = 1; i < N; i++) P[i] = (ll)P[i - 1] * p % M;
        iP[N - 1] = minv(P[N - 1], M);
        for (int i = N - 2; i >= 0; i--) iP[i] = (ll)iP[i + 1] * p % M;
    }

    vi hash(const string& s) {
        int n = s.size();
        vi h(n);
        for (int i = 0; i < n; i++) {
            h[i] = (ll)P[i] * s[i] % M;
            if (i) h[i] += h[i - 1], h[i] %= M;
        }
        return h;
    }

    int get(vi& h, int l, int r) {
        if (l == 0) return h[r];
        return (ll)(h[r] - h[l - 1] + M) % M * iP[l] % M;
    }
} sh(1e9 + 7);
