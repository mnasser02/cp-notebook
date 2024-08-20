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
    int n, x;
    cin >> n >> x;
    vi cnt(1001);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }
    ll ans = 0;
    for (int i = 0; i <= 1000; i++) {
        for (int j = i; j <= 1000; j++) {
            if ((i & j) == x) {
                if (i == j)
                    ans += (ll)cnt[i] * (cnt[i] - 1) / 2;
                else
                    ans += (ll)cnt[i] * cnt[j];
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}