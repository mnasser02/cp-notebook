// at step i, longest suffix of s ending at i
// that is prefix of word in dict
const int S = 26;
struct AhoCorasick {
    vector<vvector<int>> AL, end;
    vector<array<int, S>> trie;
    vector<int> fail, vis, ans;
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
    // build after adding all patterns
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
