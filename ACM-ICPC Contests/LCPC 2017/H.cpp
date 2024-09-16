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

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vi row(n + 1), col(m + 1);
    set<int> badr, badc;

    while (q--) {
        int t;
        cin >> t;
        if (t == 3) {
            int c;
            cin >> c;
            badc.insert(c);
            col[c]++;
        } else if (t == 4) {
            int c;
            cin >> c;
            col[c]--;
            if (col[c] == 0) badc.erase(c);
        } else if (t == 1) {
            int r;
            cin >> r;
            badr.insert(r);
            row[r]++;
        } else if (t == 2) {
            int r;
            cin >> r;
            row[r]--;
            if (row[r] == 0) badr.erase(r);
        } else {
            int xs, ys, xe, ye;
            cin >> xs >> ys >> xe >> ye;
            auto it = badr.lower_bound(min(xs, xe));
            auto it2 = badc.lower_bound(min(ys, ye));
            if (it != badr.end() && *it <= max(xs, xe) || it2 != badc.end() && *it2 <= max(ys, ye)) {
                cout << "-1\n";
            } else {
                cout << max(abs(xs - xe), abs(ys - ye)) << '\n';
            }
        }
    }
}

int main() {
    freopen("qatar.in", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}