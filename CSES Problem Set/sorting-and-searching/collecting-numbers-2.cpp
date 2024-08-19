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
using os_tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

void solve() {
    int n, m;
    cin >> n >> m;
    vi A(n + 1), pos(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        pos[A[i]] = i;
    }
    int ans = 1;
    for (int i = 1; i < n; i++) {
        ans += pos[i] > pos[i + 1];
    }

    auto fix = [&](int v, int o, int n, int v2) {
        if (v + 1 != v2 && n <= pos[v + 1] && o > pos[v + 1]) ans--;
        if (v - 1 != v2 && n >= pos[v - 1] && o < pos[v - 1]) ans--;
        if (v + 1 != v2 && n >= pos[v + 1] && o < pos[v + 1]) ans++;
        if (v - 1 != v2 && n <= pos[v - 1] && o > pos[v - 1]) ans++;
    };

    while (m--) {
        int a, b;
        cin >> a >> b;
        fix(A[a], a, b, -1);
        fix(A[b], b, a, A[a]);
        swap(pos[A[a]], pos[A[b]]);
        swap(A[a], A[b]);

        cout << ans << "\n";
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