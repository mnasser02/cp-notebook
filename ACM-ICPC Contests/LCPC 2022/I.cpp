#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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
#define LSOne(S) ((S) & -(S))

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

void solve() {
    int n;
    cin >> n;
    vi A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    vector<vi> AL(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    vector<vll> dp(n, vll(2, -1));
    auto dfs = [&](auto self, int u, int b, int p) -> ll {
        ll& ans = dp[u][b];
        if (ans != -1) return ans;

        ans = (b ? -1 : 1) * A[u];
        ll add = b ? -1e18 : 1e18;
        for (int v : AL[u]) {
            if (v == p) continue;
            if (b == 0)
                ckmin(add, self(self, v, 1, u));
            else
                ckmax(add, self(self, v, 0, u));
        }
        if (abs(add) == 1e18) add = 0;
        return ans += add;
    };
    ll ans = dfs(dfs, 0, 0, -1);
    if (ans == 0) {
        cout << "Draw\n";
    } else if (ans > 0) {
        cout << "First\n";
    } else {
        cout << "Second\n";
    }
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