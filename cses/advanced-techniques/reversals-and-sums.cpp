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
    int val;
    ll sum;
    bool rev;
    int weight, size;
    Node *left, *right;
    Node(int x) : val(x), weight(rand()), size(1), left(NULL), right(NULL), rev(0), sum(x) {}
};

inline int size(Node *node) { return node ? node->size : 0; }
inline ll sum(Node *node) { return node ? node->sum : 0; }

void pull(Node *node) {
    node->sum = node->val + sum(node->left) + sum(node->right);
    node->size = 1 + size(node->left) + size(node->right);
}

void push(Node *&node) {
    if (!node) return;
    if (node->rev) {
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
    pull(node);
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
    pull(node);
}

void reverse(Node *node, int l, int r) {
    Node *t1, *t2, *t3;
    split(node, t1, t2, r);
    split(t1, t1, t3, l - 1);
    t3->rev ^= 1;
    merge(node, t1, t3);
    merge(node, node, t2);
    // pull(node);
}

ll query(Node *node, int l, int r, int i, int j) {
    push(node);
    if (!node || r < i || l > j) {
        return 0;
    }
    if (i <= l && r <= j) {
        return node->sum;
    }
    int m = size(node->left) + l;
    int add = (i <= m && m <= j ? node->val : 0);
    return add + query(node->left, l, m - 1, i, j) + query(node->right, m + 1, r, i, j);
}
void solve() {
    int n, q;
    cin >> n >> q;

    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        merge(root, root, new Node(x));
    }

    while (q--) {
        int t, a, b;
        cin >> t >> a >> b;
        a--, b--;
        if (t == 1)
            reverse(root, a, b);
        else {
            cout << query(root, 0, n - 1, a, b) << "\n";
        }
    }
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
