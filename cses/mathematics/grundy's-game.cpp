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

int grundy[2001];

int dp(int n) {
    if (n <= 2) return 0;
    int& ans = grundy[n];
    if (ans != -1) return ans;
    set<int> st;
    for (int i = 1; i <= (n - 1) / 2; i++) {
        st.insert(dp(n - i) ^ dp(i));
    }
    ans = 0;
    while (st.count(ans)) ans++;
    return ans;
}
void solve() {
    int n;
    cin >> n;
    cout << (n >= 2000 || dp(n) ? "first\n" : "second\n");
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    memset(grundy, -1, sizeof grundy);
    while (tc--) {
        solve();
    }
    return 0;
}
