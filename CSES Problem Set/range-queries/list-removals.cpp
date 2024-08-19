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
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> os_tree;

void solve() {
    int n;
    cin >> n;
    vi x(n);
    os_tree tree;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        tree.insert(i);
    }

    for (int k = 0; k < x.size(); k++) {
        int i;
        cin >> i;
        i--;
        auto it = tree.find_by_order(i);
        cout << x[*it] << " ";
        tree.erase(it);
    }
}

int main() {
    // ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    // cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}
