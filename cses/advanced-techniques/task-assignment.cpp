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
bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}

struct MCMF {
    using F = ll;
    using C = ll;  // flow type, cost type
    struct Edge {
        int u, v;
        F flo, cap;
        C cost;
    };

    int N;
    vector<C> p, dist;
    vi pre;
    vector<Edge> eds;
    vector<vi> adj;

    MCMF(int _N) {
        N = _N;
        p.resize(N), dist.resize(N), pre.resize(N), adj.resize(N);
    }

    void add(int u, int v, F cap, C cost) {
        assert(cap >= 0);
        adj[u].push_back(size(eds));
        eds.push_back({u, v, 0, cap, cost});
        adj[v].push_back(size(eds));
        eds.push_back({v, u, 0, 0, -cost});
    }
    // use asserts, don't try smth dumb
    bool path(int s, int t) {  // find lowest cost path to send flow through
        const C inf = numeric_limits<C>::max();
        for (int i = 0; i < N; i++)
            dist[i] = inf;
        using T = pair<C, int>;
        priority_queue<T, vector<T>, greater<T>> todo;
        todo.push({dist[s] = 0, s});
        while (size(todo)) {  // Dijkstra
            T x = todo.top();
            todo.pop();
            if (x.first > dist[x.second]) continue;
            for (auto e : adj[x.second]) {
                const Edge& E = eds[e];  // all weights should be non-negative
                if (E.flo < E.cap && ckmin(dist[E.v], (x.first + E.cost + p[x.second] - p[E.v])))
                    pre[E.v] = e, todo.push({dist[E.v], E.v});
            }
        }  // if costs are doubles, add some EPS so you
        // don't traverse ~0-weight cycle repeatedly
        return dist[t] != inf;  // return flow
    }

    pair<F, C> calc(int s, int t) {
        assert(s != t);
        for (int i = 0; i < N; i++)
            for (int e = 0; e < size(eds); e++) {
                const Edge& E = eds[e];  // Bellman-Ford
                if (E.cap) ckmin(p[E.v], p[eds[e ^ 1].v] + E.cost);
            }
        F totFlow = 0;
        C totCost = 0;
        while (path(s, t)) {  // p -> potentials for Dijkstra
            for (int i = 0; i < N; i++)
                p[i] += dist[i];  // don't matter for unreachable nodes
            F df = numeric_limits<F>::max();
            for (int x = t; x != s; x = eds[pre[x] ^ 1].v) {
                const Edge& E = eds[pre[x]];
                ckmin(df, E.cap - E.flo);
            }
            totFlow += df;
            totCost += (p[t] - p[s]) * df;
            for (int x = t; x != s; x = eds[pre[x] ^ 1].v)
                eds[pre[x]].flo += df, eds[pre[x] ^ 1].flo -= df;
        }  // get max flow you can send along path
        return {totFlow, totCost};
    }
    vii get_edges() {
        vii res;
        for (auto e : eds) {
            if (e.flo > 0 && e.cost)
                res.push_back({e.u, e.v});
        }
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    MCMF mf(2 * n + 2);
    int src = 0, sink = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        mf.add(src, i, 1, 0);
        mf.add(n + i, sink, 1, 0);
        for (int j = n + 1; j <= 2 * n; j++) {
            int cost;
            cin >> cost;
            mf.add(i, j, 1, cost);
        }
    }
    cout << mf.calc(src, sink).second << "\n";
    for (auto [u, v] : mf.get_edges()) {
        cout << u << " " << v - n << "\n";
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