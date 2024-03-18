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

vector<vi> AL;
int dp[1 << 20][2];
int dfs(int u, int p, int can) {
    int &ans = dp[u][can];
    if (ans != -1) return ans;
    int sum = 0;
    for (int v : AL[u]) {
        if (v == p) continue;
        sum += dfs(v, u, 1);
    }
    ans = sum;
    if (can) {
        for (int v : AL[u]) {
            if (v == p) continue;
            ans = max(ans, sum - dfs(v, u, 1) + dfs(v, u, 0) + 1);
        }
    }
    return ans;
}
void solve() {
    int n;
    cin >> n;
    AL.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    memset(dp, -1, sizeof dp);
    cout << dfs(0, -1, 1) << "\n";
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
