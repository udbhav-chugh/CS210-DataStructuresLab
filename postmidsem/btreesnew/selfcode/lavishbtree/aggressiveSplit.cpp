#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair

class node{
    int *keys;
    node **children;
    int minDegree;
    int size;
    bool isLeaf;

    friend class bTree;

    node(int minDegree, bool isLeaf){
        this->keys = new int[2*minDegree-1];
        this->children = new node *[2*minDegree];

        for(int i = 0; i < 2*minDegree; i++){
            children[i] = NULL;
        }

        this->minDegree = minDegree;
        this->size = 0;
        this->isLeaf = isLeaf;
    }

    void split(int k, node *head){
        node *newNode = new node(head->minDegree, head->isLeaf);
        newNode->size = minDegree-1;

        for(int i = 0; i < minDegree-1; i++){
            newNode->keys[i] = head->keys[i+minDegree];
        }

        if(!(head->isLeaf)){
            for(int i = 0; i < minDegree; i++){
                newNode->children[i] = head->children[i+minDegree];
            }
        }

        head->size = minDegree-1;

        for(int i = size; i >= k+1; i--) children[i+1] = children[i];
        children[k+1] = newNode;

        for(int i = size-1; i >= k; i--) keys[i+1] = keys[i];
        keys[k] = head->keys[minDegree-1];
        size++;
    }

    void insert(int key){
        int i = size-1;

        if(isLeaf){
            while(i >= 0 && keys[i] > key){
                keys[i+1] = keys[i];
                i--;
            }

            keys[i+1] = key;
            size++;
        }
        else{
            while(i >= 0 && keys[i] > key) i--;

            if(children[i+1]->size == 2*minDegree-1){
                split(i+1, children[i+1]);
                if(keys[i+1] < key) i++;
            }

            children[i+1]->insert(key);
        }
    }

    void deleteNode(){
        if(!isLeaf){
            for(int i = 0; i <= size; i++){
                children[i]->deleteNode();
            }
        }

        delete[] keys;
        delete[] children;
    }

    node *search(int key){
        int i = 0;
        while(i < size && key > keys[i]) i++;

        if(keys[i] == key) return this;

        if(isLeaf) return NULL;

        return children[i]->search(key);
    }

    void inorder(int depth){
        if(!isLeaf){
            int i = 0;
            for(; i < size; i++){
                children[i]->inorder(depth+1);
                printf("%3d", keys[i]);
                cout << " at depth " << depth << endl;
            }
            children[i]->inorder(depth+1);
        }
        else{
            for(int i = 0; i < size; i++){
                printf("%3d", keys[i]);
                cout << " at depth " << depth << endl;
            }
        }
    }
};

class bTree{
    node *root;
    int minDegree;

    public:

        bTree(int t){
            root = NULL;
            minDegree = t;
        }

        ~bTree(){
            if(root != NULL) root->deleteNode();
        }

        void insert(int key){
            if(root == NULL){
                root = new node(minDegree, true);
                root->insert(key);
                return;
            }

            if(root->size == 2*minDegree-1){
                node *newRoot = new node(minDegree, false);
                newRoot->children[0] = root;

                newRoot->split(0, root);

                if(newRoot->keys[0] < key){
                    newRoot->children[1]->insert(key);
                }
                else newRoot->children[0]->insert(key);

                root = newRoot;
            }
            else root->insert(key);
        }

        node *search(int key){
            if(root == NULL) return NULL;

            return root->search(key);
        }

        void inorder(){
            root->inorder(1);
        }
};

int main(){
    bTree *tree = NULL;
    int choice;
    while(1){
        cout << "1. Create a new tree\n";
        cout << "2. Add a new key to the tree\n";
        cout << "3. Search a key in the tree\n";
        cout << "4. Inorder traversal of the tree\n";
        cout << "5. Delete a key from the tree\n";
        cout << "Any other choice to exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 1){
            if(tree != NULL) delete tree;

            cout << endl;
            int t;
            cout << "Enter the value of minimum degree: ";
            cin >> t;
            tree = new bTree(t);
            cout << "B-tree created\n\n";
        }

        else if(choice == 2){
            cout << endl;

            if(tree == NULL){
                cout << "Create a new tree first\n\n";
                continue;
            }

            int key;
            cout << "Enter key to add: ";
            cin >> key;
            tree->insert(key);
            cout << "Key " << key << " inserted into the B-tree\n\n";
        }

        else if(choice == 3){
            cout << endl;
            if(tree == NULL){
                cout << "Create a new tree first\n\n";
                continue;
            }

            int key;
            cout << "Enter key to search: ";
            cin >> key;
            node *result = tree->search(key);

            if(result == NULL){
                cout << "Key " << key << "not found\n\n";
            }
            else cout << "Key " << key << " found\n\n";
        }

        else if(choice == 4){
            cout << endl;
            tree->inorder();
            cout << endl;
        }

        else if(choice == 5){

        }

        else{
            cout << endl;
            break;
        }
    }
}
