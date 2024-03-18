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

const int MXN = 1e6 + 10;
int d[MXN];
void sieve() {
    for (int i = 1; i < MXN; i++) {
        for (int j = i; j < MXN; j += i) {
            d[j]++;
        }
    }
}
void solve() {
    int x;
    cin >> x;
    cout << d[x] << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    sieve();
    while (tc--) {
        solve();
    }
    return 0;
}
