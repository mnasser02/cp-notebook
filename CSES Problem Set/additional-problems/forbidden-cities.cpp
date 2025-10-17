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

struct BCC {
    vector<vi>&AL, comps;
    vi num, low, art, id;
    int n, timer, c;
    stack<int> stk;
    BCC(vector<vi>& AL_) : AL(AL_) {
        n = AL.size();
        num.resize(n);
        low.resize(n);
        art.resize(n);
        id.resize(n);
        timer = 0, c = 0;
        dfs(0, -1);
    }

    void dfs(int u, int p) {
        num[u] = low[u] = ++timer;
        stk.push(u);
        for (int v : AL[u]) {
            if (v == p) continue;
            if (num[v]) {
                ckmin(low[u], num[v]);
            } else {
                dfs(v, u);
                ckmin(low[u], low[v]);
                if (low[v] >= num[u]) {
                    comps.push_back({u});
                    art[u] = num[u] > 1 || num[v] > 2;
                    while (comps[c].back() != v) {
                        comps[c].push_back(stk.top());
                        stk.pop();
                    }
                    c++;
                }
            }
        }
    }

    vector<vi> get_tree() {
        vector<vi> t;
        int i = 0;
        for (int u = 0; u < n; u++) {
            if (art[u]) {
                id[u] = i++;
                t.push_back({});
            }
        }
        for (auto& comp : comps) {
            int cur = i++;
            t.push_back({});
            for (int u : comp) {
                if (art[u]) {
                    t[id[u]].push_back(cur);
                    t[cur].push_back(id[u]);
                } else {
                    id[u] = cur;
                }
            }
        }
        return t;
    }
};

struct LCA {
    vector<vi>&AL, up;
    vi d;
    int n, log;

    LCA(vector<vi>& AL_) : AL(AL_) {
        n = AL.size();
        d.resize(n);
        log = log2(n) + 2;
        up.assign(n, vi(log));
        dfs(0, -1);
    }
    void dfs(int u, int p) {
        for (int v : AL[u]) {
            if (v == p) continue;
            d[v] = d[u] + 1;
            up[v][0] = u;
            for (int j = 1; j < log; j++) {
                up[v][j] = up[up[v][j - 1]][j - 1];
            }
            dfs(v, u);
        }
    }
    int get(int u, int v) {
        if (d[u] < d[v]) swap(u, v);
        int k = d[u] - d[v];
        int dist = 0;
        for (int j = 0; j < log; j++) {
            if (k & (1 << j)) {
                u = up[u][j];
                dist += 1 << j;
            }
        }

        if (u == v) return dist;

        for (int j = log - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
                dist += 1 << (j + 1);
            }
        }
        return dist + 2;
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vi> AL(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }
    BCC bcc(AL);
    vector<vi> bct = bcc.get_tree();
    LCA lca(bct);

    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--, c--;
        if (a == c || b == c) {
            cout << "NO\n";
            continue;
        }
        int pc = c;
        a = bcc.id[a], b = bcc.id[b], c = bcc.id[c];
        bool ok = !bcc.art[pc] || lca.get(a, b) != lca.get(a, c) + lca.get(c, b);

        cout << (ok ? "YES\n" : "NO\n");
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