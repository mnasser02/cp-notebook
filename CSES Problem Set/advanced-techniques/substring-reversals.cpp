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

struct Node {
    char val;
    bool rev;
    int weight, size;
    Node *left, *right;
    Node(char c) : val(c), weight(rand()), size(1), left(NULL), right(NULL), rev(false) {}
};

inline int size(Node *node) { return node ? node->size : 0; }

void push(Node *&node) {
    if (node && node->rev) {
        node->rev = 0;
        swap(node->left, node->right);
        if (node->left) node->left->rev ^= 1;
        if (node->right) node->right->rev ^= 1;
    }
}
void split(Node *node, Node *&left, Node *&right, int p) {
    push(node);
    if (!node) {
        left = right = NULL;
        return;
    }
    if (size(node->left) <= p) {
        split(node->right, node->right, right, p - size(node->left) - 1);
        left = node;
    } else {
        split(node->left, left, node->left, p);
        right = node;
    }
    node->size = 1 + size(node->left) + size(node->right);
}

void merge(Node *&node, Node *left, Node *right) {
    push(left), push(right);
    if (left == NULL) {
        node = right;
        return;
    }
    if (right == NULL) {
        node = left;
        return;
    }

    if (left->weight < right->weight) {
        merge(left->right, left->right, right);
        node = left;
    } else {
        merge(right->left, left, right->left);
        node = right;
    }
    node->size = 1 + size(node->left) + size(node->right);
}

void reverse(Node *node, int l, int r) {
    Node *t1, *t2, *t3;
    split(node, t1, t2, r);
    split(t1, t1, t3, l - 1);
    t3->rev ^= 1;
    merge(node, t1, t3);
    merge(node, node, t2);
}

ostream &operator<<(ostream &os, Node *node) {
    if (!node) return os;
    push(node);
    os << node->left;
    os << node->val;
    os << node->right;
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
        int a, b;
        cin >> a >> b;
        a--, b--;
        reverse(root, a, b);
    }
    cout << root << "\n";
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
