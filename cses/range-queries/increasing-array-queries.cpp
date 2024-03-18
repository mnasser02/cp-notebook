#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

int n, q;
vll stree, lazy;
void push(int p, int l, int r) {
    if (lazy[p]) {
        stree[p] = lazy[p] * (r - l + 1);
        if (l != r) {
            lazy[p << 1] = lazy[p];
            lazy[p << 1 | 1] = lazy[p];
        }
        lazy[p] = 0;
    }
}
ll query(int p, int l, int r, int i, int j) {
    push(p, l, r);
    if (i <= l && r <= j) {
        return stree[p];
    }
    if (r < i || l > j) {
        return 0;
    }
    int m = l + r >> 1;
    return query(p << 1, l, m, i, j) + query(p << 1 | 1, m + 1, r, i, j);
}
void update(int p, int l, int r, int i, int j, int x) {
    push(p, l, r);
    if (i <= l && r <= j) {
        lazy[p] = x;
        push(p, l, r);
        return;
    }
    if (r < i || l > j) {
        return;
    }
    int m = l + r >> 1;
    update(p << 1, l, m, i, j, x);
    update(p << 1 | 1, m + 1, r, i, j, x);
    stree[p] = stree[p << 1] + stree[p << 1 | 1];
}
void solve() {
    cin >> n >> q;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vll pre(n + 1);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + a[i];
    }

    int ni = n;
    while (__builtin_popcount(n) != 1) n++;
    stree.resize(2 * n), lazy.resize(2 * n);
    for (int i = 0; i < ni; i++) {
        stree[n + i] = a[i];
    }
    for (int i = n - 1; i >= 1; i--) {
        stree[i] = stree[i << 1] + stree[i << 1 | 1];
    }

    vector<vii> queries(ni);
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        queries[a].push_back({b, i});
    }

    vll ans(q);
    vii v;
    for (int i = ni - 1; i >= 0; i--) {
        auto it = lower_bound(v.rbegin(), v.rend(), ii{a[i], 0});
        if (it != v.rbegin()) {
            it--;
            update(1, 0, n - 1, i, it->second, a[i]);
        }
        for (auto [r, id] : queries[i]) {
            ll init = pre[r + 1] - pre[i];
            ll cur = query(1, 0, n - 1, i, r);
            ans[id] = cur - init;
        }
        int j = i;
        while (!v.empty() && v.back().first < a[i]) {
            j = max(j, v.back().second);
            v.pop_back();
        }
        v.push_back({a[i], j});
    }
    for (ll x : ans) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    // cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}
