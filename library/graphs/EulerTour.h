#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<pair<int, int>> AL[N];
bool seen[N];      // remove if directed
vector<int> path;  // reversed (important if path not cycle)
void dfs(int u) {
    while (!AL[u].empty()) {
        auto [v, i] = AL[u].back();
        AL[u].pop_back();
        if (seen[i]) continue;
        seen[i] = 1;
        dfs(v);
    }
    path.push_back(u);  // u&1 for de bruijn
}
string debruijn_seq(int n) {
    if (n == 1) {
        cout << "01";
        return;
    }
    int sz = (1 << (n - 1));
    for (int u = 0; u < sz; u++) {
        int v = (u & ((1 << (n - 2)) - 1)) << 1;
        AL[u].push_back(v);
        AL[u].push_back(v ^ 1);
    }
    dfs(0);
    reverse(path.begin(), path.end());
    n -= 2;
    while (n-- > 0) cout << 0;
    for (int x : path) cout << x;
}