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
    vll C(n), C2;

    for (int i = 0; i < n; i++) {
        cin >> C[i];
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
    }

    vi in_stk(n), dfs_low(n), dfs_num(n, -1), id(n);
    int scc = 0, ctr = 0;
    stack<int> stk;
    auto tarjan = [&](auto self, int u) -> void {
        dfs_low[u] = dfs_num[u] = ctr++;
        in_stk[u] = 1;
        stk.push(u);
        for (int v : AL[u]) {
            if (dfs_num[v] == -1) self(self, v);
            if (in_stk[v])
                ckmin(dfs_low[u], dfs_low[v]);
        }

        if (dfs_low[u] == dfs_num[u]) {
            while (1) {
                int v = stk.top();
                stk.pop();
                id[v] = scc;
                in_stk[v] = 0;
                if (v == u) break;
                C[u] += C[v];
            }
            scc++;
            C2.push_back(C[u]);
        }
    };

    for (int u = 0; u < n; u++) {
        if (dfs_num[u] == -1) tarjan(tarjan, u);
    }

    vector<vi> AL2(n);
    set<ii> st;
    for (int u = 0; u < n; u++) {
        for (int v : AL[u]) {
            if (st.count({id[u], id[v]}) || id[u] == id[v]) continue;
            AL2[id[u]].push_back(id[v]);
        }
    }

    vll dp(scc, -1);
    auto dfs = [&](auto self, int u) -> ll {
        ll& ans = dp[u];
        if (ans != -1) return ans;
        ans = 0;
        for (int v : AL2[u]) {
            ckmax(ans, self(self, v));
        }
        ans += C2[u];
        return ans;
    };

    ll ans = 0;
    for (int u = 0; u < scc; u++) {
        ckmax(ans, dfs(dfs, u));
    }

    cout << ans << "\n";
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