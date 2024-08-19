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
    int n;
    cin >> n;
    vi a(n);
    ll tot = 0;
    for (int &x : a) {
        cin >> x;
        tot += x;
    }
    ll mn = 1e15l;
    for (int bm = 0; bm < (1 << n); bm++) {
        ll sum = 0;
        for (int msk = bm; msk; msk ^= LSOne(msk)) {
            int v = __builtin_ctz(msk);
            sum += a[v];
        }
        mn = min(mn, abs(tot - sum - sum));
    }
    cout << mn << "\n";
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
