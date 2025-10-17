int get_sizes(int u, int p = -1) {
    sz[u] = 1;
    for (int v : AL[u]) {
        if (v == p || removed[v]) {
            continue;
        }
        sz[u] += get_sizes(v, u);
    }
    return sz[u];
}

int get_centroid(int u, int tree_size, int p = -1) {
    for (int v : AL[u]) {
        if (v == p || removed[v]) {
            continue;
        }
        if (sz[v] * 2 > tree_size) {
            return get_centroid(v, tree_size, u);
        }
    }
    return u;
}

void centroid_decomp(int u) {
    int centroid = get_centroid(u, get_sizes(u));

    // do something
    removed[centroid] = true;
    for (int v : AL[centroid]) {
        if (removed[v])
            continue;
        centroid_decomp(v);
    }
}
