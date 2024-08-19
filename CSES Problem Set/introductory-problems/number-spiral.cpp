#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & (-S))

void solve() {
    ll x, y;
    cin >> x >> y;
    ll ans;
    if (x >= y) {
        if (x % 2) {
            ans = (x - 1) * (x - 1) + y;
        } else {
            ans = x * x - (y - 1);
        }
    } else {
        if (y % 2) {
            ans = y * y - (x - 1);
        } else {
            ans = (y - 1) * (y - 1) + x;
        }
    }
    cout << ans << "\n";
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