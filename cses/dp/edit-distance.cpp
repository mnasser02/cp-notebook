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

int memo[5001][5001];
string s, t;
int n, m;
int dp(int i, int j) {
    if (i == n && j == m) return 0;

    int &ans = memo[i][j];
    if (ans != -1) return ans;

    if (s[i] == t[j]) {
        ans = dp(i + 1, j + 1);
    } else if (i == n) {
        ans = 1 + dp(i, j + 1);
    } else if (j == m) {
        ans = 1 + dp(i + 1, j);
    } else {
        ans = 1 + min({dp(i, j + 1), dp(i + 1, j), dp(i + 1, j + 1)});
    }
    return ans;
}
void solve() {
    cin >> s >> t;
    n = s.size(), m = t.size();

    memset(memo, -1, sizeof memo);
    cout << dp(0, 0) << "\n";
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
