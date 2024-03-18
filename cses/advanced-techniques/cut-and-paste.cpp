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
#define LSOne(S) ((S) & -(S))

struct Node {
    char val;
    int weight, size;
    Node *left, *right;
    Node(char c) : val(c), weight(rand()), size(1), left(NULL), right(NULL) {}
};

inline int size(Node *treap) { return treap ? treap->size : 0; }

void split(Node *treap, Node *&left, Node *&right, int val) {
    if (!treap) {
        left = right = NULL;
        return;
    }

    if (size(treap->left) < val) {
        split(treap->right, treap->right, right, val - size(treap->left) - 1);
        left = treap;
    } else {
        split(treap->left, left, treap->left, val);
        right = treap;
    }
    treap->size = 1 + size(treap->left) + size(treap->right);
}

void merge(Node *&treap, Node *left, Node *right) {
    if (left == NULL) {
        treap = right;
        return;
    }
    if (right == NULL) {
        treap = left;
        return;
    }

    if (left->weight < right->weight) {
        merge(left->right, left->right, right);
        treap = left;
    } else {
        merge(right->left, left, right->left);
        treap = right;
    }
    treap->size = 1 + size(treap->left) + size(treap->right);
}

ostream &operator<<(ostream &os, Node *n) {
    if (!n) return os;
    os << n->left;
    os << n->val;
    os << n->right;
    return os;
}

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    Node *root = NULL;
    for (char c : s) {
        merge(root, root, new Node(c));
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        Node *a, *b, *c, *tmp;
        split(root, tmp, c, r + 1);
        split(tmp, a, b, l);
        merge(root, a, c);
        merge(root, root, b);
    }
    cout << root;
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
