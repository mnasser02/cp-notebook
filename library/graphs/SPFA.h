if (mn_edge >= 0) {
    cout << mn_edge << "\n";
    return;
}
queue<int> q;
vll dist(n, 1e18);
vi freq(n, 0);
vector<bool> in_queue(n, 0);

for (int i = 0; i < n; i++) {
    q.push(i);
    dist[i] = 0;
    in_queue[i] = 1;
}
ll ans = LONG_LONG_MAX;
bool neg_cycle = false;
while (!q.empty() && !neg_cycle) {
    int u = q.front();
    q.pop();
    in_queue[u] = 0;
    for (auto& [v, w] : AL[u]) {
        if (dist[u] + w >= dist[v]) continue;
        dist[v] = dist[u] + w;
        ans = min(ans, dist[v]);
        freq[v]++;

        if (!in_queue[v]) {
            q.push(v);
            in_queue[v] = 1;
        }
        if (freq[v] > n) {
            neg_cycle = true;
            break;
        }
    }
}
