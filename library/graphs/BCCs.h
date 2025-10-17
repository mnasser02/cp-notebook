#include <bits/stdc++.h>
using namespace std;

struct BCC {
    vector<vector<int>>&AL, comps;
    vector<int> num, low, art, id;
    int n, timer, c;
    stack<int> stk;
    BCC(vector<vector<int>>& AL_) : AL(AL_) {
        n = AL.size();
        num.resize(n);
        low.resize(n);
        art.resize(n);
        id.resize(n);
        timer = 0, c = 0;
        dfs(0, -1);
    }

    void dfs(int u, int p) {
        num[u] = low[u] = ++timer;
        stk.push(u);
        for (int v : AL[u]) {
            if (v == p) continue;
            if (num[v]) {
                low[u] = min(low[u], num[v]);
            } else {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= num[u]) {
                    comps.push_back({u});
                    art[u] = num[u] > 1 || num[v] > 2;
                    while (comps[c].back() != v) {
                        comps[c].push_back(stk.top());
                        stk.pop();
                    }
                    c++;
                }
            }
        }
    }
    // block-cut tree
    vector<vector<int>> get_tree() {
        vector<vector<int>> t;
        int i = 0;
        for (int u = 0; u < n; u++) {
            if (art[u]) {
                id[u] = i++;
                t.push_back({});
            }
        }
        for (auto& comp : comps) {
            int cur = i++;
            t.push_back({});
            for (int u : comp) {
                if (art[u]) {
                    t[id[u]].push_back(cur);
                    t[cur].push_back(id[u]);
                } else {
                    id[u] = cur;
                }
            }
        }
        return t;
    }
};
