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

using a2 = array<ll, 2>;
const int MX = 2e5 + 1;

struct BIT {
    int n;
    vll bit, A;

    BIT(int n) : n(n), bit(n + 1), A(n) {}

    void set(int i, ll val) { add(i, val - A[i]); }

    void add(int i, ll val) {
        A[i] += val;
        i++;
        for (; i <= n; i += i & -i) {
            bit[i] += val;
        }
    }

    ll pre(int i) {
        i++;
        ll total = 0;
        for (; i > 0; i -= i & -i) {
            total += bit[i];
        }
        return total;
    }

    ll query(int i, int j) { return pre(j) - pre(i - 1); }
    ll suf(int i) { return query(i, MX - 1); }
};

ll s(a2 a) { return (a[0] - a[1]) * (a[0] - a[1]); }
void solve() {
    int n;
    cin >> n;
    vector<a2> A(n);

    BIT b1(MX), b2(MX), b3(MX), b4(MX);
    for (int i = 0; i < n; i++) {
        cin >> A[i][0] >> A[i][1];
        b1.add(A[i][0], s(A[i]));
    }

    sort(all(A), [&](a2 a, a2 b) {
        if (a[1] == b[1]) return a[0] < b[0];
        return a[1] > b[1];
    });

    ll ans = 0;
    for (auto a : A) {
        b1.add(a[0], -s(a));

        ans += b1.suf(a[0]);

        ans += a[1] * a[1] * b2.query(a[0] + 1, a[1] - 1);
        ans += b3.query(a[0] + 1, a[1] - 1);
        ans += -2 * a[1] * b4.query(a[0] + 1, a[1] - 1);

        b2.add(a[0], 1);
        b3.add(a[0], a[0] * a[0]);
        b4.add(a[0], a[0]);
    }
    cout << ans << '\n';
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