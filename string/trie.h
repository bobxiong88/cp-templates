#include <bits/stdc++.h>

using namespace std;
template <typename T>
struct TrieNode{
    map<T, TrieNode *> chd;
    bool ed = false;

    TrieNode<T> *tryStep( T c) {
        if (!chd.count(c)) {
            return nullptr;
        }
        return chd[c];
    }

    void insert(const vector<T> &vT, int pos) {
        if (pos == vT.size()) {
            ed = true;
        } else {
            TrieNode<T> * nxt = tryStep(vT[pos]);
            if (nxt == nullptr) {
                nxt = new TrieNode();
                chd[vT[pos]] = nxt;
            }
            nxt->insert(vT, pos+1);
        }
    }

    bool find(const vector<T> &vT, int pos) {
        if (pos == vT.size()) {
            return ed;
        } else {
            auto nxt = tryStep(vT[pos]);
            if (!nxt) {
                return false;
            }
            return nxt->find(vT, pos+1);
        }
    }
};


template<typename T>
struct Trie{
    TrieNode<T> *root;
    TrieNode<T> *curr; 


    Trie() {
        root = new TrieNode<T>();
    }

    void insert(const vector<T> &vT) {
        root->insert(vT, 0);
    }

    bool find(const vector<T> &vT) {
        return root->find(vT, 0);
    }
};

vector<char> conv(const string &s) {
    return vector<char> (s.begin(), s.end());
}