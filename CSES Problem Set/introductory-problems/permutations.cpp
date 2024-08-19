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
    if (n == 3 || n == 2) {
        cout << "NO SOLUTION\n";
        return;
    }
    vi ans(n);
    for (int i = 0; i < n; i++) {
        if ((i + 1) % 2)
            ans[n / 2 + i / 2] = i + 1;
        else
            ans[i / 2] = i + 1;
    }
    for (int x : ans) cout << x << " ";
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
