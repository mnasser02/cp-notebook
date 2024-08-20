#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

int id = 0;
struct SegTree {
    vector<ordered_set<ii>> tree;
    int n;

    SegTree(int n_) : n(n_) {
        while (__builtin_popcount(n) != 1) n++;
        tree.resize(2 * n);
    }

    int query(int p, int l, int r, int i, int j, int y) {
        if (i <= l && r <= j) {
            return tree[p].order_of_key({y, 1e9});
        }
        if (r < i || l > j) return 0;
        int m = l + r >> 1;
        return query(p << 1, l, m, i, j, y) + query(p << 1 | 1, m + 1, r, i, j, y);
    }

    void update(int p, int x) {
        tree[n + p].insert({x, ++id});
        for (int j = n + p >> 1; j >= 1; j >>= 1) {
            tree[j].insert({x, id});
        }
    }

    int query(int i, int j, int y) { return query(1, 0, n - 1, i, j, y); }
};

const int MX = 1e5 + 5;

using a2 = array<int, 2>;
void solve() {
    int n;
    cin >> n;
    SegTree st(MX);
    for (int i = 0; i < n; i++) {
        a2 a, b;
        cin >> a[0] >> a[1] >> b[0] >> b[1];
        st.update(b[0], b[1]);
    }

    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            a2 a, b;
            cin >> a[0] >> a[1] >> b[0] >> b[1];
            st.update(b[0], b[1]);
        } else {
            a2 a;
            cin >> a[0] >> a[1];
            cout << st.query(0, a[0], a[1]) << '\n';
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