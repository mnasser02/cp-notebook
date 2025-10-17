struct query {
    int u, v;
    bool joined = 0;
    query(int u_, int v_) : u(u_), v(v_) {}
};

struct QueryTree {
    DSU dsu;
    vector<vector<query>> tree;
    vi ans;

    QueryTree(int n, int q) : dsu(n), tree(4 * q + 5), ans(q) {}

    void insert(int p, int l, int r, int i, int j, query qr) {
        if (i <= l && r <= j) {
            tree[p].push_back(qr);
            return;
        }
        if (l > j || r < i) return;
        int m = l + r >> 1;
        insert(p << 1, l, m, i, j, qr);
        insert(p << 1 | 1, m + 1, r, i, j, qr);
    }

    void dfs(int p, int l, int r) {
        for (query& qr : tree[p]) {
            qr.joined = dsu.join(qr.u, qr.v);
        }

        if (l == r) {
            ans[l] = dsu.cc;
        } else {
            int m = l + r >> 1;
            dfs(p << 1, l, m);
            dfs(p << 1 | 1, m + 1, r);
        }
        for (query qr : tree[p]) {
            if (qr.joined) dsu.rollback();
        }
    }
}