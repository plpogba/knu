#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

typedef struct node {
    char c;
    int freq;
    node* left;
    node* right;
} node;

struct cmp {
    bool operator()(node* a, node* b) const {
        return a->freq > b->freq;
    }
};

void preorder(node* root, bool& isFirst);
void inorder(node* root, bool& isFirst);
void encode(node* root, string code, map<char, string>& encoder);
string decode(node* root, string s);

int main() {
    int n, m, k, tmpi;
    priority_queue<node*, vector<node*>, cmp> pq;

    if (!(cin >> n)) return 0;

    vector<char> chars(n);
    for (int i = 0; i < n; i++) cin >> chars[i];
    
    for (int i = 0; i < n; i++) {
        cin >> tmpi;
        node* newNode = new node;
        newNode->c = chars[i];
        newNode->freq = tmpi;
        newNode->left = nullptr;
        newNode->right = nullptr;
        pq.push(newNode);
    }

    while (pq.size() > 1) {
        node* a = pq.top(); pq.pop();
        node* b = pq.top(); pq.pop();

        node* parent = new node;
        parent->c = '+';
        parent->freq = a->freq + b->freq;
        parent->left = a;
        parent->right = b;
        
        pq.push(parent);
    }
    
    node* header = pq.top();

    

    cin >> m;
    vector<string> stringlist(m);
    for (int i = 0; i < m; i++) cin >> stringlist[i];

    cin >> k;
    vector<string> encodedlist(k);
    for (int i = 0; i < k; i++) cin >> encodedlist[i];

    bool isFirstPre = true;
    preorder(header, isFirstPre);
    cout << endl;

    bool isFirstIn = true;
    inorder(header, isFirstIn);
    cout << endl;
    map<char, string> encoder;
    encode(header, "", encoder);

    for (const string& str : stringlist) {
        for (char ch : str) cout << encoder[ch];
        cout << endl;
    }

    for (int i = 0; i < k; i++) {
        cout << decode(header, encodedlist[i]);
        if (i != k - 1) cout << endl; 
    }
    cout << endl;

    return 0;
}

void preorder(node* root, bool& isFirst) {
    if (root == nullptr) return;
    
    if (!isFirst) cout << " ";
    cout << root->c << ":" << root->freq;
    isFirst = false;

    preorder(root->left, isFirst);
    preorder(root->right, isFirst);
}

void inorder(node* root, bool& isFirst) {
    if (root == nullptr) return;
    
    inorder(root->left, isFirst);
    
    if (!isFirst) cout << " ";
    cout << root->c << ":" << root->freq;
    isFirst = false;

    inorder(root->right, isFirst);
}

void encode(node* root, string code, map<char, string>& encoder) {
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr) {
        encoder[root->c] = code;
        return;
    }
    encode(root->left, code + "0", encoder);
    encode(root->right, code + "1", encoder);
}

string decode(node* root, string s) {
    string result = "";
    node* cur = root;
    for (char bit : s) {
        if (bit == '0') cur = cur->left;
        else cur = cur->right;

        if (cur->left == nullptr && cur->right == nullptr) {
            result += cur->c;
            cur = root;
        }
    }
    return result;
}