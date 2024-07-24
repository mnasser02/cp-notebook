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
    ll at(ll x) { return a * x + b; }
    ll inter(line l) {
        return (b - l.b) / (l.a - a);
    }
};

void solve() {
    int n, K;
    cin >> n >> K;

    vi A(n + 1);
    vll pre(n + 1), prem(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        pre[i] = pre[i - 1] + A[i];
        prem[i] = prem[i - 1] + (ll)i * A[i];
    }

    vector<vll> f(n + 1, vll(K + 1)), g(n + 1, vll(K + 1));
    vector<deque<line>> dqf(K + 1), dqg(K + 1);
    dqf[0].push_back({0, 0});
    dqg[0].push_back({0, 0});

    auto get = [&](deque<line>& dq, ll x) {
        while (dq.size() > 1 && dq[0].at(x) >= dq[1].at(x)) {
            dq.pop_front();
        }
        return dq.front();
    };

    auto add = [&](deque<line>& dq, line l) {
        dq.push_back(l);
        int m = dq.size();
        while (m > 2 && dq[m - 1].inter(dq[m - 2]) <= dq[m - 2].inter(dq[m - 3])) {
            auto tmp = dq[m - 1];
            dq.pop_back();
            dq.pop_back();
            dq.push_back(tmp);
            m--;
        }
    };

    for (int j = 1; j <= n; j++) {
        for (int k = min(j, K); k >= 1; k--) {
            ll x = j;
            line l = get(dqg[k - 1], x);
            ll c = j * pre[j] - prem[j];
            f[j][k] = l.at(x) + c;

            l = {-j, f[j][k] - prem[j] + j * pre[j]};
            add(dqf[k], l);

            x = pre[j];
            l = get(dqf[k], x);
            c = prem[j];
            g[j][k] = l.at(x) + c;

            l = {-pre[j], g[j][k] + prem[j]};
            add(dqg[k], l);
        }
    }
    cout << g[n][K] << "\n";
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