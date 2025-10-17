set<int> dfs(int u, int p) {
    set<int> st{a[u]};

    for (int v : AL[u]) {
        if (v == p) continue;
        set<int> cur = dfs(v, u);
        if (cur.size() > st.size()) {
            swap(cur, st);
        }
        for (int x : cur) st.insert(x);
    }
    // process st here to compute ans[u]. Offline queries
    return st;
}
