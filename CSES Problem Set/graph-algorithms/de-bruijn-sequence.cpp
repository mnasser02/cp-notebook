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
    int n;
    cin >> n;
    if (n == 1) {
        cout << "01";
        return;
    }
    int sz = (1 << (n - 1));
    vector<vi> AL(sz);

    for (int u = 0; u < sz; u++) {
        int v = (u & ((1 << (n - 2)) - 1)) << 1;
        AL[u].push_back(v);
        AL[u].push_back(v ^ 1);
    }

    vi ans;
    auto hierholzer = [&](int s) {
        vi idx(sz, 0), st;
        st.push_back(s);
        while (!st.empty()) {
            int u = st.back();
            if (idx[u] < (int)AL[u].size()) {
                st.push_back(AL[u][idx[u]]);
                ++idx[u];
            } else {
                ans.push_back(u & 1);
                st.pop_back();
            }
        }
        reverse(ans.begin(), ans.end());
    };
    hierholzer(0);
    n -= 2;
    while (n-- > 0) cout << 0;
    for (int x : ans) cout << x;
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