#include <bits/stdc++.h>
using namespace std;

vector<int> num, low;
vector<bool> bridge;
int timer;
void dfs(int u, int p) {
    num[u] = low[u] = ++timer;
    for (auto [v, i] : AL[u]) {
        if (!num[v]) {
            dfs(v, u);
            if (low[v] > num[u]) {
                bridge[i] = 1;
            }
            low[u] = min(low[u], low[v]);
        } else if (v != p) {
            low[u] = min(low[u], num[v]);
        }
    }
}
void bridges() {
    bridge.assign(m, 0);
    num.assign(n, -1);
    low.assign(n, -1);
    timer = 0;

    for (int u = 0; u < n; u++) {
        if (num[u] == -1) {
            dfs(u, -1);
        }
    }
}