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
    vector<string> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    vector<vi> grundy(n, vi(m, -1));
    auto dp = [&](auto self, int i, int j) -> int {
        int& ans = grundy[i][j];
        if (ans != -1) return ans;
        set<int> st;
        for (int k = 1; k <= 3; k++) {
            if (j + k >= m) break;
            if (A[i][j + k] == 'W')
                st.insert(self(self, i, j + k));
            else
                break;
        }

        for (int k = 1; k <= 5; k += 2) {
            if (i + k >= n) break;
            if (A[i + k][j] == 'W')
                st.insert(self(self, i + k, j));
        }

        ans = 0;
        while (st.count(ans)) ans++;
        return ans;
    };
    while (q--) {
        int k;
        cin >> k;
        int nim = 0;
        while (k--) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            nim ^= dp(dp, x, y);
        }
        cout << (nim ? "Roger\n" : "Rafael\n");
    }
}

int main() {
    freopen("roger.in", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}