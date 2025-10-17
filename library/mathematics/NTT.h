// Arbitrary Mod
typedef complex<double> cd;
void fft(vector<cd>& a) {
    int n = size(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<cd> rt(2, 1);  // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        for (int i = k; i < 2 * k; i++) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vi rev(n);
    for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);

    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            for (int j = 0; j < k; j++) {
                auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];
                cd z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}

typedef vector<ll> vll;
template <int mod>
vll convMod(const vll& a, const vll& b) {
    if (a.empty() || b.empty()) return {};
    vll res(size(a) + size(b) - 1);
    int B = 32 - __builtin_clz(size(res)), n = 1 << B, cut = int(sqrt(mod));
    vector<cd> L(n), R(n), outs(n), outl(n);
    for (int i = 0; i < size(a); i++) L[i] = cd((int)a[i] / cut, (int)a[i] % cut);
    for (int i = 0; i < size(b); i++) R[i] = cd((int)b[i] / cut, (int)b[i] % cut);
    fft(L), fft(R);
    for (int i = 0; i < n; i++) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    for (int i = 0; i < size(res); i++) {
        ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
        ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
        res[i] = ((av % mod * cut + bv) % mod * cut + cv) % mod;
    }
    return res;
}
// Mod of the form p=c2^k+1
/*
Already Precomputed Constants
MOD = 998244353    root = 3    inv_root = 332748118    mod_pow = 23    odd_factor = 119
MOD = 132120577    root = 5    inv_root = 52848231     mod_pow = 21    odd_factor = 63
MOD = 7340033      root = 3    inv_root = 2446678      mod_pow = 20    odd_factor = 7
MOD = 786433       root = 10   inv_root = 235930       mod_pow = 18    odd_factor = 3;
*/

const ll mod = 132120577;
const ll root = 5;
const ll inv_root = 52848231;
const int mod_p = 21;
const ll odd_factor = 63;

void NTT(vector<ll>& a, const ll& cur_root) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        if (i < (j ^= bit)) {
            swap(a[i], a[j]);
        }
    }

    for (int len = 2; len <= n; len <<= 1) {
        ll Wn = cur_root;
        for (int i = len; i < n; i <<= 1)
            Wn = (Wn * Wn) % mod;

        for (int i = 0; i < n; i += len) {
            ll W = 1;
            for (int j = 0; j < (len >> 1); j++, W = (W * Wn) % mod) {
                ll even = a[i + j], odd = (W * a[i + j + (len >> 1)]) % mod;
                a[i + j + (len >> 1)] = (even - odd + mod) % mod;
                a[i + j] = (even + odd) % mod;
            }
        }
    }
}

vector<ll> poly_mod_mult(vector<ll>& a, vector<ll>& b) {
    vector<ll> A(a.begin(), a.end()), B(b.begin(), b.end());
    int N = (int)a.size(), M = (int)b.size();
    int n = 1, logN = 0;
    while (n < (N + M)) {
        n <<= 1;
        logN++;
    }
    A.resize(n, 0);
    B.resize(n, 0);

    // Getting roots with cycle exactly n
    ll norm_factor = odd_factor * mod_pow(2, mod_p - logN);
    ll cur_root = mod_pow(root, norm_factor);
    ll cur_inv_root = mod_pow(inv_root, norm_factor);

    NTT(A, cur_root);
    NTT(B, cur_root);
    for (int i = 0; i < n; i++) A[i] = (A[i] * B[i]) % mod;

    NTT(A, cur_inv_root);
    ll invN = mod_inv(n);
    for (auto& x : A) x = (x * invN) % mod;

    return A;
}

void generate_constants(const ll& MOD) {
    auto is_primitve_root = [&](ll x) {
        ll cur = x, N = 1;
        while (++N != MOD - 1) {
            cur = (cur * x) % MOD;
            if (cur == 1) {
                return false;
            }
        }
        return true;
    };
    int r = 2;
    while (!is_primitve_root(r)) {
        r++;
    }
    int p = 0;
    ll cur = MOD - 1, rInv = mod_inv(r);
    while ((cur & 1) == 0) {
        p++;
        cur >>= 1;
    }

    cout << "Prime: " << MOD << '\n';
    cout << "Primitive Root: " << r << '\n';
    cout << "Inverse of Primitive Root: " << rInv << '\n';
    cout << "Highest Power of 2 in (Prime-1): " << p << ' ' << (1ll << p) << '\n';
    cout << "Highest Odd factor of (Prime-1): " << (MOD - 1) / (1ll << p) << '\n';
}
