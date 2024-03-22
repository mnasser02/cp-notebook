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
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> os_tree;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    ll AM[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                AM[i][j] = 0;
            else
                AM[i][j] = 1e15;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        AM[u][v] = min(AM[u][v], (ll)w);
        AM[v][u] = min(AM[v][u], (ll)w);
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
            }
        }
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        ll d = AM[u][v];
        if (d == 1e15) {
            cout << "-1\n";
        } else {
            cout << d << "\n";
        }
    }
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
