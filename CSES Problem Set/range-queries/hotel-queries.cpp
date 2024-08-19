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

vi stree;
int n, m;
int query(int p, int l, int r, int x) {
    if (l == r) {
        return l;
    }
    int m = l + r >> 1;
    if (stree[p << 1] >= x) {
        return query(p << 1, l, m, x);
    } else {
        return query(p << 1 | 1, m + 1, r, x);
    }
}
void update(int p, int x) {
    stree[n + p] -= x;
    for (int j = n + p >> 1; j >= 1; j >>= 1) {
        stree[j] = max(stree[j << 1], stree[j << 1 | 1]);
    }
}
void solve() {
    cin >> n >> m;
    vi h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    while (__builtin_popcount(n) != 1) n++;
    stree.resize(2 * n);
    for (int i = 0; i < h.size(); i++) {
        stree[n + i] = h[i];
    }
    for (int i = n - 1; i >= 1; i--) {
        stree[i] = max(stree[i << 1], stree[i << 1 | 1]);
    }
    while (m--) {
        int r;
        cin >> r;
        if (stree[1] >= r) {
            int i = query(1, 0, n - 1, r);
            update(i, r);
            cout << i + 1 << " ";
        } else {
            cout << "0 ";
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
