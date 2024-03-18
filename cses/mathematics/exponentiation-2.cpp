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

const int M = (int)1e9 + 7;
int mod_pow(ll b, ll p, ll m) {
    ll ans = 1;
    while (p) {
        if (p & 1) ans = ans * b % m;
        b = b * b % m;
        p >>= 1;
    }
    return ans;
}

void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    cout << mod_pow(a, mod_pow(b, c, M - 1), M) << "\n";
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
