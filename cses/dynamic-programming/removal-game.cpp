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

ll memo[5001][5001];
int n;
vi x;

ll dp(int l, int r) {
    if (l == r) {
        return x[l];
    }

    ll &ans = memo[l][r];
    if (ans != -1) return ans;

    return ans = max(x[l] - dp(l + 1, r), x[r] - dp(l, r - 1));
}
void solve() {
    cin >> n;
    x.resize(n);
    ll tot = 0;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        tot += x[i];
    }
    memset(memo, -1, sizeof memo);

    cout << (tot + dp(0, n - 1)) / 2 << "\n";
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
