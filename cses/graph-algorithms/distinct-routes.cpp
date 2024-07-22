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

using edge = array<ll, 3>;
const ll INF = 1e18;

struct max_flow {
    int n;
    vector<edge> EL;
    vector<vi> AL;
    vi d, last;
    vii p;
    bool bfs(int s, int t) {
        d.assign(n, -1);
        d[s] = 0;
        queue<int> q({s});
        p.assign(n, {-1, -1});
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) break;
            for (auto& id : AL[u]) {
                auto& [v, cap, flow] = EL[id];
                if (cap - flow > 0 && d[v] == -1)
                    d[v] = d[u] + 1, q.push(v), p[v] = {u, id};
            }
        }
        return d[t] != -1;
    }
    ll dfs(int u, int t, ll f = INF) {
        if ((u == t) || (f == 0)) return f;
        for (int& i = last[u]; i < AL[u].size(); i++) {
            auto& [v, cap, flow] = EL[AL[u][i]];
            if (d[v] != d[u] + 1) continue;
            if (ll pushed = dfs(v, t, min(f, cap - flow))) {
                flow += pushed;
                auto& rflow = EL[AL[u][i] ^ 1][2];
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    max_flow(int n_) : n(n_) {
        EL.clear();
        AL.assign(n, vi());
    }
    void add_edge(int u, int v, ll w, bool directed = true) {
        if (u == v) return;
        EL.push_back({v, w, 0});
        AL[u].push_back(EL.size() - 1);
        EL.push_back({u, directed ? 0 : w, 0});
        AL[v].push_back(EL.size() - 1);
    }
    ll dinic(int s, int t) {
        ll mf = 0;
        while (bfs(s, t)) {
            last.assign(n, 0);
            while (ll f = dfs(s, t)) mf += f;
        }
        return mf;
    }
    vector<set<int>> build() {
        vector<set<int>> res(n);
        for (int u = 0; u < n; u++) {
            for (int id : AL[u]) {
                auto& [v, cap, flow] = EL[id];
                if (flow > 0) {
                    res[u].insert(v);
                }
            }
        }
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    max_flow mf(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        mf.add_edge(u, v, 1);
    }
    cout << mf.dinic(0, n - 1) << "\n";

    auto AL = mf.build();
    vector<vi> ans;
    while (!AL[0].empty()) {
        int u = 0;
        ans.push_back(vi());
        while (u != n - 1) {
            ans.back().push_back(u);
            auto it = AL[u].begin();
            int v = *it;
            AL[u].erase(it);
            u = v;
        }
        ans.back().push_back(n - 1);
    }
    for (auto& v : ans) {
        cout << v.size() << "\n";
        for (int x : v) cout << x + 1 << " ";
        cout << "\n";
    }
}

int main() {
    // ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    // cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}