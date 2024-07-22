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

const int M = 1e9 + 7;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vi> AM(n, vi(n));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AM[u][v]++;
    }

    vector<vll> memo(n, vll(1 << n, -1));

    auto dp = [&](auto self, int u, int bm) -> ll {
        if (bm == 0) {
            return u == n - 1;
        }
        if (u == n - 1) return 0;
        ll& ans = memo[u][bm];
        if (ans != -1) return ans;

        ans = 0;
        int m = bm;
        while (m) {
            int two_v = LSOne(m);
            int v = __builtin_ctz(two_v);
            if (AM[u][v])
                ans += self(self, v, bm ^ two_v) * AM[u][v];
            ans %= M;
            m ^= two_v;
        }

        return ans;
    };

    cout << dp(dp, 0, ((1 << n) - 1) ^ 1);
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