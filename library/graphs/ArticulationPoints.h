#include <bits/stdc++.h>
using namespace std;

vector<bool> art;
vector<int> low, num;
int timer, root_ch;
void dfs(int u, int p) {
    low[u] = num[u] = timer++;
    for (int v : AL[u]) {
        if (num[v] == -1) {
            dfs(v, u);
            if (u == 0) root_ch++;
            if (low[v] >= num[u]) {
                art[u] = 1;
            }
            low[u] = min(low[u], low[v]);
        } else if (p != v) {
            low[u] = min(low[u], num[v]);
        }
    }
}
void art_points() {
    low.assign(n, -1);
    num.assign(n, -1);
    art.assign(n, 0);
    timer = 0;

    for (int u = 0; u < n; u++) {
        if (num[u] == -1) {
            root_ch = 0;
            dfs(u, -1);
            art[u] = root_ch > 1;
        }
    }
}