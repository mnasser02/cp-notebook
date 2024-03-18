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

string P;
int n, m;
int memo[1001][101];
vi pi;
const int M = 1e9 + 7;
vi prefix_function(string &s) {
    int n = s.length();
    vi pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int dp(int i, int j) {
    if (i == n) {
        return j == m;
    }

    int &ans = memo[i][j];
    if (ans != -1) return ans;

    if (j == m) {
        return 26ll * dp(i + 1, j) % M;
    }

    ans = 0;
    for (char c = 'A'; c <= 'Z'; c++) {
        int k = j;
        while (k && c != P[k]) {
            k = pi[k - 1];
        }
        if (c == P[k])
            k++;
        ans = (ans + dp(i + 1, k)) % M;
    }
    return ans;
}

void solve() {
    cin >> n >> P;
    m = P.size();
    memset(memo, -1, sizeof memo);
    pi = prefix_function(P);
    cout << dp(0, 0) << "\n";
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
