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

const int N = 1 << 20;
void solve() {
    int n;
    cin >> n;

    vi dp1(N), dp2(N), x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        dp1[x[i]]++;
        dp2[x[i]]++;
    }
    for (int i = 0; i < 20; i++) {
        for (int bm = 0; bm < N; bm++) {
            if (bm & (1 << i)) dp1[bm] += dp1[bm ^ (1 << i)];
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int bm = N - 1; bm >= 0; bm--) {
            if (!(bm & (1 << i))) dp2[bm] += dp2[bm ^ (1 << i)];
        }
    }
    for (int i = 0; i < n; i++) {
        cout << dp1[x[i]] << ' ' << dp2[x[i]] << ' ' << (n - dp1[((1 << 20) - 1) ^ x[i]]);
        cout << '\n';
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