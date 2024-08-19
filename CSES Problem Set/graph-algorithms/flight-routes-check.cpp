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
    vector<vi> AL(n), ALr(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        ALr[v].push_back(u);
    }

    vector<vi> vis(2, vi(n));
    auto dfs = [&](auto self, int u, int d, vector<vi>& AL) -> void {
        vis[d][u] = 1;
        for (int v : AL[u]) {
            if (!vis[d][v]) self(self, v, d, AL);
        }
    };

    dfs(dfs, 0, 0, AL);
    dfs(dfs, 0, 1, ALr);

    for (int u = 0; u < n; u++) {
        if (!vis[0][u]) {
            cout << "NO\n";
            cout << 1 << " " << u + 1 << "\n";
            return;
        }
        if (!vis[1][u]) {
            cout << "NO\n";
            cout << u + 1 << " " << 1 << "\n";
            return;
        }
    }

    cout << "YES\n";
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