#include<iostream>
#include<string>
using namespace std;
template<typename V>

//MAPPING FROM STRING TO INTEGER

class MapNode{
public:
	string key;
	V value;
	MapNode *next;

	MapNode(string key,V value){
		this->key=key;
		this->value=value;
		this->next=NULL;
	}

	~MapNode(){
		delete this->next;
	}
};

template<typename V>
class OurMap{
	MapNode<V> **buckets;
	int count;
	int numBuckets;

	int func(string key){
		int len=0;
		for(int i=0;key[i];i++){
			len++;
		}
		int help=1;
		int ans=0;
		for(int i=len-1;i>=0;i--){
			ans+=(key[i]*help);
			help=help*2;
			ans=ans%(this->numBuckets);
		}
		return ans;
	}

public:
	OurMap(int n){
		this->buckets=new MapNode<V>*[n];
		this->numBuckets=n;
		this->count=0;
		for(int i=0;i<n;i++){
			buckets[i]=NULL;
		}
	}

	~OurMap(){
		for(int i=0;i<this->numBuckets;i++){
			delete buckets[i];
		}
		delete [] this->buckets;
	}

	int size(){
		return this->count;
	}

	void insert(string key,V value){
		int hashCode=func(key);
		int BucketIndex=(hashCode%(this->numBuckets));
		MapNode<V> *head=buckets[BucketIndex];
		while(head!=NULL){
			if(head->key==key){
				head->value=value;
				return;
			}
			head=head->next;
		}
		head=buckets[BucketIndex];
		MapNode<V> *node=new MapNode<V>(key,value);
		node->next=head;
		buckets[BucketIndex]=node;
		count++;
	}


	V remove(string key){
		int hsh=func(key);
		int index=hsh%numBuckets;
		MapNode<V> *head=buckets[index];
		if(head->key==key){
			buckets[index]=head->next;
			this->count--;
			return head->value;
		}
		MapNode<V> *prev=NULL;
		while(head!=NULL){
			if(head->key==key){
				prev->next=head->next;
				this->count--;
				return head->value;
			}
			if(prev==NULL){
				prev=head;
			}else{
				prev=prev->next;
			}
			head=head->next;
		}
		return 0;

	}


	V getValue(string key){
		int hsh=func(key);
		int index=(hsh%(numBuckets));
		MapNode<V> *head=buckets[index];
		while(head!=NULL){
			if(head->key==key){
				return head->value;
			}
			head=head->next;
		}
		return 0;
	}

	void display(){
		for(int i=0;i<this->numBuckets;i++){
			if(buckets[i]!=NULL){
				MapNode<V> *head=buckets[i];
				while(head!=NULL){
					cout<<head->key<<"->"<<head->value<<endl;
					head=head->next;
				}
			}
		}
	}



};


int main(){
	int n;
	cin>>n;
	OurMap<int> *m=new OurMap<int>(n);
	m->insert("abc",2);
	m->insert("abdg",4);
	m->insert("abdg",5);
	m->insert("abdbdsjb",78);
	m->insert("hdikj",40);
	// for(int i=0;i<10;i++){
	// 	string s;
	// 	cin>>s;
	// 	int h;
	// 	cin>>h;
	// 	m->insert(s,h);
	// }
	cout<<m->getValue("abc")<<endl;
	if(m->getValue("yuegvdyueu")==0){
		cout<<"Key Not present"<<endl;
	}
	cout<<"Size"<<m->size()<<endl;



	m->display();
	cout<<m->remove("abc")<<endl;
	m->display();


}