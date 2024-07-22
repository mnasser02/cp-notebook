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

struct TwoSAT {
    vector<vi> AL;
    vector<bool> ans;
    TwoSAT(int n) : AL(2 * n), ans(n) {}

    void add_disj(int a, int b, bool na, bool nb) {
        int u = 2 * a ^ na, v = 2 * b ^ nb;
        AL[u ^ 1].push_back(v);
        AL[v ^ 1].push_back(u);
    }

    bool solve() {
        int n = AL.size();
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
                scc++;
                while (1) {
                    int v = stk.top();
                    stk.pop();
                    id[v] = -scc;
                    in_stk[v] = 0;
                    if (v == u) break;
                }
            }
        };

        for (int u = 0; u < n; u++) {
            if (dfs_num[u] == -1) tarjan(tarjan, u);
        }
        for (int u = 0; u < n; u += 2) {
            if (id[u] == id[u ^ 1]) return false;
            ans[u / 2] = id[u ^ 1] < id[u];
        }
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    TwoSAT sat(m);
    for (int i = 0; i < n; i++) {
        char c1, c2;
        int a, b;
        cin >> c1 >> a >> c2 >> b;
        a--, b--;
        bool na = c1 == '-', nb = c2 == '-';
        sat.add_disj(a, b, na, nb);
    }
    if (!sat.solve()) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (bool x : sat.ans) {
        cout << (x ? '+' : '-') << " ";
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