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

struct node {
    ll sum;
    node *left, *right;
    node(int x) : left(nullptr), right(nullptr), sum(x) {}
    node(node *l, node *r) : left(l), right(r), sum(0) {
        if (left) sum += l->sum;
        if (right) sum += r->sum;
    }
};

const int N = 1 << 18;
int a[N];
node *version[N];

node *build(int l, int r) {
    if (l == r) {
        return new node(a[l]);
    }
    int m = l + r >> 1;
    return new node(build(l, m), build(m + 1, r));
}
ll query(node *v, int l, int r, int i, int j) {
    if (i <= l && r <= j) {
        return v->sum;
    }
    if (r < i || l > j) {
        return 0;
    }
    int m = l + r >> 1;
    return query(v->left, l, m, i, j) + query(v->right, m + 1, r, i, j);
}

node *update(node *v, int l, int r, int i, int x) {
    if (l == r) {
        return new node(x);
    }

    int m = l + r >> 1;
    if (i <= m)
        return new node(update(v->left, l, m, i, x), v->right);
    else
        return new node(v->left, update(v->right, m + 1, r, i, x));
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int cnt = 1;
    version[cnt++] = build(0, N - 1);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, a, x;
            cin >> k >> a >> x;
            a--;
            version[k] = update(version[k], 0, N - 1, a, x);
        } else if (t == 2) {
            int k, a, b;
            cin >> k >> a >> b;
            a--, b--;
            cout << query(version[k], 0, N - 1, a, b) << "\n";
        } else {
            int k;
            cin >> k;
            version[cnt++] = version[k];
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
