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
