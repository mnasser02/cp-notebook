#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef tuple<int, int, int> iii;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

int n;
vll tree;
ll RSQ(int p, int L, int R, int i, int j) {
    if (L >= i && R <= j) return tree[p];
    if (R < i || L > j) return 0;
    int m = (L + R) / 2;
    return RSQ(2 * p, L, m, i, j) + RSQ(2 * p + 1, m + 1, R, i, j);
}
void update(int i, int v) {
    tree[n + i] = v;
    for (int j = (n + i) / 2; j >= 1; j /= 2) {
        tree[j] = tree[2 * j] + tree[2 * j + 1];
    }
}
void solve() {
    int q;
    cin >> n >> q;
    vi a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    while (__builtin_popcount(n) != 1) n++;
    tree.resize(2 * n);
    for (int i = 0; i < a.size(); i++) tree[i + n] = a[i];
    for (int i = n - 1; i >= 1; i--) tree[i] = tree[2 * i] + tree[2 * i + 1];
    while (q--) {
        int cmd, c, d;
        cin >> cmd >> c >> d;
        if (cmd == 1) {
            c--;
            update(c, d);
        } else {
            c--;
            d--;
            cout << RSQ(1, 0, n - 1, c, d) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    // cin >> tc;
    int k = 1;
    while (tc--) {
        solve();
    }
    return 0;
}
