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

const int N = 1 << 18;
ll stree[N << 1], lazy1[N << 1], lazy2[N << 1];
int n, q;

void push(int p, int l, int r) {
    if (lazy1[p]) {
        stree[p] += lazy1[p] * (r - l + 1) * (l + r + 2) / 2;
        if (l != r) {
            lazy1[p << 1] += lazy1[p];
            lazy1[p << 1 | 1] += lazy1[p];
        }
        lazy1[p] = 0;
    }
    if (lazy2[p]) {
        stree[p] += lazy2[p] * (r - l + 1);
        if (l != r) {
            lazy2[p << 1] += lazy2[p];
            lazy2[p << 1 | 1] += lazy2[p];
        }
        lazy2[p] = 0;
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
void update(int p, int l, int r, int i, int j, int t) {
    push(p, l, r);
    if (i <= l && r <= j) {
        if (t == 1) {
            lazy1[p]++;
        } else {
            lazy2[p] += t;
        }
        push(p, l, r);
        return;
    }
    if (r < i || l > j) return;

    int m = l + r >> 1;
    update(p << 1, l, m, i, j, t);
    update(p << 1 | 1, m + 1, r, i, j, t);
    stree[p] = stree[p << 1] + stree[p << 1 | 1];
}

void solve() {
    cin >> n >> q;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        stree[N + i] = a[i];
    }
    for (int i = N - 1; i >= 1; i--) {
        stree[i] = stree[i << 1] + stree[i << 1 | 1];
    }
    while (q--) {
        int t;
        cin >> t;
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (t == 1) {
            update(1, 0, N - 1, a, b, 1);
            update(1, 0, N - 1, a, b, -a);
        } else {
            cout << query(1, 0, N - 1, a, b) << "\n";
        }
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
