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

vector<string> board(8);
bitset<8> bs;
vi rows(8);
bool check(int r, int c) {
    for (int j = 0; j < c; j++) {
        int i = rows[j];
        if (i - j == r - c || r + c == i + j) {
            return false;
        }
    }
    return true;
}
int queens(int c) {
    if (c == 8) {
        return 1;
    }
    int tot = 0;
    for (int r = 0; r < 8; r++) {
        if (board[r][c] == '*') continue;
        if (bs[r] == 0 && check(r, c)) {
            bs[r] = 1;
            rows[c] = r;
            tot += queens(c + 1);
            bs[r] = 0;
        }
    }
    return tot;
}
void solve() {
    bs.reset();
    for (int i = 0; i < 8; i++) {
        cin >> board[i];
    }
    cout << queens(0) << "\n";
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
