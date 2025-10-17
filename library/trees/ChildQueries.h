// tin[u] -> tout[u] doesn't include u
void dfs(int u, int p) {
    tin[u] = t, chin[u] = t;
    for (int v : AL[u]) {
        if (v != p) id[v] = t++;
    }
    chout[u] = t - 1;
    for (int v : AL[u]) {
        if (v != p) dfs(v, u);
    }
    tout[u] = t - 1;
}
