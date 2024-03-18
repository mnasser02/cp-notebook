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
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> os_tree;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

ll mem[20][10][2][2];
string num;
ll dp(int i, int prev, int pref, int start) {
    if (i == num.size()) {
        return 1;
    }

    ll& ans = mem[i][prev][pref][start];
    if (ans != -1) return ans;

    int D = 9;
    if (pref) {
        D = num[i] - '0';
    }
    ans = 0;
    for (int d = 0; d <= D; d++) {
        int np = pref;
        int ns = start;
        if (d < D) np = 0;
        if (d) ns = 1;
        if (prev != d || !ns) {
            ans += dp(i + 1, d, np, ns);
        }
    }
    return ans;
}
ll solve(ll x) {
    num = to_string(x);
    memset(mem, -1, sizeof mem);
    return dp(0, 0, 1, 0);
}

void solve() {
    ll x, y;
    cin >> x >> y;
    cout << solve(y) - solve(x - 1) << "\n";
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