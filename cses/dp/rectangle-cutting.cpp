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

int memo[501][501];
int dp(int a, int b) {
    if (a == b) {
        return 0;
    }
    int &ans = memo[a][b];
    if (ans != -1) return ans;
    ans = 1e9;
    for (int x = 1; x < a; x++) {
        ans = min(ans, 1 + dp(x, b) + dp(a - x, b));
    }
    for (int x = 1; x < b; x++) {
        ans = min(ans, 1 + dp(a, x) + dp(a, b - x));
    }
    memo[b][a] = ans;
    return ans;
}
void solve() {
    int a, b;
    cin >> a >> b;
    memset(memo, -1, sizeof memo);
    cout << dp(a, b) << "\n";
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
