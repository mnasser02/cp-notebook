#include <bits/stdc++.h>

using namespace std;

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

int josephus(int n, int k) {
    int rmv = (n + 1) / 2;
    if (k <= rmv) {
        return (2 * k - 1) % n + 1;
    }
    int x = josephus(n - rmv, k - rmv);
    if (n % 2)
        return 2 * x + 1;
    else
        return 2 * x - 1;
}

void solve() {
    int n, k;
    cin >> n >> k;
    cout << josephus(n, k) << "\n";
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