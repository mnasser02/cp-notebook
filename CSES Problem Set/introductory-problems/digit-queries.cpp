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

ll pow10[20];
vll pre(20);
void solve() {
    ll k;
    cin >> k;
    ll l = 0, r = 1e17;
    ll nb = 0, bf = 0;
    while (l <= r) {
        ll m = (l + r) / 2;
        ll sz = to_string(m).size();
        ll x = pre[sz - 1] + (m - pow10[sz - 1]) * sz;
        if (x < k) {
            nb = m;
            bf = x;
            l = m + 1;
        } else
            r = m - 1;
    }
    ll rm = k - bf;
    cout << to_string(nb)[rm - 1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    pow10[0] = 1;
    for (ll i = 1; i <= 18; i++) {
        pow10[i] = 10 * pow10[i - 1];
    }
    ll nn = 9;
    for (ll i = 1; i <= 17; i++) {
        pre[i] = nn * i + pre[i - 1];
        nn *= 10;
    }

    while (tc--) {
        solve();
    }
    return 0;
}