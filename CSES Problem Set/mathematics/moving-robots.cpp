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

int K;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    cin >> K;

    ld dp[101][8][8], ans[8][8];

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            ans[i][j] = 1;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            memset(dp, 0, sizeof dp);
            dp[0][r][c] = 1;
            for (int k = 0; k < K; k++) {
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        int dir = 4;
                        if (i == 0 || i == 7) dir--;
                        if (j == 0 || j == 7) dir--;
                        for (int z = 0; z < 4; z++) {
                            int ni = i + di[z], nj = j + dj[z];
                            if (ni < 0 || nj < 0 || ni >= 8 || nj >= 8) continue;
                            dp[k + 1][ni][nj] += dp[k][i][j] / dir;
                        }
                    }
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    ans[i][j] *= (1 - dp[K][i][j]);
                }
            }
        }
    }
    ld res = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            res += ans[i][j];
        }
    }
    cout << fixed << setprecision(6) << res << "\n";
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
