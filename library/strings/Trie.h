struct node {
    char c;
    bool exist;
    vector<node*> child;
    node(char c) : c(c), exist(0), child(26, 0) {}
};

struct Trie {
    node* root;
    Trie() { root = new node('!'); }
    void insert(string& s) {
        node* cur = root;
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if (cur->child[c] == NULL) {
                cur->child[c] = new node(s[i]);
            }
            cur = cur->child[c];
        }
        cur->exist = 1;
    }
    bool search(string& s) {
        node* cur = root;
        for (int i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            if (cur->child[c] == NULL)
                return false;
            cur = cur->child[c];
        }
        return cur->exist;
    }
    bool starts_with(string& s) {
        node* cur = root;
        for (int i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            if (cur->child[c] == NULL)
                return false;
            cur = cur->child[c];
        }
        return true;
    }
};
