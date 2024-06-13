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
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> os_tree;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x1).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

struct node {
    bool b;
    vector<node*> child;
    node(bool b) : b(b), child(2, 0) {}
};

struct Trie {
    node* root;
    Trie() { root = new node(0); }
    void insert(int x) {
        node* cur = root;
        for (int j = 30; j >= 0; j--) {
            bool b = (x & (1 << j)) != 0;
            if (cur->child[b] == NULL) {
                cur->child[b] = new node(b);
            }
            cur = cur->child[b];
        }
    }
    int search(int x) {
        node* cur = root;
        int mx = 0;
        for (int j = 30; j >= 0; j--) {
            bool b = (x & (1 << j)) != 0;
            if (cur->child[1 ^ b] == NULL) {
                cur = cur->child[b];
            } else {
                cur = cur->child[1 ^ b];
                mx ^= 1 << j;
            }
        }
        return mx;
    }
};

void solve() {
    int n;
    cin >> n;
    Trie trie;
    int ans = 0;
    int pre = 0;
    trie.insert(0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pre ^= x;

        ans = max(ans, trie.search(pre));
        trie.insert(pre);
    }
    cout << ans << "\n";
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
