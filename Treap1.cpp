#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val, pr;
    Node* left;
    Node* right;
    /////////////
    int size;
    int SUM;
    int MAX;
    int ADD;
    bool REV;
    Node(int value) {
        val = value;
        pr = rand();
        left = right = nullptr;
        size = 1;
        REV = false;
    }
};
void recalc(Node* root);

void push(Node* root) {
    root->val += root->ADD;
    if(root->REV) {
        swap(root->left, root->right);
    }
    if(root->left) {
        root->left->ADD += root->ADD;
        root->left->REV ^= root->REV;
        recalc(root->left);
    }
    if(root->right) {
        root->right->ADD += root->ADD;
        root->right->REV ^= root->REV;
        recalc(root->right);
    }
    root->REV = false;
    root->ADD = 0;
    recalc(root);
}

void recalc(Node* root) {
    root->size = 1;
    root->SUM = root->val;
    root->MAX = root->val;
    if(root->left) {
        root->size += root->left->size;
        root->SUM += root->left->SUM;
        root->MAX = max(root->MAX, root->left->MAX);
    }
    if(root->right) {
        root->size += root->right->size;
        root->SUM = root->right->SUM;
        root->MAX = max(root->MAX, root->right->MAX);
    }
    root->SUM += root->ADD*root->size;
    root->MAX += root->ADD;
}

Node* merge(Node* l, Node* r) {
    if(l == nullptr) return r;
    if(r == nullptr) return l;
    Node* p;
    if(l->pr < r->pr) {
        push(l);
        l->right = merge(l->right, r);
        p = l;
    } else {
        push(r);
        r->left = merge(l, r->left);
        p = r;
    }
    recalc(p);
    return p;
}

pair<Node*, Node*> split(Node* root, int count) {
    if(!root) return make_pair(nullptr, nullptr);
    if(count == 0) return make_pair(nullptr, root);
    push(root);
    if(!root->left) {
        auto p = split(root->right, count - 1);
        root->right = p.first;
        recalc(root);
        return make_pair(root, p.second);
    }
    if(root->left->size >= count) {
        auto p = split(root->left, count);
        root->right = p.second;
        recalc(root);
        return make_pair(p.first, root);
    } else {
        auto p = split(root->right, count - root->left->size - 1);
        root->right = p.first;
        recalc(root);
        return make_pair(root, p.second);
    }
}

Node* Insert(Node* root, int val, int ind) {
    auto p = split(root, ind - 1);
    return merge(merge(p.first, new Node(val)), p.second);
}
Node* Erase(Node* root, int ind) {
    auto p1 = split(root, ind - 1);
    auto p2 = split(p1.second, 1);
    if(p2.first)
        delete p2.first;
    return merge(p1.first, p2.second);
}

int Sum(Node*& root, int l, int r) {
    auto p1 = split(root, r);
    auto p2 = split(p1.first, l - 1);
    int res = p2.second->SUM;
    root = merge(merge(p2.first, p2.second), p1.second);
    return res;
}

void Rev(Node*& root, int l, int r) {
    auto p1 = split(root, r);
    auto p2 = split(p1.first, l - 1);
    p2.second->REV ^= true;
    root = merge(merge(p2.first, p2.second), p1.second);
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