struct Congruence {
    ll a, m;
};
// m_i pairwise coprime
ll CRT(vector<Congruence> const& congruences) {
    ll M = 1;
    for (auto const& congruence : congruences) {
        M *= congruence.m;
    }

    ll sol = 0;
    for (auto const& congruence : congruences) {
        ll a_i = congruence.a;
        ll M_i = M / congruence.m;
        ll N_i = mod_inv(M_i, congruence.m);
        sol = (sol + a_i * M_i % M * N_i) % M;
    }
    return sol;
}
bool handle_prime(ll m_new, int i, ll a, unordered_map<ll, Congruence>& mp) {
    ll a_new = a % m_new;
    if (mp.count(i)) {
        auto [a_old, m_old] = mp[i];
        ll m_min = min(m_old, m_new);
        if (a_old % m_min != a_new % m_min) return 0;
        if (m_new > m_old) mp[i] = {a_new, m_new};

    } else {
        mp[i] = {a_new, m_new};
    }
    return 1;
}
// K = lcm(m_i)
ll CRT_general(vector<Congruence> const& congruences) {
    unordered_map<ll, Congruence> mp;
    for (auto [a, m] : congruences) {
        for (ll i = 2; i * i <= m; i++) {
            ll m_new = 1;
            while (m % i == 0) {
                m_new *= i;
                m /= i;
            }
            if (m_new > 1) {
                if (!handle_prime(m_new, i, a, mp)) return -1;
            }
        }
        if (m != 1) {
            if (!handle_prime(m, m, a, mp)) return -1;
        }
    }
    vector<Congruence> cong_new;
    for (auto [k, c] : mp) {
        cong_new.push_back(c);
    }
    return CRT(cong_new);
}
