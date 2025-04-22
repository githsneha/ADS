# include<iostream>
using namespace std;

class Multiplayer{
    public:
    int p_id, score, height;
    Multiplayer *left, *right;
    Multiplayer(int id, int score)
    {
        p_id = id;
        this->score = score;
        left = right = NULL;
        height = 1;
    }
};

int height(Multiplayer *node)
{
    if(node == NULL){
        return 0;
    }
    return node->height;
}

int balance(Multiplayer *node)
{
    if(node == NULL){
        return 0;
    }
    return height(node->left) - height(node->right);
}

Multiplayer *rightRotate(Multiplayer *y){
    Multiplayer *x = y->left;
    Multiplayer *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

Multiplayer *leftRotate(Multiplayer *x){
    Multiplayer *y = x->right;
    Multiplayer *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

Multiplayer *add(Multiplayer *root, int p_id, int score) 
{
    if(root == NULL)
    {
        return new Multiplayer(p_id, score);
    }
    if(score < root->score)
    {
        root->left = add(root->left, p_id, score);
    }
    else {
        root->right = add(root->right, p_id, score);
    }
    root->height = 1 + max(height(root->left), height(root->right));

    int bf = balance(root);
    if(bf > 1 && score < root->left->score){
        return rightRotate(root);
    }
    if(bf < -1 && score > root->right->score){
        return leftRotate(root);
    }
    if(bf > 1 && score > root->left->score){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(bf < -1 && score < root->right->score){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}  

void inorder(Multiplayer *node){
    if(node == NULL){
        return;
    }
    inorder(node->left);
    cout << node->p_id << "\t\t" << node->score << endl;
    inorder(node->right);
}

Multiplayer* search(Multiplayer* root, int p_id) {
    if (root == NULL || root->p_id == p_id)
        return root;
    if (p_id < root->p_id)
        return search(root->left, p_id);
    return search(root->right, p_id);
}

Multiplayer* minValueNode(Multiplayer* node) {
    Multiplayer* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Multiplayer* deleteNode(Multiplayer* root, int p_id)
{
    if (root == NULL) return root;

    if (p_id < root->p_id ){
        root->left = deleteNode(root->left, p_id);
    } else if (p_id > root->p_id) {
        root->right = deleteNode(root->right, p_id);
    } else {
        if(root->left == NULL || root->right == NULL)
        {
            Multiplayer *temp;
            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;
            
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            delete temp;
        }
        else {
            Multiplayer* temp = minValueNode(root->right);
            root->p_id = temp->p_id;
            root->score = temp->score;
            root->right = deleteNode(root->right, temp->p_id);
        }
    }
    if (root == NULL) return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int bf = balance(root);
    if (bf > 1 && balance(root->left) >= 0) return rightRotate(root);
    if (bf > 1 && balance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && balance(root->right) <= 0) return leftRotate(root);
    if (bf < -1 && balance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int main() {
    int ch, id, score;
    Multiplayer* root = NULL;
    do {
        cout << "\nMultiplayer Game System" << endl;
        cout << "1. Player Registration" << endl;
        cout << "2. Leaderboard Display" << endl;
        cout << "3. Search Player" << endl;
        cout << "4. Remove Player from Game" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            cout << "Enter player ID: ";
            cin >> id;
            cout << "Enter score: ";
            cin >> score;
            root = add(root, id, score);
            break;
        case 2:
            cout << "\nLeaderboard Display" << endl;
            cout << "Player ID\tScore\n";
            inorder(root);
            cout << endl;
            break;
        case 3:
            cout << "Enter player ID to search: ";
            cin >> id;
            if (search(root, id) != NULL)
                cout << "Player with ID " << id << " found!" << endl;
            else
                cout << "Player not found." << endl;
            break;
        case 4:
            cout << "Enter ID of player to remove: ";
            cin >> id;
            root = deleteNode(root, id);
            cout << "Player removed." << endl;
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    } while (ch != 5);

    return 0;
}
