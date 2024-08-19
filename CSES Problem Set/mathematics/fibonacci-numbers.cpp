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
#define LSOne(S) ((S) & -(S))

const int M = 1e9 + 7;
vector<vll> mul(vector<vll> A, vector<vll> B) {
    vector<vll> ans(2, vll(2));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                ans[i][j] += A[i][k] * B[k][j] % M;
                ans[i][j] %= M;
            }
        }
    }
    return ans;
}

vector<vll> mod_pow(vector<vll> b, ll p) {
    vector<vll> ans = {{1, 0}, {0, 1}};

    while (p) {
        if (p & 1) {
            ans = mul(ans, b);
        }
        p >>= 1;
        b = mul(b, b);
    }
    return ans;
}

void solve() {
    ll n;
    cin >> n;
    vector<vll> fib{{1, 1}, {1, 0}};
    if (n < 2) {
        cout << n << "\n";
        return;
    }
    fib = mod_pow(fib, n - 1);
    cout << fib[0][0] << "\n";
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
