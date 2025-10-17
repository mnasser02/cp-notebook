// O(V^2 E)
// A unit network is a network in which for any vertex except // s and t either incoming or outgoing edge is unique and has // unit capacity. This case: O(E * sqrt(V))
// In a more generic settings when all edges have unit
// capacities, but the number of incoming and outgoing edges // is unbounded: O(E * sqrt(E)), O(E * V2/3)
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
};
