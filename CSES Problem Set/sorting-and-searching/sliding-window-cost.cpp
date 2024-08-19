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
    cin >> n >> k;
    vi A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    multiset<int> st1, st2;
    ll sum = 0, m = (k - 1) / 2;

    auto insert = [&](ll x) {
        if (st1.empty()) {
            st1.insert(x);
            sum -= x;
            return;
        }
        int med = *st1.rbegin();
        if (x < med) {
            st1.insert(x);
            sum -= x;
            if (st1.size() > 1 + st2.size()) {
                int y = *st1.rbegin();
                st2.insert(y);
                st1.erase(--st1.end());
                sum += 2 * y;
            }
        } else {
            st2.insert(x);
            sum += x;
            if (st2.size() > st1.size()) {
                int y = *st2.begin();
                st1.insert(y);
                st2.erase(st2.begin());
                sum -= 2 * y;
            }
        }
    };
    auto remove = [&](ll x) {
        if (st2.count(x)) {
            st2.extract(x);
            sum -= x;
        } else {
            st1.extract(x);
            sum += x;
        }
        if (st1.empty() && !st2.empty()) {
            int y = *st2.begin();
            st2.extract(y);
            st1.insert(y);
            sum -= 2 * y;
        }
    };

    for (int j = 0; j < n; j++) {
        insert(A[j]);
        if (j < k - 1) continue;

        ll med = *st1.rbegin();
        cout << (2 * (m + 1) - k) * med + sum << " ";

        remove(A[j - k + 1]);
    }
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