#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

/**************************************************************************************************************************/

void swap(int* a, int* b){
	int t = *a;
	*a = *b;
	*b = t;
}

/**************************************************************************************************************************/

void bubbleSort(vector<int> &v){
	int n=v.size();
	for(int i=0;i<n-1;i++){
		for (int j=0;j<n-i-1;j++){
			if(v[j]>v[j+1]){
				int temp=v[j];
				v[j]=v[j+1];
				v[j+1]=temp;
			} 
		}
	}
}
/**************************************************************************************************************************/

void selectionSort(vector<int> &v){
	int min_idx;
	int n=v.size();
	for(int i=0;i<n-1;i++){
		min_idx=i;
		for(int j=i+1;j<n;j++){
			if(v[j]<v[min_idx])
				min_idx=j;
		}
		if(min_idx!=i){
			int temp=v[min_idx];
			v[min_idx]=v[i];
			v[i]=temp;
		}
	}
}

/**************************************************************************************************************************/

void insertionSort(vector<int> &v){
	int n=v.size();
	int i,key,j;
	for(i=1;i<n;i++){
		key=v[i];
		j=i-1;
		while(j>=0&&v[j]>key){
			v[j+1]=v[j];
			j=j-1;
		}
		v[j+1]=key;
	}
}

/**************************************************************************************************************************/

void shellSort(vector<int> &v){
	int n=v.size();
	for (int h=n/2; h>0;h/=2){
		for (int i=h;i<n;i+=1){
			int temp=v[i];
			int j;
			for (j=i;j>=h && v[j-h]>temp;j-=h)
				v[j]=v[j-h];
			v[j]=temp;
		}
	}
}
/**************************************************************************************************************************/

int partition(vector<int> &v, int low, int high){
	int pivot = v[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++) {
		if (v[j] < pivot) {
			i++;
			swap(&v[i], &v[j]);
		}
	}
	swap(&v[i + 1], &v[high]);
	return (i + 1);
}

void quickSort(vector<int> &v, int low, int high){
	if (low < high) { 
		int pi = partition(v, low, high);
		quickSort(v, low, pi - 1);
		quickSort(v, pi + 1, high);
	}
}

/**************************************************************************************************************************/

void merge(vector<int> &v, int low, int high, int mid){
	int i, j, k, c[v.size()];
	i = low;
	k = low;
	j = mid + 1;
    	while (i <= mid && j <= high){
        	if (v[i] < v[j]){
            		c[k] = v[i];
            		k++;
            		i++;
        	}
        	else{
            		c[k] = v[j];
            		k++;
            		j++;
        	}
    	}
    	while (i <= mid){
        	c[k] = v[i];
        	k++;
        	i++;
    	}
    	while (j <= high){
        	c[k] = v[j];
        	k++;
        	j++;
    	}
    	for (i = low; i < k; i++){
        	v[i] = c[i];
    	}
}

void mergeSort(vector<int> &v, int low, int high){
	if(low<high){
		int mid;
		mid = (low+high)/2;
		mergeSort(v, low, mid);
		mergeSort(v, mid+1, high);
		merge(v,low,high,mid);
	}

}

/**************************************************************************************************************************/

int main(){

	// opening/creating a file to write the results in
	ofstream data ("data.csv", ios::app);

	data << "algorithm,time,n" << endl;

	int step = 10;

	for(int size = 10; size <= 1000000; size += step){

		if(size == 100){
			step *= 10;
		}
		if(size == 1000){
			step *= 10;
		}
		if(size == 10000){
			step *= 10;
		}

		if(size == 100000){
			step *= 10;
		}
		
		// creating a vector of size X
		vector<int> v(size);

		for(int i = 0; i < 3; i++){
					
			// creating random numbers and pushing them into the vector
			for(int j = 0; j < v.size(); j++){
				v[j] = rand();
			}

			// creating a vector to each algorithm so they don't use a sorted algorithm
			vector<int> vBubbleSort = v;
			vector<int> vSelectionSort = v;
			vector<int> vInsertionSort = v;
			vector<int> vShellSort = v;
			vector<int> vQuickSort = v;
			vector<int> vMergeSort = v;

		/**************************************************************************************************************************/

			auto start = high_resolution_clock::now();
			bubbleSort(vBubbleSort);
			auto end = high_resolution_clock::now();

			duration<double> duration = end - start;

			data << "bubble_sort, " << duration.count() << ", " << size << endl;

		/**************************************************************************************************************************/

			start = high_resolution_clock::now();
			selectionSort(vSelectionSort);
			end = high_resolution_clock::now();

			duration = end - start;

			data << "selection_sort, " << duration.count() << ", " << size << endl;

		/**************************************************************************************************************************/

			start = high_resolution_clock::now();
			insertionSort(vInsertionSort);
			end = high_resolution_clock::now();
			
			duration = end - start;

			data << "insertion_sort, " << duration.count() << ", " << size << endl;

		/**************************************************************************************************************************/

			start = high_resolution_clock::now();
			shellSort(vShellSort);
			end = high_resolution_clock::now();
			
			duration = end - start;
			
			data << "shell_sort, " << duration.count() << ", " << size << endl;

		/**************************************************************************************************************************/

			start = high_resolution_clock::now();
			quickSort(vQuickSort, 0, vQuickSort.size() - 1);
			end = high_resolution_clock::now();
			
			duration = end - start;

			data << "quick_sort, " << duration.count() << ", " << size << endl;
			
		/**************************************************************************************************************************/

			start = high_resolution_clock::now();
			mergeSort(vMergeSort, 0, vMergeSort.size() - 1);
			end = high_resolution_clock::now();

			duration = end - start;

			data << "merge_sort, " << duration.count() << ", " << size << endl;

		/**************************************************************************************************************************/
		};
	}

	data.close();

	return 0;
}
