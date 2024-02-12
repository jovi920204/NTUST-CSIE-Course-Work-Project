#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef enum {
    RED = 0,
    BLACK
} Color;

struct Node {
    Node(int _num) {
        num = _num;
        left = nullptr;
        right = nullptr;
        color = RED;
    }
    Color color;
    int num;
    Node* left;
    Node* right;
    Node* parent;
};

class Queue {
private:
    vector<Node*> data;

public:
    Node* front() {
        return this->data[0];
    }
    void push(Node* node) {
        data.push_back(node);
    };
    void pop() {
        vector<Node*> temp = data;
        data.clear();
        data.assign(temp.begin() + 1, temp.end());
    };
    bool empty() {
        return data.empty();
    };
};

vector<Node*> v;
Queue q;
vector<int> redTeam;
vector<int> blackTeam;

Node* insertValue(Node* node, int insertNum);
Node* colorChange(Node* node, int insertNum);
bool checkColorChange(Node* node);
Node* changeColor(Node* node);
Node* checkRoot(Node* root);
Node* rotate(Node* node);
void inorder(Node* node, string& output);
void levelorder(Node* root);
void sorted(vector<int> data);

int main() {
    int input;
    cin >> input;
    Node* root = new Node(input);
    checkRoot(root);
    while (cin >> input) {
        root = colorChange(root, input);
        root = rotate(root);
        root = insertValue(root, input);
        root = rotate(root);
        checkRoot(root);

        // string output;
        // inorder(root, output);
        // cout << output << endl;
    }
    levelorder(root);

    if (redTeam.size() < 4 || blackTeam.size() < 4) {
        cout << "No game";
    }
    else {
        int r_size = redTeam.size();
        vector<int> red_outfield = { redTeam[r_size - 3], redTeam[r_size - 2],redTeam[r_size - 1] };
        int red_jumpBall = redTeam[0];
        cout << "Red team: ";
        sorted(redTeam);
        cout << "outfield: ";
        for (int i = 0; i < red_outfield.size() - 1; i++) {
            cout << red_outfield[i] << ",";
        }
        cout << red_outfield[red_outfield.size() - 1] << endl;
        cout << "jump ball: " << red_jumpBall << endl;

        int b_size = blackTeam.size();
        vector<int> black_outfield = { blackTeam[b_size - 3],blackTeam[b_size - 2], blackTeam[b_size - 1] };
        int black_jumpBall = blackTeam[0];
        cout << "Black team: ";
        sorted(blackTeam);
        cout << "outfield: ";
        for (int i = 0; i < black_outfield.size() - 1; i++) {
            cout << black_outfield[i] << ",";
        }
        cout << black_outfield[black_outfield.size() - 1] << endl;
        cout << "jump ball: " << black_jumpBall;
    }
    return 0;
}

Node* colorChange(Node* node, int insertNum) {
    if (node == nullptr) {
        return nullptr;
    }
    // cout << checkColorChange(node);
    if (checkColorChange(node) == 1) {
        node = changeColor(node);
        return node;
    }

    if (insertNum > node->num) {
        node->right = colorChange(node->right, insertNum);
        if (node->right != nullptr) node->right->parent = node;
    }
    else {
        node->left = colorChange(node->left, insertNum);
        if (node->left != nullptr) node->left->parent = node;
    }
    return node;
}

Node* insertValue(Node* node, int insertNum) {
    if (node == nullptr) {
        return new Node(insertNum);
    }

    if (insertNum > node->num) {
        node->right = insertValue(node->right, insertNum);
        if (node->right != nullptr) node->right->parent = node;
    }
    else {
        node->left = insertValue(node->left, insertNum);
        if (node->left != nullptr) node->left->parent = node;
    }
    return node;
}

bool checkColorChange(Node* node) {
    if (node->left != nullptr && node->right != nullptr) {
        if (node->left->color == RED && node->right->color == RED) {
            return 1;
        }
    }
    return 0;
}

Node* changeColor(Node* node) {
    node->color = RED;
    node->left->color = BLACK;
    node->right->color = BLACK;
    return node;
}

Node* checkRoot(Node* root) {
    root->color = BLACK;
    root->parent = nullptr;
    return root;
}

Node* rotate(Node* node) {
    if (node == nullptr) return node;
    if (node->left != nullptr) {
        node->left = rotate(node->left);
    }
    if (node->right != nullptr) {
        node->right = rotate(node->right);
    }
    if (node->color == BLACK) { // left > right => go to left node
        if (node->left != nullptr && node->left->color == RED) {
            if (node->left->left != nullptr && node->left->left->color == RED) {
                // LL
                Node* bNode = node->left;
                node->left = bNode->right;
                if (bNode->right != nullptr) bNode->right->parent = node;
                bNode->right = node;

                node->color = RED;
                bNode->color = BLACK;
                return bNode;
            }
            if (node->left->right != nullptr && node->left->right->color == RED) {
                // LR
                Node* bNode = node->left;
                Node* cNode = bNode->right;
                node->left = cNode->right;
                if (cNode->right != nullptr) cNode->right->parent = node;
                bNode->right = cNode->left;
                if (cNode->left != nullptr) cNode->left->parent = bNode;
                cNode->right = node;
                cNode->left = bNode;
                if (node->parent != nullptr) cNode->parent = node->parent;
                bNode->parent = node->parent = cNode;

                cNode->color = BLACK;
                node->color = RED;
                return cNode;
            }
        }
        else if (node->right != nullptr && node->right->color == RED) {
            if (node->right->right != nullptr && node->right->right->color == RED) {
                // RR
                Node* bNode = node->right;
                node->right = bNode->left;
                if (bNode->left != nullptr) bNode->left->parent = node;
                bNode->left = node;

                node->color = RED;
                bNode->color = BLACK;
                return bNode;
            }
            if (node->right->left != nullptr && node->right->left->color == RED) {
                // RL
                Node* bNode = node->right;
                Node* cNode = bNode->left;
                node->right = cNode->left;
                if (cNode->left != nullptr) cNode->left->parent = node;
                bNode->left = cNode->right;
                if (cNode->right != nullptr) cNode->right->parent = bNode;
                cNode->right = bNode;
                cNode->left = node;
                if (node->parent != nullptr) cNode->parent = node->parent;
                bNode->parent = node->parent = cNode;

                cNode->color = BLACK;
                node->color = RED;
                return cNode;
            }
        }
    }
    return node;
}

void inorder(Node* node, string& output) {
    if (node == nullptr) return;
    inorder(node->left, output);
    if (node->color == RED) {
        output += "R";
    }
    else {
        output += "B";
    }
    output += to_string(node->num) + " ";
    inorder(node->right, output);
}
void levelorder(Node* root) {
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        v.push_back(curr);
        if (curr->color == RED) {
            redTeam.push_back(curr->num);
        }
        else {
            blackTeam.push_back(curr->num);
        }

        if (curr->left != nullptr) {
            q.push(curr->left);
        }
        if (curr->right != nullptr) {
            q.push(curr->right);
        }
    }
}

void sorted(vector<int> data) {
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data.size() - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                int temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < data.size() - 1; i++) {
        cout << data[i] << ",";
    }
    cout << data[data.size() - 1] << endl;
}