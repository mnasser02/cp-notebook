void solve() {
    int n, m;
    cin >> n >> m;
    vector<vi> AL(n);
    vector<vi> ALr(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        AL[--a].push_back(--b);
        ALr[b].push_back(a);
    }

    vi visit_order;
    vi visit_time(n, 1e9);
    vi visit_parent(n, -1);
    vector<bool> visited(n, false);
    auto dfs = [&](auto self, int at, int prev) {
        if (visited[at]) {
            return;
        }
        visited[at] = true;

        visit_time[at] = visit_order.size();
        visit_order.push_back(at);
        visit_parent[at] = prev;
        for (int next : AL[at]) {
            self(self, next, at);
        }
    };
    dfs(dfs, 0, -1);

    vi dsu_parent(n, -1);
    vi dsu_min(n, 1e9);
    auto find = [&](auto self, int x) {
        if (dsu_parent[x] == -1) {
            return x;
        }
        if (dsu_parent[dsu_parent[x]] != -1) {
            int parent_res = self(self, dsu_parent[x]);
            if (visit_time[parent_res] < visit_time[dsu_min[x]]) {
                dsu_min[x] = parent_res;
            }
            dsu_parent[x] = dsu_parent[dsu_parent[x]];
        }

        return dsu_min[x];
    };

    vi sdom(n, -1);
    for (int i = visit_order.size() - 1; i > 0; i--) {
        int c = visit_order[i];
        for (int from : ALr[c]) {
            int find_res = find(find, from);
            if (sdom[c] == -1 || visit_time[find_res] < visit_time[sdom[c]]) {
                sdom[c] = find_res;
            }
        }

        dsu_parent[c] = visit_parent[c];
        dsu_min[c] = sdom[c];
    }

    vii sdom_times(n, {1e9, -1});
    for (int c : visit_order) {
        if (c != 0) {
            sdom_times[c] = {visit_time[sdom[c]], c};
        }
    }
    // LCA only straight path and don't include last node in min
    LCA lca(visit_parent, sdom_times);

    vi rdom(n, -1);
    for (int c : visit_order) {
        if (c != 0) {
            rdom[c] = lca.get(sdom[c], c).second;
        }
    }

    vi idom(n, -1);
    for (int c : visit_order) {
        if (c != 0) {
            idom[c] = rdom[c] == c ? sdom[c] : idom[rdom[c]];
        }
    }
}