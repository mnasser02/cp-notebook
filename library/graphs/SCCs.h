#include <bits/stdc++.h>
using namespace std;

int timer, scc_cnt;
vector<int> num, low, vis, id;
stack<int> stk;
void dfs(int u) {
    low[u] = num[u] = timer;
    timer++;
    stk.push(u);
    vis[u] = 1;
    for (auto v : AL[u]) {
        if (num[v] == -1)
            dfs(v);
        if (vis[v])
            low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        ++scc_cnt;
        while (1) {
            int v = stk.top();
            stk.pop();
            id[v] = u;
            vis[v] = 0;
            if (u == v) break;
        }
    }
}
void sccs() {
    id.assign(n, -1);
    num.assign(n, -1);
    low.assign(n, 0);
    vis.assign(n, 0);
    while (!stk.empty()) stk.pop();
    timer = scc_cnt = 0;
    for (int u = 0; u < n; ++u)
        if (num[u] == -1)
            dfs(u);
}