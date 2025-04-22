#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    string key;
    Node* left;
    Node* right;
    Node(string item) {
        key = item;
        left = NULL;
        right = NULL;
    }
};

Node* insert(Node* node, string key) {
    if (node == NULL)
        return new Node(key);
    if (node->key == key) 
        return node; // Duplicate handling (no insertion)
    if (node->key < key)
        node->right = insert(node->right, key);
    else
        node->left = insert(node->left, key);
    return node;
}

Node* findMin(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

Node* deleteNode(Node* root, string key) {
    if (root == NULL) {
        cout << "No such word found in dictionary." << endl;
        return root;
    }
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL)
            return root->right;
        else if (root->right == NULL)
            return root->left;
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

Node* searchNode(Node* root, string key) {
    if (root == NULL || root->key == key)
        return root;
    if (root->key < key)
        return searchNode(root->right, key);
    return searchNode(root->left, key);
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
    }
}

void mirror(Node*& root) {
    if (root == NULL)
        return;
    swap(root->left, root->right);
    mirror(root->left);
    mirror(root->right);
}

Node* copyTree(Node* root) {
    if (root == NULL)
        return NULL;
    Node* newNode = new Node(root->key);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

void levelOrder(Node* root) {
    if (root == NULL)
        return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        cout << temp->key << " ";
        if (temp->left)
            q.push(temp->left);
        if (temp->right)
            q.push(temp->right);
    }
}

int main() {
    Node* root = NULL;
    int choice;
    string word;
    do {
        cout << "\nDictionary Operations:\n";
        cout << "1. Insert Word\n";
        cout << "2. Delete Word\n";
        cout << "3. Search Word\n";
        cout << "4. Display Dictionary (Inorder)\n";
        cout << "5. Display Dictionary (Preorder)\n";
        cout << "6. Display Dictionary (Postorder)\n";
        cout << "7. Mirror Dictionary\n";
        cout << "8. Copy Dictionary\n";
        cout << "9. Level Order Traversal\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter word to insert: ";
            cin >> word;
            root = insert(root, word);
            break;
        case 2:
            cout << "Enter word to delete: ";
            cin >> word;
            root = deleteNode(root, word);
            break;
        case 3:
            cout << "Enter word to search: ";
            cin >> word;
            if (searchNode(root, word))
                cout << word << " found in dictionary." << endl;
            else
                cout << word << " not found in dictionary." << endl;
            break;
        case 4:
            cout << "Dictionary (Inorder Traversal): ";
            inorder(root);
            cout << endl;
            break;
        case 5:
            cout << "Dictionary (Preorder Traversal): ";
            preorder(root);
            cout << endl;
            break;
        case 6:
            cout << "Dictionary (Postorder Traversal): ";
            postorder(root);
            cout << endl;
            break;
        case 7:
            mirror(root);
            cout << "Mirrored Dictionary (Inorder): ";
            inorder(root);
            cout << endl;
            break;
        case 8: {
            Node* copied = copyTree(root);
            cout << "Copied Dictionary (Inorder): ";
            inorder(copied);
            cout << endl;
            break;
        } 
        case 9:
            cout << "Level Order Traversal: ";
            levelOrder(root);
            cout << endl;
            break;
        case 10:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 10);
    return 0;
}
