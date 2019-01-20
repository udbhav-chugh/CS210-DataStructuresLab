#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back

class node{
    int roll;
    string name;
    node *next;

    friend class bucket;

    node(int r, string n){
        roll = r;
        name = n;
        next = NULL;
    }
};

class bucket{
    int bucketSize;
    node *head;
    node *rear;

    friend class hashmap;

    void insert(int r, string n){
        if(head == NULL){
            node *newNode = new node(r, n);
            head = newNode;
            rear = newNode;
            bucketSize++;
            return;
        }

        node *newNode = new node(r, n);
        rear->next = newNode;
        rear = newNode;
        bucketSize++;
    }

    string search(int r){
        node *temp = head;
        while(temp != NULL){
            if(temp->roll == r) return temp->name;
            temp = temp->next;
        }
        return "Not found";
    }

    void deleteRecord(int r){
        if(bucketSize == 0){
            cout << "Record not found!" << endl;
            return;
        }
        else if(bucketSize == 1){
            if(head->roll == r){
                cout << "Deleting record of " << head->name << endl;
                node *temp = head;
                head = NULL;
                rear = NULL;
                delete temp;
                bucketSize--;
                return;
            }
            else{
                cout << "Record not found!" << endl;
                return;
            }
        }

        node *prev = NULL;
        node *temp = head;
        if(head->roll == r){
            cout << "Deleted record of " << head->name << endl;
            head = head->next;
            delete temp;
            bucketSize--;
            return;
        }

        while(temp != NULL){
            if(temp->roll == r){
                if(temp->next == NULL){
                    rear = prev;
                    cout << "Deleted record of " << temp->name << endl;
                    delete temp;
                    bucketSize--;
                }
                else{
                    prev->next = temp->next;
                    cout << "Deleted record of " << temp->name << endl;
                    delete temp;
                    bucketSize--;
                }
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "Record not found!" << endl;
    }
};

class hashmap{
    int mapSize;
    bucket *map;

public:
    void insert(int r, string n){
        map[r%mapSize].insert(r, n);
    }

    hashmap(int size){
        mapSize = size;
        map = new bucket[size];
        for(int i = 0; i < size; i++){
            map[i].bucketSize = 0;
            map[i].head = NULL;
            map[i].rear = NULL;
        }
    }

    string search(int r){
        return map[r%mapSize].search(r);
    }

    void deleteRecord(int r){
        map[r%mapSize].deleteRecord(r);
    }
};

int main(){
    hashmap m(10);

    while(1){
        cout << "Enter choice of operation: " << endl;
        cout << "1: Enter student record" << endl;
        cout << "2: Delete student record" << endl;
        cout << "3: Search for a student record" << endl;
        cout << "-1: Quit" << endl << endl;
        int choice;
        cin >> choice;

        if(choice == -1) break;
        else if(choice == 1){

            cout << "Enter student's roll no. and name" << endl;
            cout << "Roll no.: ";
            int r;
            cin >> r;
            cout << "Name: ";
            string n;
            cin >> n;
            cout << endl;

            m.insert(r, n);

        }
        else if(choice == 2){

            cout << "Enter student's roll no." << endl;
            cout << "Roll no.: ";
            int r;
            cin >> r;
            m.deleteRecord(r);
            cout << endl;

        }
        else if(choice == 3){

            cout << "Enter student's roll no." << endl;
            cout << "Roll no.: ";
            int r;
            cin >> r;
            string n = m.search(r);
            if(n != "Not found"){
                cout << "Name: " << n << endl;
            }
            else cout << "Record not found!" << endl;
            cout << endl;

        }
        else{
            cout << "You entered wrong key." << endl;
        }
    }
}
