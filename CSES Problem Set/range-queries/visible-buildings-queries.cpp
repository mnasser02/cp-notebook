#include <bits/stdc++.h>

using namespace std;

bool chmax(int &a, int b) { return a < b ? a = b, 1 : 0; }

struct SegTree {
    vector<vector<int>> tree;
    int n;
    vector<int> merge_(const vector<int> &a, const vector<int> &b) {
        vector<int> c;
        merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(c));
        return c;
    }

    SegTree(vector<int> &A) {
        n = A.size();
        while (__builtin_popcount(n) != 1) n++;

        tree.resize(2 * n);
        for (int i = 0; i < A.size(); i++) {
            tree[n + i] = vector<int>{A[i]};
        }
        for (int i = n - 1; i >= 1; i--) {
            tree[i] = merge_(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    int query(int p, int l, int r, int i, int j, int x) {
        if (r < i || l > j) return 0;
        if (i <= l && r <= j) {
            return lower_bound(tree[p].begin(), tree[p].end(), x) - tree[p].begin();
        }
        int m = l + r >> 1;
        return query(p << 1, l, m, i, j, x) + query(p << 1 | 1, m + 1, r, i, j, x);
    }

    int query(int i, int j, int x) { return query(1, 0, n - 1, i, j, x); }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> left_max(n, -1);
    stack<pair<int, int>> stk;
    int mx = 0, p = -1;
    stk.push({2e9, -1});
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        while (x > stk.top().first) stk.pop();

        left_max[i] = stk.top().second;
        stk.push({x, i});
    }
    SegTree st(left_max);

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cout << st.query(a, b, a) << '\n';
    }
    return 0;
}