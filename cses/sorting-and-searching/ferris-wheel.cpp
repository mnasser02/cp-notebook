#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<ll, ll, ll> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

void solve() {
    int n, x;
    cin >> n >> x;
    vi A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(all(A));
    int l = 0, r = n - 1;
    int ans = 0;
    while (l <= r) {
        if (A[l] + A[r] <= x) {
            l++, r--;
        } else {
            r--;
        }
        ans++;
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