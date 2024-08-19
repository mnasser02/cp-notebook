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
struct mat {
    vector<vll> a;
    mat() : a(6, vll(6)) {}

    mat operator*(const mat& b) const {
        mat res;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                for (int k = 0; k < 6; k++) {
                    res.a[i][j] += a[i][k] * b.a[k][j];
                    res.a[i][j] %= M;
                }
            }
        }
        return res;
    }
};

mat mod_pow(mat b, ll p) {
    mat ans;
    for (int i = 0; i < 6; i++) ans.a[i][i] = 1;

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
    ll n;
    cin >> n;
    mat b;
    b.a = {{1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 0}};

    mat res = mod_pow(b, n);

    cout << res.a[0][0] << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    // cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}
