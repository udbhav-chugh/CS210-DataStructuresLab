#include<iostream>
#include<ctime>
#include<cstdlib>
// #define arsize 9
using namespace std;

template <class T> T mini (T a, T b){
	if (a<b)
		return a;
	else 
		return b;
}


template <class T> void printarr (T input[], int arsize){
	for (int i = 0; i<arsize; i++)
		cout<<input[i]<<" ";
	cout<<endl;
}

template <class T> void swapel (T &a, T &b){
	T temp = a;
	a = b;
	b = temp;
}

template <class T> void bubblesort (T input[], int arsize){
	for (int i=0; i<arsize-1; i++){
		for (int j=0; j<arsize-i-1; j++)
			if (input[j] > input[j+1])
				swapel (input[j], input[j+1]);
	}
}

template <class T> void selectsort (T input[], int arsize){
	int max = -1, pos = -1,i,j;
	for (i=0; i<arsize; i++){
		pos = 0;
		max = input[0];
		for (j=1; j<arsize-i; j++){
			if (input[j] > max){
				max = input[j];
				pos = j;
			}
		}
		if (pos!= (arsize-i-1))
			swapel (input[pos], input[arsize-i-1]);
	}
}

template<class T> void selectshiftsort (T input[], int arsize){
	int i,j,pos=-1,min=-1;
	for (i=0; i<arsize; i++){
		pos = i;
		min = input[i];
		for (j=i+1; j<arsize; j++){
			if (min > input[j]){
				min = input[j];
				pos = j;
			}
		}
		if (pos != i){
			T temp = input[pos];
			for (j=pos; j>i; j--){
				input[j] = input[j-1];
			}
			input[i]= temp;
		}
	}
}

template<class T> void insertsort (T input[], int arsize){
	int i,j;
	for (i=1; i<arsize; i++){
		T temp = input[i];
		j=i-1;
		while (j>=0 && temp < input[j]){
			input[j+1] = input[j];
			j--;
		}
		j++;
		input[j] = temp;
		printarr(input,arsize);
	}
}

template<class T> void mergearr (T input[], int beg, int mid, int end){
	int i=beg, j=mid+1,k=0;
	T buff[end-beg+1];
	while (i<=mid && j<=end){
		if (input[i] <= input[j])
			buff[k++] = input[i++];
		else
			buff[k++] = input[j++];
	}
	while (i<=mid)
		buff[k++] = input[i++];
	while (j<=end)
		buff[k++] = input[j++];

	for (i=beg; i<=end; i++)
		input[i] = buff[i-beg];
}


template<class T> void mergesorttopdown (T input[], int beg, int end){
	int mid;
	if (end - beg > 0){
		mid = (end+beg)/2;
		mergesorttopdown (input,beg,mid);
		mergesorttopdown (input, mid+1,end);
		mergearr (input, beg,mid,end);
	}
}

template <class T> void mergesortbottomup (T input[], int beg, int end){
	int no = 2,mid;
	while (no<(end-beg+1)){
		for (int i=beg; i<=end; i+=no){
			mid = no/2;
			// cout<<"Before: ";
			// printarr(input+i, mini(no,end-i+1));		
			mergearr (input,i, i+mid-1, mini(i+no-1,end));		
			// cout<<"After: ";
			// printarr(input+i, mini(no,end-i+1));
		}
		no *=2;
	}
	mergearr (input,beg,beg+no/2-1,end);
}

template <class T> int partitiontwopass (T input[], int beg, int end){
	int piv = input[beg], small=beg;
	for(int i=beg+1; i<=end; i++){
		if (input[i]<piv)
			small++;
	}
	swapel(input[beg], input[small]);
	int i=beg, j=end;
	// input[small]=piv;
	while (i<small && j>small){
		if (input[i]>=piv && input[j]<piv){
			swapel (input[i],input[j]);
			i++;
			j--;
		}
		else if (input[i]<piv)
			i++;
		else if (input[j]>=piv)
			j--;
	}
	return small;

}

template <class T> int partitiononepass(T input[], int beg, int end){
	float piv = input[end];
	int j = beg-1;
	cout<<"Before: ";
	printarr(input,end-beg+1);
	for (int i=beg; i<=end-1; i++){
		if (int(input[i])<=int(piv)){
			j++;
			swapel (input[i],input[j]);
		}
	}
	// swapel (input[j+1], input[end]);
	for (int i=end; i>j+1; i--)
		input[i] = input[i-1];
	input[j+1] = piv;
	cout<<"After: ";
	printarr(input,end-beg+1);
	return (j+1);
}

template <class T> int partitionrandom(T input[], int beg, int end){
	srand(time(0));
	int pos = (beg + (rand() % (end-beg+1))); 
	swapel (input[pos], input[end]);
	partitiononepass (input,beg,end);
}


template <class T> void quicksort (T input[], int beg, int end){
	if (end - beg < 1)
		return;
	// int piv = input[beg];
	// int pi = partitiontwopass (input,beg,end);

	// int pi = partitiononepass (input,beg,end);
	int pi = partitionrandom (input,beg,end);
	if (beg < pi-1)
		quicksort (input, beg, pi-1) ;
	if (end > pi+1)
		quicksort (input, pi+1, end);
}

// template <class T> void partitionstable (T input[], int beg, int end, int &i, int &j){
// 	int piv = input[beg];
// 	int i=beg, j=end+1;
// 	p1 = beg; p2 = end+1;
	
// 	cout<<"Pivot: "<<piv<<endl;
// 	while(1){
// 		while (input[++i] < piv)
// 			if (i>=end)
// 				break;
// 		while (input[--j] > piv);
// 			// if (j<=beg)
// 			// 	break;
// 		cout<<"i: "<<i<<" j: "<<j<<endl;
// 		if (i>=j)
// 			break;
// 		swapel (input[i], input[j]);
// 		if (input[i]==piv){
// 			p1++;
// 			swapel(input[p1],input[i]);
// 		}
// 		if (input[j]==piv){
// 			p2--;
// 			swapel(input[j],input[p2]);
// 		}
// 	}

// 	swapel(input[beg], input[i]);

// 	j=i-1;
// 	for (int k=beg+1; k<p1; k++, j--)
// 		swapel(input[k],input[j]);
// 	j=i+1;
// 	for (int k=end; k>p2; k--, j++)
// 		swapel(input[k], input[j]);

// }

// template <class T> void quicksortstable (T input[], int beg, int end){
// 	if (end<=beg)
// 		return;
// 	int p1,p2;
// 	// cout<<"Before: ";
// 	// printarr(input,end-beg+1);
// 	partitionstable(input, beg, end, p1, p2);
// 	// cout<<beg<<" "<<p1<<" "<<p2<<" "<<end<<endl;
// 	// if (beg < p1 - 1)
// 	quicksortstable (input, beg, p2);
// 	// if (end > p2 + 1)
// 	quicksortstable (input, p1, end);
// 	// cout<<"After: ";
// 	// printarr(input,end-beg+1);
// 	}

int main(){
	float input[]={5,2.3,2.05,2.1,8,1,4,2.2,2.15};
	int arsize = 9;
	// int N;
	// int arsize;
	// cin>>arsize;
	// float input[arsize];
	// for (int i=0; i<arsize; i++)
	// 	cin>>input[i];
	// bubblesort(input,arsize);
	// selectsort(input,arsize);
	// selectshiftsort(input, arsize);
	// insertsort (input, arsize);
	// mergesorttopdown (input,0,arsize-1);
	// mergesortbottomup (input,0,arsize-1);
	quicksort(input,0,arsize-1);
	// quicksortstable(input,0,arsize-1);
	cout<<"Sorted Array: ";
	printarr(input, arsize);

	return 0;
}