#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

int n;
struct mat {
    vector<vll> a;
    bool neut;
    mat(int n, ll x, bool neut = 0) : a(n, vll(n, x)), neut(neut) {}

    mat operator*(const mat& b) const {
        if (neut) return b;
        if (b.neut) return *this;
        mat res(n, 2e18);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    res.a[i][j] = min(res.a[i][j], a[i][k] + b.a[k][j]);
                    // cout << res.a[i][j] << " ";
                }
            }
        }
        return res;
    }
};

mat mod_pow(mat b, ll p) {
    mat ans(n, 0, 1);

    while (p) {
        if (p & 1) {
            ans = ans * b;
        }
        b = b * b;
        p >>= 1;
    }
    return ans;
}

void solve() {
    int m, k;
    cin >> n >> m >> k;
    mat a(n, 2e18);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        a.a[u][v] = min(a.a[u][v], (ll)w);
    }
    mat res = mod_pow(a, k);
    if (res.a[0][n - 1] == 2e18)
        cout << "-1\n";
    else
        cout << res.a[0][n - 1] << "\n";
}

int main() {
    // ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    // cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}
