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

const int MX = 1e6 + 1;
void solve() {
    int n;
    cin >> n;
    vi a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vi b2 = b;
    sort(all(b2));
    vi can, done(MX);
    can.reserve(MX);
    for (int i = 0; i < n; i++) {
        if (done[b2[i]]) continue;
        for (int j = b2[i]; j < MX; j += b2[i]) {
            can.push_back(j);
            done[j] = 1;
        }
    }
    sort(all(can));

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int d = b[i] - a[i];
        if (d < 0) {
            cout << "-1\n";
            return;
        }
        auto it = upper_bound(all(can), d);
        if (it != can.begin()) {
            d -= *prev(it);
            ans++;
        }
        ans += d;
    }

    cout << ans << "\n";
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