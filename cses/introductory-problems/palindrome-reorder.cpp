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
    string s;
    cin >> s;
    vi cnt(128, 0);
    for (char c : s) cnt[c]++;
    string left, right;
    char m = 'a';
    for (int c = 'A'; c <= 'Z'; c++) {
        if (cnt[c] % 2) {
            if (m != 'a') {
                cout << "NO SOLUTION\n";
                return;
            }
            m = c;
            cnt[c]--;
        }
        while (cnt[c]) {
            left.push_back(c);
            right.push_back(c);
            cnt[c] -= 2;
        }
    }
    if (m != 'a')
        left.push_back(m);
    reverse(all(right));

    cout << left + right << "\n";
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
