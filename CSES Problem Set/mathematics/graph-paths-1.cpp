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

const int M = 1e9 + 7;
int n;
struct mat {
    vector<vll> a;
    mat(int n) : a(n, vll(n)) {}

    mat operator*(const mat& b) const {
        mat res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    res.a[i][j] += a[i][k] * b.a[k][j];
                    res.a[i][j] %= M;
                }
            }
        }
        return res;
    }
};

mat mod_pow(mat b, ll p) {
    mat ans(n);
    for (int i = 0; i < n; i++) ans.a[i][i] = 1;

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
    mat a(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        a.a[u][v]++;
    }
    mat res = mod_pow(a, k);
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
