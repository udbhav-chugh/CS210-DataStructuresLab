#include <bits/stdc++.h>
using namespace std;

class node{
    int data;
    int leftHeight;
    int rightHeight;
    node *parent;
    node *left;
    node *right;

    friend class avlTree;

    node(int key){
        data = key;
        leftHeight = 0;
        rightHeight = 0;
        parent = NULL;
        left = NULL;
        right = NULL;
    }

    void updateHeight(){
        if(left == NULL) leftHeight = 0;
        else{
            leftHeight = max(left->leftHeight, left->rightHeight)+1;
        }

        if(right == NULL) rightHeight = 0;
        else{
            rightHeight = max(right->leftHeight, right->rightHeight)+1;
        }
    }
};

class avlTree{
    node *root;

    node *rotateLeft(node *head){
        node *a = head;
        node *b = head->right;
        node *parent = head->parent;

        if(parent != NULL){
            if(parent->right == a) parent->right = b;
            else parent->left = b;
        }
        b->parent = parent;


        a->right = b->left;
        if(b->left != NULL) b->left->parent = a;

        b->left = a;
        a->parent = b;

        a->updateHeight();
        b->updateHeight();

        head = b;
        return head;
    }

    node *rotateRight(node *head){
        node *a = head;
        node *b = head->left;
        node *parent = head->parent;

        if(parent != NULL){
            if(parent->left == a) parent->left = b;
            else parent->right = b;
        }
        b->parent = parent;

        a->left = b->right;
        if(b->right != NULL) b->right->parent = a;

        b->right = a;
        a->parent = b;

        a->updateHeight();
        b->updateHeight();

        head = b;
        return head;
    }

    void rebalance(node *head){
        head->updateHeight();

        int balanceFactor = head->rightHeight - head->leftHeight;

        if(balanceFactor == -2){
            if(head->left->leftHeight >= head->left->rightHeight){
                node *newHead = rotateRight(head);
                head = newHead;
                cout << "Rotate Right" << endl;
            }
            else{
                cout << "Rotate Left Then Right" << endl;
                node *newLeft = rotateLeft(head->left);
                head->left = newLeft;
                node *newHead = rotateRight(head);
                head = newHead;
            }
        }
        else if(balanceFactor == 2){
            if(head->right->rightHeight >= head->right->leftHeight){
                node *newHead = rotateLeft(head);
                head = newHead;
                cout << "Rotate Left" << endl;
            }
            else{
                cout << "Rotate Right Then Left" << endl;
                node *newRight = rotateRight(head->right);
                head->right = newRight;
                node *newHead = rotateLeft(head);
                head = newHead;
            }
        }

        if(head->parent == NULL) root = head;
        else{
            rebalance(head->parent);
        }
    }

    void inorder(node *head){
        if(head == NULL) return;

        inorder(head->left);

        cout << head->data << " ";

        if(head->left != NULL) cout << "(" << head->left->data << ") ";
        else cout << "(-) ";

        if(head->right != NULL) cout << "(" << head->right->data << ")" << endl;
        else cout << "(-)" << endl;

        inorder(head->right);
    }

    node *maximum(node *head){
        node *temp = head;
        while(temp->right != NULL) temp = temp->right;
        return temp;
    }

    node *predecessor(node *head){
        if(head->left != NULL) return maximum(head->left);

        node *temp = head;
        node *parentNode = head->parent;
        while(parentNode != NULL && parentNode->right != temp){
            temp = parentNode;
            parentNode = temp->parent;
        }
        return parentNode;
    }

    void deleteNode(node *head){
        if(head != NULL){
            deleteNode(head->left);
            deleteNode(head->right);
            delete head;
        }
    }

public:
    avlTree(){
        root = NULL;
    }

    ~avlTree(){
        deleteNode(root);
    }

    bool insertNode(int key){
        if(root == NULL){
            root = new node(key);
            return true;
        }

        node *prev = NULL;
        node *temp = root;

        while(temp != NULL){
            if(temp->data == key) return false;

            prev = temp;

            if(key < temp->data) temp = temp->left;
            else temp = temp->right;
        }

        node *newNode = new node(key);
        newNode->parent = prev;
        if(key > prev->data) prev->right = newNode;
        else prev->left = newNode;

        rebalance(prev);

        return true;
    }

    void inorder(){
        inorder(root);
        cout << endl;
    }

    node *search(int key){
        node *temp = root;
        while(temp != NULL){
            if(temp->data == key) return temp;

            if(key < temp->data) temp = temp->left;
            else temp = temp->right;
        }

        return NULL;
    }

    void deleteKey(node *temp){
        node *parentNode = temp->parent;

        if(temp->left == NULL && temp->right == NULL){

            if(temp == root){
                root = NULL;
                return;
            }

            parentNode = temp->parent;
            if(parentNode->left == temp) parentNode->left = NULL;
            else parentNode->right = NULL;

            delete temp;

            rebalance(parentNode);
            return;
        }
        else if(temp->left == NULL || temp->right == NULL){

            if(temp == root){
                root = temp->left != NULL ? temp->left : temp->right;
                delete temp;
                return;
            }

            parentNode = temp->parent;
            node *childNode = temp->left == NULL ? temp->right : temp->left;

            if(parentNode->left == temp){
                parentNode->left = childNode;
                childNode->parent = parentNode;
            }
            else{
                parentNode->right = childNode;
                childNode->parent = parentNode;
            }

            delete temp;
            rebalance(parentNode);
            return;
        }

        node *pred = predecessor(temp);
        int swap = temp->data;
        temp->data = pred->data;
        pred->data = swap;

        deleteKey(pred);
    }
};

int main(){
    avlTree *tree = new avlTree();

    int choice, key;
    while(true){
        cout << "1. Create new tree" << endl;
        cout << "2. Add new key to the tree" << endl;
        cout << "3. Search a key in the tree" << endl;
        cout << "4. Delete a key from the tree" << endl;
        cout << "5. Inorder traversal of the tree" << endl;
        cout << "Any other choice to exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        if(choice == 1){
            if(tree != NULL){
                delete tree;
            }
            tree = new avlTree();
        }
        else if(choice == 2){
            if(tree == NULL){
                cout << "Create a tree first" << endl;
                continue;
            }
            cout << "Enter key to add: ";
            cin >> key;
            if(tree->insertNode(key)){
                cout << "Inserted key: " << key << endl;
            }
            else cout << "Could not insert key" << endl;
            cout << endl;
        }
        else if(choice == 3){
            if(tree == NULL){
                cout << "Create a new tree first" << endl;
                continue;
            }
            cout << "Enter key to search: ";
            cin >> key;
            node *temp = tree->search(key);
            if(temp == NULL) cout << "Key " << key << " not found" << endl << endl;
            else cout << "Key " << key << " found" << endl << endl;
        }
        else if(choice == 4){
            if(tree == NULL){
                cout << "Create a new tree first" << endl;
                continue;
            }
            cout << "Enter key to delete: ";
            cin >> key;

            node *temp = tree->search(key);
            if(temp == NULL) cout << "Key " << key << " not found" << endl;
            else tree->deleteKey(temp);
            cout << endl;
        }
        else if(choice == 5){
            if(tree == NULL){
                cout << "Create a new tree first" << endl;
                continue;
            }
            tree->inorder();
        }
        else break;
    }
}
