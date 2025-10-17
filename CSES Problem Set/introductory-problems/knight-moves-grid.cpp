#include <bits/stdc++.h>

using namespace std;

const int N = 1001;
int dist[N][N];
int dr[] = {1, 1, -1, -1, 2, 2, -2, -2}, dc[] = {2, -2, 2, -2, 1, -1, 1, -1};

int main() {
    int n;
    cin >> n;

    memset(dist, 0x1f, sizeof dist);
    dist[0][0] = 0;
    vector<array<int, 2>> q{{0, 0}};
    for (int i = 0; i < q.size(); i++) {
        auto [r, c] = q[i];
        for (int j = 0; j < 8; j++) {
            int nr = r + dr[j], nc = c + dc[j];
            if (nr < 0 || nc < 0 || nr >= n || nc >= n || dist[nr][nc] < 1e7) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push_back({nr, nc});
        }
    }
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cout << dist[r][c] << ' ';
        }
        cout << '\n';
    }

    return 0;
}