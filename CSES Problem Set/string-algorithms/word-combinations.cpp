#include <bits/stdc++.h>

#pragma GCC optimize("O3")

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

const int M = 1e9 + 7, N = 5001;

struct node {
    char c;
    bool exist;
    vector<node *> child;
    node(char c) : c(c), exist(0), child(26, 0) {}
};

struct Trie {
    node *root;
    Trie() { root = new node('!'); }
    void insert(string &s) {
        node *cur = root;
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if (cur->child[c] == NULL) {
                cur->child[c] = new node(s[i]);
            }
            cur = cur->child[c];
        }
        cur->exist = 1;
    }
    vi EOWpos(string &s, int l) {
        node *cur = root;
        vi v;
        for (int i = l; i < s.size(); i++) {
            int c = s[i] - 'a';
            if (cur->child[c] == NULL) {
                break;
            }
            cur = cur->child[c];
            if (cur->exist) v.push_back(i + 1);
        }
        return v;
    }
};

void solve() {
    string s;
    cin >> s;
    int k;
    cin >> k;
    int n = s.size();

    Trie trie;
    while (k--) {
        string t;
        cin >> t;
        trie.insert(t);
    }

    vi dp(n + 1);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        vi v = trie.EOWpos(s, i);
        for (int j : v) {
            dp[i] += dp[j];
            dp[i] %= M;
        }
    }
    cout << dp[0] << "\n";
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
