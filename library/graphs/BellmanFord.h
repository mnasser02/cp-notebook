vector<int> dist(n, INF);
dist[s] = 0;
for (int i = 0; i < n - 1; ++i) {
    for (int u = 0; u < n; ++u) {
        if (dist[u] != INF) {
            for (auto& [v, w] : AL[u]) {
                dist[v] = min(dist[v], dist[u] + w);
            }
        }
    }
}
for (int u = 0; u < n; ++u) {
    if (dist[u] != INF) {
        for (auto& [v, w] : AL[u]) {
            if (dist[v] > dist[u] + w) {
                hasNegativeCycle = true;
            }
        }
    }
}
