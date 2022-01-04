#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val, pr;
    Node* left;
    Node* right;
    Node(int value) {
        val = value;
        pr = rand();
        left = right = nullptr;
    }
};

Node* merge(Node* l, Node* r) {
    if(l == nullptr) return r;
    if(r == nullptr) return l;

    if(l->pr < r->pr) {
        l->right = merge(l->right, r);
        return l;
    } else {
        r->left = merge(l, r->left);
        return r;
    }
}

pair<Node*, Node*> split(Node* root, int val) {
    if(!root) return make_pair(nullptr, nullptr);

    if(root->val < val) {
        auto p = split(root->right, val);
        root->right = p.first;
        return make_pair(root, p.second);
    } else {
        auto p = split(root->left, val);
        root->left = p.second;
        return make_pair(p.first, root);
    }
}

Node* Insert(Node* root, int val) {
    auto p = split(root, val);
    return merge(merge(p.first, new Node(val)), p.second);
}
Node* Erase(Node* root, int val) {
    auto p1 = split(root, val);
    auto p2 = split(p1.second, val);
    if(p2.first)
        delete p2.first;
    return merge(p1.first, p2.second);
}

Node* Find(Node* root, int val) {
    if(!root || root->val == val) return root;

    if(root->val < val) {
        return Find(root->right, val);
    } else {
        return Find(root->left, val);
    }
}


int main() {
    srand(time(nullptr));
}