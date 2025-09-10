struct BTrie {
    struct Node {
        Node *ch[2];
        int cnt[2];
        Node() {
            ch[0] = nullptr;
            ch[1] = nullptr;
            cnt[0] = 0;
            cnt[1] = 0;
        }
    };

    Node* root = new Node();

    ~BTrie() {
        clear(root);
    }

    void clear(Node* node) {
        if (node == nullptr)
            return;
        for (int i = 0; i < 2; ++i) {
            clear(node->ch[i]);
        }
        delete node;
    }
    void insert(int n) {
        Node *c = root;
        for (int i = 29; i >= 0; --i) {
            int idx = (n >> i) & 1;
            if (c->ch[idx] == nullptr) {
                c->ch[idx] = new Node();
            }
            c->cnt[idx]++;
            c = c->ch[idx];
        }
    }

    void Delete(int n) {
        Node *c = root;
        for (int i = 29; i >= 0; --i) {
            int idx = (n >> i) & 1;
            c->cnt[idx]--;
            if (c->cnt[idx] == 0) {
                delete c->ch[idx];
                c->ch[idx] = nullptr;
                return;
            }
            c = c->ch[idx];
        }
    }
    ll solve(int n){
        Node* c = root;
        bitset<30> N(n);
        bitset<30> ans(0);
        for (int i = 29; i >= 0; --i) {
            int bit = N[i];
            if(bit == 0){
                if(c->ch[1] != nullptr){
                    c = c->ch[1];
                    ans[i] = 1;
                } else {
                    c = c->ch[0];
                    ans[i] = 0;
                }
            } else { // bit == 1
                if(c->ch[0] != nullptr){
                    c = c->ch[0];
                    ans[i] = 0;
                } else {
                    c = c->ch[1];
                    ans[i] = 1;
                }
            }
        }
        return ans.to_ullong();
    }
};
