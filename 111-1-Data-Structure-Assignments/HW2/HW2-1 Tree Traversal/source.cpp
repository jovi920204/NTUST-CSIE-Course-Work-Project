#include <iostream>
#include <string>
using namespace std;

struct Node{
    Node(int _num){
        num = _num;
        left = nullptr;
        right = nullptr;
    }
    int num;
    Node* left;
    Node* right;
};

class Stack
{
private:
    Node* array[1000];
    int topIndex;
public:
    Stack(){ topIndex = -1; };
    ~Stack(){};
    void push(Node* node){
        array[++topIndex] = node;
    }
    void pop(){
        if (topIndex != -1){
            topIndex--;
        }
    }
    bool isEmpty(){
        if (topIndex != -1) return 0;
        return 1;
    }
    Node* top(){
        return array[topIndex];
    }
};

Node* insert(Node* node, int insertNum);
void inorder(Node* node, string& output);
void preorder(Node* node, string& output);
void postorder(Node* node, string& output);
int toNumber(string str);

int main(){
    string inputString;
    while(getline(cin, inputString)){
        inputString += " ";
        Node* root = nullptr;
        string numString = "";
        for (int i=0;i<inputString.size();i++){
            if (inputString[i] == ' '){
                root = insert(root, toNumber(numString));
                numString = "";
                continue;
            }
            numString += inputString[i];
        }
        string inorderOutput = "";
        string preorderOutput = "";
        string postorderOutput = "";
        inorder(root, inorderOutput);
        preorder(root, preorderOutput);
        postorder(root, postorderOutput);
        cout << inorderOutput.substr(0, inorderOutput.size()-1) << endl;
        cout << preorderOutput.substr(0, preorderOutput.size()-1) << endl;
        cout << postorderOutput.substr(0, postorderOutput.size()-1);
    }
}

int toNumber(string str){
    int len = str.size();
    int retNum = 0;
    for (int i=len-1, weight = 1;i>=0;i--, weight*=10){
        retNum += (str[i]-'0')*weight;
    }
    return retNum;
}

Node* insert(Node* node, int insertNum){
    if (node == nullptr){
        return new Node(insertNum);
    }
    if (insertNum > node->num){
        node->right = insert(node->right, insertNum);
    }
    else{
        node->left = insert(node->left, insertNum);
    }
    return node;
}

void inorder(Node* node, string& output){
    if (node == nullptr) return;
    inorder(node->left, output);
    output += to_string(node->num) + " ";
    inorder(node->right, output);
}

void preorder(Node* node, string& output){
    if (node == nullptr) return;
    output += to_string(node->num) + " ";
    preorder(node->left, output);
    preorder(node->right, output);
}
void postorder(Node* node, string& output){
    if (node == nullptr) return;
    postorder(node->left, output);
    postorder(node->right, output);
    output += to_string(node->num) + " ";
}