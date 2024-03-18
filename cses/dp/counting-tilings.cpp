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

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

const int M = 1e9 + 7;
ll mem[1 << 10][1000];
int n, m;

bool check(int bm) {
    for (int j = 0; j < n; j++) {
        int x = 0;
        while (j < n && ((1 << j) & bm)) {
            j++;
            x++;
        }
        if (x % 2) {
            return 0;
        }
    }
    return 1;
}
ll dp(int bm, int j) {
    if (j == m - 1) {
        return check(bm);
    }
    ll& ans = mem[bm][j];
    if (ans != -1) return ans;

    int bar = ((1 << n) - 1) & (~bm);
    ans = dp(bar, j + 1);
    for (int ss = bm; ss; ss = bm & (ss - 1)) {
        if (check(ss)) {
            ans = (ans + dp(ss ^ bar, j + 1)) % M;
        }
    }
    return ans % M;
}

void solve() {
    cin >> n >> m;
    memset(mem, -1, sizeof mem);
    cout << dp((1 << n) - 1, 0) << "\n";
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