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
    int n, m;
    cin >> n >> m;
    vector<vi> cost(m, vi(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> cost[j][i];
        }
    }

    vector<vll> mem(m, vll(1 << n, -1));
    auto dp = [&](auto self, int bm, int i) -> ll {
        if (i == m) {
            return bm == (1 << n) - 1 ? 0 : 1e18;
        }
        ll& ans = mem[i][bm];
        if (ans != -1) return ans;

        ans = 1e18;
        for (int j = 0; j < n; j++) {
            ckmin(ans, self(self, bm ^ (1 << j), i + 1) + cost[i][j]);
        }
        return ans;
    };

    vector<vi> sgn(n);
    auto path = [&](auto self, int bm, int i) -> void {
        if (i == m) return;
        for (int j = 0; j < n; j++) {
            if (dp(dp, bm, i) == dp(dp, bm ^ (1 << j), i + 1) + cost[i][j]) {
                self(self, bm ^ (1 << j), i + 1);
                sgn[j].push_back(i);
                return;
            }
        }
    };

    cout << dp(dp, 0, 0) << '\n';
    path(path, 0, 0);
    for (int i = 0; i < n; i++) {
        cout << sgn[i].size() << ' ';
        for (int x : sgn[i]) cout << x + 1 << ' ';
        cout << '\n';
    }
}

int main() {
    freopen("mercato.in", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}