#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<ll, ll, ll> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

const int M = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    ll dp1 = 1, dp2 = 1;
    for (int i = 2; i <= n; i++) {
        ll tmp1 = dp1;
        dp1 = 4 * dp1 + dp2;
        dp2 = 2 * dp2 + tmp1;
        dp1 %= M, dp2 %= M;
    }
    cout << (dp1 + dp2) % M << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}
