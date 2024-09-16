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
    int n, k;
    double p;
    cin >> n >> k >> p;
    vector<vector<double>> mem(n + 1, vector<double>(k + 1, -1));
    auto dp = [&](auto self, int r, int x) -> double {
        if (r == 1) return x;
        double& ans = mem[r][x];
        if (ans != -1) return ans;
        ans = 0;
        int y = r - x;
        double den = r * (r - 1) / 2;
        if (x && y) {
            ans += x * y * p * self(self, r - 1, x);
            ans += x * (r - x) * (1 - p) * self(self, r - 1, x - 1);
        }
        if (y >= 2)
            ans += y * (y - 1) / 2 * self(self, r - 1, x);
        if (x >= 2)
            ans += x * (x - 1) / 2 * self(self, r - 1, x - 1);
        return ans /= den;
    };
    cout << fixed << setprecision(6) << dp(dp, n, k) << '\n';
}

int main() {
    freopen("ballon.in", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}