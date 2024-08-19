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
    ll n;
    cin >> n;
    ll mem[50][50][50];
    memset(mem, -1, sizeof mem);
    auto dp = [&](auto dp, int i, int pref, int c) -> ll {
        if (i < 0) return 0;
        ll& ans = mem[i][pref][c];
        if (ans != -1) return ans;
        int b = !!((1ll << i) & n);
        c += b;
        if (pref) {
            ans = (1ll << (pref - 1)) + dp(dp, i - 1, pref, c);
        } else {
            if (b) {
                ans = (1ll << i) * (c - 1) + dp(dp, i - 1, i, c) + 1 + dp(dp, i - 1, 0, c);
            } else {
                ans = dp(dp, i - 1, 0, c);
            }
        }
        return ans;
    };
    cout << dp(dp, 63 - __builtin_clzll(n), 0, 0);
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