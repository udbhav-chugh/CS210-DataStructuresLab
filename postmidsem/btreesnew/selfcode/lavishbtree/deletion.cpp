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

    void deleteKey(int key);

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

    int findKey(int key){
        int id=0;
        while(id < size && keys[id] < key) id++;
        return id;
    }

    int getPred(int id){
        node *curr = children[id];
        while(!(curr->isLeaf)) curr = curr->children[curr->size];
        return curr->keys[curr->size - 1];
    }

    int getSucc(int id){
        node *curr = children[id+1];
        while(!(curr->isLeaf)) curr = curr->children[0];
        return curr->keys[0];
    }

    void fill(int id){
        if(id != 0 && children[id-1]->size >= minDegree) borrowFromPrev(id);
        else if(id != size && children[id+1]->size >= minDegree) borrowFromNext(id);
        else{
            if(id != size) merge(id);
            else merge(id-1);
        }
    }

    void borrowFromPrev(int id){
        node *child = children[id];
        node *sibling = children[id-1];

        for(int i = child->size - 1; i >= 0; i--) child->keys[i+1] = child->keys[i];

        if(!(child->isLeaf)){
            for(int i = child->size; i>= 0; i--){
                child->children[i+1] = child->children[i];
            }
        }

        child->keys[0] = keys[id-1];

        if(!(child->isLeaf)) child->children[0] = sibling->children[sibling->size];

        keys[id-1] = sibling->keys[sibling->size - 1];
        child->size += 1;
        sibling->size -= 1;
    }

    void borrowFromNext(int id){
        node *child = children[id];
        node *sibling = children[id+1];

        child->keys[child->size] = keys[id];

        if(!(child->isLeaf)){
            child->children[child->size + 1] = sibling->children[0];
        }

        keys[id] = sibling->keys[0];

        for(int i = 1; i < sibling->size; i++){
            sibling->keys[i-1] = sibling->keys[i];
        }

        if(!(sibling->isLeaf)){
            for(int i = 1; i <= sibling->size; i++){
                sibling->children[i-1] = sibling->children[i];
            }
        }

        child->size += 1;
        sibling->size -= 1;
    }

    void merge(int id){
        node *child = children[id];
        node *sibling = children[id+1];

        child->keys[minDegree-1] = keys[id];

        for(int i = 0; i < sibling->size; i++){
            child->keys[i+minDegree] = sibling->keys[i];
        }

        if(!(child->isLeaf)){
            for(int i = 0; i <= sibling->size; i++){
                child->children[i+minDegree] = sibling->children[i];
            }
        }

        for(int i = id+1; i < size; i++) keys[i-1] = keys[i];
        for(int i = id+2; i <= size; i++) children[i-1] = children[i];

        child->size += sibling->size + 1;
        size--;

        delete sibling;
    }

    void removeFromLeaf(int id){
        for(int i = id+1; i < size; i++){
            keys[i-1] = keys[i];
        }
        size--;
    }

    void removeFromNonLeaf(int id){
        int key = keys[id];

        if(children[id]->size >= minDegree){
            int pred = getPred(id);
            keys[id] = pred;
            children[id]->deleteKey(pred);
        }
        else if(children[id+1]->size >= minDegree){
            int succ = getSucc(id);
            keys[id] = succ;
            children[id+1]->deleteKey(succ);
        }
        else{
            merge(id);
            children[id]->deleteKey(key);
        }
    }

};

void node::deleteKey(int key){
    int id = findKey(key);

    if(id < size && keys[id] == key){
        if(isLeaf) removeFromLeaf(id);
        else removeFromNonLeaf(id);
    }
    else{
        if(isLeaf){
            cout << "Key " << key << " not found\n";
            return;
        }

        bool flag = (id == size) ? true : false;
        if(children[id]->size < minDegree) fill(id);

        if(flag && id > size) children[id-1]->deleteKey(key);
        else children[id]->deleteKey(key);
    }
}

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

        void deleteKey(int key){
            if(root == NULL){
                cout << "B-tree is empty\n";
                return;
            }

            root->deleteKey(key);

            if(root->size == 0){
                node *temp = root;
                if(root->isLeaf) root = NULL;
                else root = root->children[0];

                delete temp;
            }

        }

        node *search(int key){
            if(root == NULL) return NULL;

            return root->search(key);
        }

        void inorder(){
            if(root == NULL){
                cout << "Tree is empty" << endl;
                return;
            }
            
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
            if(tree == NULL){
                cout << "Create a new tree first\n\n";
                continue;
            }

            cout << endl;
            tree->inorder();
            cout << endl;
        }

        else if(choice == 5){
            if(tree == NULL){
                cout << "Create a new tree first\n\n";
                continue;
            }

            int key;
            cout << "Enter key to delete: ";
            cin >> key;
            tree->deleteKey(key);
            cout << endl;
        }

        else{
            cout << endl;
            break;
        }
    }
}
