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

    int ans = 0;
    for (int i = 0; i < (1 << n); i++) {
        ans ^= LSOne(i);

        int x = ans;
        for (int k = 0; k < n; k++) {
            cout << x % 2;
            x /= 2;
        }

        cout << "\n";
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