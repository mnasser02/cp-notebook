#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

// at depth i, longest suffix of s ending at i
// that is prefix of word in dict
const int S = 26;
struct AhoCorasick {
    vector<vi> AL, end;
    vector<array<int, S>> trie;
    vi fail, vis, ans;
    int cnt = 1;

    AhoCorasick() : trie(2), end(2) {}
    void add(int i, string& s) {
        int u = 1;
        for (char cc : s) {
            int c = cc - 'a';
            if (!trie[u][c]) {
                trie[u][c] = ++cnt;
                trie.push_back({});
                end.push_back({});
            }
            u = trie[u][c];
        }
        end[u].push_back(i);
        ans.push_back(0);
    }
    void build() {
        fail.resize(cnt + 1), AL.resize(cnt + 1);
        queue<int> q;

        for (int c = 0; c < S; c++) {
            if (trie[1][c]) {
                fail[trie[1][c]] = 1;
                q.push(trie[1][c]);
            } else {
                trie[1][c] = 1;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < 26; c++) {
                if (trie[u][c]) {
                    fail[trie[u][c]] = trie[fail[u]][c];
                    q.push(trie[u][c]);
                } else {
                    // failure built-in trie
                    trie[u][c] = trie[fail[u]][c];
                }
            }
        }

        // exit links reversed, proper suffix -> string
        for (int u = 2; u <= cnt; u++) {
            AL[fail[u]].push_back(u);
        }
    }

    void search(string& s) {
        vis.assign(cnt + 1, 0);
        int u = 1;
        for (char cc : s) {
            int c = cc - 'a';
            u = trie[u][c];
            vis[u] = 1;
        }
    }

    // handle exit links
    int dfs(int u) {
        int res = vis[u];
        for (int v : AL[u]) {
            res += dfs(v);
        }
        for (int i : end[u]) ans[i] = res;
        return res;
    }
};
void solve() {
    string s;
    int k;
    cin >> s >> k;
    AhoCorasick aho;
    for (int i = 0; i < k; i++) {
        string p;
        cin >> p;
        aho.add(i, p);
    }
    aho.build();
    aho.search(s);
    aho.dfs(1);
    for (int i = 0; i < k; i++) cout << (aho.ans[i] ? "YES\n" : "NO\n");
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
