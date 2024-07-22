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

const int LOG = 30;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<vi> up(n, vi(LOG));
    for (int u = 0; u < n; u++) {
        int v;
        cin >> v;
        v--;
        up[u][0] = v;
    }

    for (int j = 1; j < LOG; j++) {
        for (int u = 0; u < n; u++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }
    }

    while (q--) {
        int u, k;
        cin >> u >> k;
        u--;
        for (int j = 0; j < LOG; j++) {
            if (k & (1 << j)) {
                u = up[u][j];
            }
        }
        cout << u + 1 << "\n";
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