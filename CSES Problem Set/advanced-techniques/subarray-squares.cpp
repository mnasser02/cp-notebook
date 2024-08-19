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

struct line {
    ll a, b;
};
ll calc(line l, ll x) {
    return l.a * x + l.b;
}
ll inter(line l1, line l2) {
    return (l1.b - l2.b) / (l2.a - l1.a);
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<vll> dp(n + 1, vll(k + 1));
    vector<deque<line>> dqs(k + 1);
    ll pre = 0;

    dqs[0].push_back({0, 0});

    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        pre += t;
        ll x = pre;

        for (int j = min(i, k); j >= 1; j--) {
            auto& dq = dqs[j - 1];
            while (dq.size() > 1 && calc(dq[0], x) >= calc(dq[1], x)) {
                dq.pop_front();
            }

            dp[i][j] = calc(dq[0], x) + pre * pre;
            ll a = -2 * pre, b = dp[i][j] + pre * pre;
            auto& dq2 = dqs[j];
            dq2.push_back({a, b});

            int m = dq2.size();
            while (dq2.size() > 2 && inter(dq2[m - 1], dq2[m - 2]) <= inter(dq2[m - 2], dq2[m - 3])) {
                auto tmp = dq2[m - 1];
                dq2.pop_back();
                dq2.pop_back();
                dq2.push_back(tmp);
                m--;
            }
        }
    }
    cout << dp[n][k];
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