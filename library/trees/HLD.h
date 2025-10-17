template <class T>
struct HLD {
    vector<vi>& AL;
    vi sz, par, d, id, top;
    SegTree<T> st;
    int ct;

    HLD(vector<vi>& AL_) : AL(AL_), st(AL_.size()) {
        int n = AL.size();
        sz.assign(n, 0);
        par.assign(n, -1);
        d.resize(n);
        id.assign(n, -1);
        top.assign(n, -1);
        ct = -1;
        dfs(0, -1);
        dfs_hld(0, -1, 0);
    }

    void dfs(int u, int p) {
        sz[u] = 1;
        for (int v : AL[u]) {
            if (v == p) continue;
            d[v] = d[u] + 1;
            par[v] = u;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    void dfs_hld(int u, int p, int t) {
        id[u] = ++ct;
        top[u] = t;
        int h_ch = -1, h_sz = -1;
        for (int v : AL[u]) {
            if (v == p) continue;
            if (sz[v] > h_sz) {
                h_ch = v;
                h_sz = sz[v];
            }
        }
        if (h_ch == -1) return;
        dfs_hld(h_ch, u, t);
        for (int v : AL[u]) {
            if (v == p || v == h_ch) continue;
            dfs_hld(v, u, v);
        }
    }

    T query(int u, int v) {
        T ans = 0;
        while (top[u] != top[v]) {
            if (d[top[u]] < d[top[v]]) swap(u, v);
            ans = st.merge(ans, st.query(id[top[u]], id[u]));
            u = par[top[u]];
        }

        if (d[u] > d[v]) swap(u, v);
        ans = st.merge(ans, st.query(id[u], id[v]));
        return ans;
    }
    void update(int p, int x) {
        st.update(id[p], x);
    }
};
