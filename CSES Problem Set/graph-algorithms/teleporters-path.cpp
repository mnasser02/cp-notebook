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
    vector<vi> AL(n);
    vi in(n), out(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        in[v]++, out[u]++;
    }
    for (int u = 1; u < n - 1; u++) {
        if (in[u] != out[u]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    if (out[0] != in[0] + 1 || in[n - 1] != out[n - 1] + 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    vi ans;
    auto hierholzer = [&](int s) {
        vi idx(n, 0), st;
        st.push_back(s);
        while (!st.empty()) {
            int u = st.back();
            if (idx[u] < (int)AL[u].size()) {
                st.push_back(AL[u][idx[u]]);
                ++idx[u];
            } else {
                ans.push_back(u);
                st.pop_back();
            }
        }
        reverse(ans.begin(), ans.end());
    };
    hierholzer(0);
    if (ans.size() < m + 1)
        cout << "IMPOSSIBLE\n";
    else
        for (int x : ans) cout << x + 1 << " ";
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