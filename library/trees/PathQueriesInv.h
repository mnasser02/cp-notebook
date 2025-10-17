// pt updates
int timer;

void dfs(int u, int p) {
    in[u] = ++timer;
    for (int v : AL[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    out[u] = ++timer;
}
// main
dfs(0, -1);
for (int i = 0; i < n; i++) {
    st.update(in[i], a[i]);
    st.update(out[i], -a[i]);
}

st.update(in[i], x);
st.update(out[i], -x);
a[i] = x;

int anc = lca(u, v);
st.query(in[anc], in[u]) + st.query(in[anc], in[v]) - a[anc];
