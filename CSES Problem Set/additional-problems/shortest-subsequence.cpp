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
    string s;
    cin >> s;
    int n = s.size();
    map<char, int> mp{{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
    vi active(4);
    int c = 0;
    string ans;
    for (int i = 0; i < n; i++) {
        int x = mp[s[i]];
        if (!active[x]) {
            c++;
        }
        active[x] = 1;
        if (c == 4) {
            active.assign(4, 0);
            c = 0;
            ans.push_back(s[i]);
        }
    }
    for (auto [k, v] : mp) {
        if (!active[v]) {
            ans.push_back(k);
            break;
        }
    }
    cout << ans << "\n";
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