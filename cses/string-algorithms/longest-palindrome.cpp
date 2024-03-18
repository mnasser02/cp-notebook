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

vector<vi> manacher(string &s) {
    int n = s.size();
    vector<vi> p(2, vi(n, 0));
    for (int z = 0, l = 0, r = 0; z < 2; z++, l = 0, r = 0)
        for (int i = 0; i < n; i++) {
            if (i < r) p[z][i] = min(r - i + !z, p[z][l + r - i + !z]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1]) p[z][i]++, L--, R++;
            if (R > r) l = L, r = R;
        }
    return p;
}

void solve() {
    string s;
    cin >> s;
    vector<vi> p = manacher(s);
    int n = s.size();
    int mx = 1, j = 0;
    bool o = 1;
    for (int i = 0; i < n; i++) {
        int len = 2 * p[1][i] + 1;
        if (len > mx) {
            mx = len;
            j = i;
            o = 1;
        }
        len = 2 * p[0][i];
        if (len > mx) {
            mx = len;
            j = i;
            o = 0;
        }
    }
    string ans = s.substr(j - mx / 2, mx);
    cout << ans;
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