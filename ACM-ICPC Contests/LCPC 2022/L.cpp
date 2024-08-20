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
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vi> pos(26);
    for (int i = 0; i < n; i++) {
        pos[s[i] - 'a'].push_back(i);
    }
    vi dp(n), done(26);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        if (dp[i]) {
            int c1 = (s[i] + 1 - 'a');
            if (c1 < 26 && !done[c1]) {
                for (int j : pos[c1]) {
                    dp[j] = 1;
                }
                done[c1] = 1;
            }
            int c2 = (s[i] - 1 - 'a');
            if (c2 >= 0 && !done[c2]) {
                for (int j : pos[c2]) {
                    dp[j] = 1;
                }
                done[c2] = 1;
            }
        }
    }
    cout << (dp[n - 1] ? "YES\n" : "NO\n");
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