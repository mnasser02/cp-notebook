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
    vi s1, s2;
    int l = 1, r = n;
    if (n % 4 == 0) {
        l = 1, r = n;
    } else if (n % 4 == 3) {
        s1.push_back(1);
        s1.push_back(2);
        s2.push_back(3);
        l = 4, r = n;

    } else {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    while (l < r) {
        s1.push_back(l);
        s1.push_back(r);
        l++, r--;
        s2.push_back(l);
        s2.push_back(r);
        l++, r--;
    }
    cout << s1.size() << "\n";
    for (int x : s1) {
        cout << x << " ";
    }
    cout << "\n";

    cout << s2.size() << "\n";
    for (int x : s2) {
        cout << x << " ";
    }
    cout << "\n";
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
