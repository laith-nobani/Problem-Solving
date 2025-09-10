struct Trie {
    struct Node {
        Node *ch[26];
        ll prefix, End;
        Node() {
            prefix = 0;
            End = 0;
            for (int i = 0; i < 26; ++i) { // 26 only (a–z)
                ch[i] = nullptr;
            }
        }
    };

    Node *root;
    Trie() {
        root = new Node();
    }

 ~Trie() {
        clear(root);
    }

    void clear(Node* node) {
        if (node == nullptr) return;
        for (int i = 0; i < 26; ++i) {
            clear(node->ch[i]);
        }
        delete node;
    }

    void insert(string st) {
        Node *cr = root;
        for (int i = 0; i < st.size(); ++i) {
            int idx = st[i] - 'a';
            if (cr->ch[idx] == nullptr) {
                cr->ch[idx] = new Node();
            }
            cr = cr->ch[idx];
            cr->prefix++;
        }
        cr->End++;
    }

    // Function to delete a word from the trie
    void deleteWord(string word)
    {
        Node* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->ch[index]) {
                return;
            }
            node = node->ch[index];
        }
        if (node->End > 0) {
            node->End--;  
        }
    }


    // Function to check if there is any word in the trie
    // that starts with the given prefix

    bool startsWith(string prefix)
    {
        Node* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!node->ch[index]) {
                return false;
            }
            node = node->ch[index];
        }
        return true;
    }

    ll cntWord(string st) {
        Node *cr = root;
        for (int i = 0; i < st.size(); ++i) {
            int idx = st[i] - 'a';
            if (cr->ch[idx] == nullptr)
                return 0;
            cr = cr->ch[idx];
        }
        return cr->End;
    }

    ll cntPrefix(string st) {
        Node *cr = root;
        for (int i = 0; i < st.size(); ++i) {
            int idx = st[i] - 'a';
            if (cr->ch[idx] == nullptr)
                return 0;
            cr = cr->ch[idx];
        }
        return cr->prefix;
    }

    void solve(string st){
            Node *cr = root;
            for (int i = 0; i < st.size(); ++i) {
                int idx = st[i] - 'a';
                if (cr->ch[idx] == nullptr)
                    return;
                cr = cr->ch[idx];
            }

             solve2(cr,st);
    }
    
    void solve2(Node *cr,string st){
        if(cr->End){
            ans.push_back(st);
        }
        for (int i = 0; i < 28-2; ++i) {
            if(cr->ch[i]!= nullptr)
               solve2(cr->ch[i],st+char(i+'a'));
        }
    }
 void solve3() {
        queue<pair<Node*,int>> q;
        q.push({root, 0});
        while(!q.empty()) {
            int sz = q.size();
            ll mx = 0;
            int level = q.front().second;
            for(int i = 0; i < sz; i++) {
                auto [node, c] = q.front();
                q.pop();
                for(int j = 0; j < 26; j++) {
                    if(node->ch[j]) {
                        mx = max(mx, node->ch[j]->prefix);
                        q.push({node->ch[j], c+1});
                    }
                }
            }

            mp[level + 1] = mx;
        }
    }
};
