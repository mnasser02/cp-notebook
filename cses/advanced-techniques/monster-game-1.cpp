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

struct line {
    ll a, b;
};
ll eval(line l, ll x) {
    return l.a * x + l.b;
}
ll isect(line l1, line l2) {
    return (l2.b - l1.b) / (l1.a - l2.a);
}

void solve() {
    int n, x;
    cin >> n >> x;

    vll s(n), f(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }

    deque<line> dq;
    dq.push_back({x, 0});

    vll dp(n);
    for (int i = 0; i < n; i++) {
        int m = dq.size();
        int x = s[i], y = f[i];
        while (m >= 2 && eval(dq[1], x) <= eval(dq[0], x)) {
            dq.pop_front();
            m--;
        }

        auto [a, b] = dq.front();
        dp[i] = a * x + b;
        line cur = {y, dp[i]};

        if (cur.a == dq[m - 1].a) {
            if (cur.b > dq[m - 1].b) {
                continue;
            }
            dq.pop_back();
            m--;
        }

        while (m >= 2 && isect(cur, dq[m - 1]) <= isect(dq[m - 1], dq[m - 2])) {
            dq.pop_back();
            m--;
        }

        dq.push_back(cur);
    }
    cout << dp[n - 1] << "\n";
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