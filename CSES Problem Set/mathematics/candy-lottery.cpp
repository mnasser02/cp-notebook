#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

ld C[101][101];
void solve() {
    int n, k;
    cin >> n >> k;

    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= n; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    ld exp = 1.0;
    for (ld mx = 2; mx <= k; mx++) {
        for (int i = 1; i <= n; i++) {
            exp += C[n][i] * mx * powl(mx - 1, n - i);
        }
    }
    exp /= powl(k, n);

    cout << fixed << setprecision(6) << exp << "\n";
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
