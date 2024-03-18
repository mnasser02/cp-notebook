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

#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree<ii, null_type, less<ii>, rb_tree_tag, tree_order_statistics_node_update> os_tree;

void solve() {
    int n, q;
    cin >> n >> q;
    vi a(n);
    os_tree tree;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        tree.insert({a[i], i});
    }
    while (q--) {
        char t;
        cin >> t;
        if (t == '!') {
            int k, x;
            cin >> k >> x;
            k--;
            tree.erase({a[k], k});
            a[k] = x;
            tree.insert({a[k], k});
        } else {
            int a, b;
            cin >> a >> b;
            int r = tree.order_of_key({b, 1e9});
            int l = tree.order_of_key({a, -1});
            cout << r - l << "\n";
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
