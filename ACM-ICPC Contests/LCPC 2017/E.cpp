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

#define EPS 1e-9

void solve() {
    int n, m;
    cin >> n >> m;
    vii rooms(n);

    double l = 0, r = 1e12;
    for (int i = 0; i < n; i++) {
        cin >> rooms[i].first >> rooms[i].second;
        ckmax(l, (double)rooms[i].second);
    }
    set<int> rtr;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        rtr.insert(x);
    }

    auto inter = [&](ll c1, double r1, ll c2, double r2) {
        ll d = c2 - c1;
        double cos = r1 * r1 + d * d - r2 * r2;
        cos /= 2.0 * r1 * d;
        return cos * r1 + c1;
    };

    auto check = [&](double R) {
        for (auto [x, r] : rooms) {
            auto it2 = rtr.lower_bound(x);
            if (it2 != rtr.end())
                if (*it2 - x + r - R < EPS) continue;
            if (it2 != rtr.begin()) {
                auto it1 = prev(it2);
                if (x - *it1 + r <= R) continue;
                if (it2 != rtr.end()) {
                    if (x - r - *it1 - R > -EPS || *it2 - (x + r) - R > -EPS) return false;
                    if (inter(*it1, R, x, r) - inter(x, r, *it2, R) > -EPS) continue;
                }
            }
            return false;
        }
        return true;
    };
    double ans = 1e18;
    while (abs(r - l) > EPS) {
        double m = (l + r) / 2;
        if (check(m)) {
            ckmin(ans, m);
            r = m;
        } else {
            l = m;
        }
    }
    cout << fixed << setprecision(6) << ans << '\n';
}

int main() {
    freopen("syria.in", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}