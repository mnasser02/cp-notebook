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
    string s;
    cin >> s;
    vector<vi> AL(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }
    int r = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            r = i;
            break;
        }
    }
    if (r == -1) {
        cout << "0\n";
        return;
    }

    int h = 0;
    auto dfs = [&](auto self, int u, int p) -> int {
        int mx1 = -1, mx2 = -1;
        for (int v : AL[u]) {
            if (v == p) continue;
            int cur = self(self, v, u);
            if (cur > mx1) {
                mx2 = mx1;
                mx1 = cur;
            } else if (cur > mx2) {
                mx2 = cur;
            }
        }
        int l = 1 + mx1, r = 1 + mx2;
        if (s[u] == '0') {
            if (l == 0 && r == 0) return -1;
            if (l && r) ckmax(h, l + r);
        } else
            ckmax(h, l + r);
        return l;
    };

    dfs(dfs, r, -1);
    cout << h << '\n';
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