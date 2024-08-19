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
#define LSOne(S) ((S) & -(S))

int least_rotation(string s) {
    s += s;
    int n = s.size();
    vi pi(n, -1);
    int k = 0;
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1 - k];
        while (j != -1 && s[i] != s[k + j + 1]) {
            if (s[i] < s[k + j + 1]) {
                k = i - j - 1;
            }
            j = pi[j];
        }
        if (s[i] != s[k + j + 1]) {
            if (s[i] < s[k]) {
                k = i;
            }
            pi[i - k] = -1;
        } else {
            pi[i - k] = j + 1;
        }
    }
    return k;
}
void solve() {
    string s;
    cin >> s;
    int k = least_rotation(s);
    rotate(s.begin(), s.begin() + k, s.end());
    cout << s;
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
