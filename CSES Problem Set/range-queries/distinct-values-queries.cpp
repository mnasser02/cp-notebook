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
vi stree;

int query(int p, int l, int r, int i, int j) {
    if (i <= l && r <= j) {
        return stree[p];
    }
    if (r < i || l > j) {
        return 0;
    }
    int m = l + r >> 1;
    return query(p << 1, l, m, i, j) + query(p << 1 | 1, m + 1, r, i, j);
}
void update(int p, int x) {
    stree[n + p] = x;
    for (int j = n + p >> 1; j >= 1; j >>= 1) {
        stree[j] = stree[j << 1] + stree[j << 1 | 1];
    }
}
void solve() {
    cin >> n >> q;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ni = n;
    while (__builtin_popcount(n) != 1) n++;
    stree.resize(2 * n);

    vector<iii> queries;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        queries.push_back({a, b, i});
    }
    sort(all(queries));
    map<int, int> pos;
    vi ans(q);
    int j = q - 1;
    auto [l, r, id] = queries[j];
    for (int i = ni - 1; i >= 0; i--) {
        if (pos.count(a[i])) {
            update(pos[a[i]], 0);
        }
        update(i, 1);
        pos[a[i]] = i;
        while (l == i) {
            ans[id] = query(1, 0, n - 1, l, r);
            j--;
            if (j == -1) break;
            tie(l, r, id) = queries[j];
        }
        if (j == -1) break;
    }
    for (int x : ans) cout << x << "\n";
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
