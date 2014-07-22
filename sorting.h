
#ifndef _SORTING_H_
#define _SORTING_H_

#include <memory>
#include <random>
#include <time.h>
//-------------bubble sort----------------------------
template<typename T>
void bubble_sort(T a[],int n)
{
	bool tag=true;
	for(int i=0;i<n-1&&tag;i++)
	{
		tag=false;
		for (int j=n-1;j>i;j--)
		{
			if(a[j]<a[j-1])
			{
				T temp=a[j];
				a[j]=a[j-1];
				a[j-1]=temp;
				tag=true;
			}

		}
	}
}

//-------------simple Select sort---------------------
//交换次数少，最好0次，最多n-1次
//比较次数多，最好最差都是n(n-1)/2
//性能略优于冒泡排序
template<typename T>
void select_sort(T a[],int n)
{
	int minIdx;
	for (int i=0;i<n-1;i++)
	{
		minIdx=i;
		for (int j=i+1;j<n;j++)
		{
			if(a[j]<a[minIdx])
			{
				minIdx=j;
			}
		}
		if(minIdx!=i)
		{
			T temp=a[i];
			a[i]=a[minIdx];
			a[minIdx]=temp;
		}
	}
}

//-------------insertion sort-------------------------
template<typename T>
void insertion_sort(T a[], int n)
{
	T tm;
	for (int i=0; i!=n; ++i) {
		tm = a[i];
		int k=i;
		for (; k>0; --k) {
			if (tm >= a[k-1])
				break;
			a[k] = a[k-1];
		}
		a[k] = tm;
	}
}
//with guard a[0]
template<typename T>
void insertion_sort_guard(T a[],int n)
{
	for(int i=2;i<=n;i++)
	{
		if (a[i]<a[i-1])
		{
			a[0]=a[i];
			int j;
			for (j=i-1;a[j]>a[0];j--)
			{
				a[j+1]=a[j];
			}
			a[++j]=a[0];
		}
	}
}
//---------------------------------------------------

//-----------------shell sort------------------------
template<typename T>
void shellsort(T a[], int n)
{
	for (int increment=n/2; increment>=1; increment/=2) {
		if (increment%2 == 0) increment++;
		for (int i=increment; i<n; ++i) {
			T tm = a[i];
			int j=i;
			for (; j>=increment; j-=increment) {
				if (tm >= a[j-increment])
					break;
				a[j] = a[j-increment];
			}
			a[j] = tm;
		}//for
	}//for
}
//----------------------------------------------------

//-----------------heap sort--------------------------
template<typename T>
void max_heapfy(T a[],int i,int heapsize)
{
	int left=2*i+1;
	int right=2*i+2;
	int large=i;
	if (left<=heapsize&&a[left]>a[i])
	{
		large=left;
	}
	if (right<=heapsize&&a[right]>a[large])
	{
		large=right;
	}
	if(large!=i)
	{
		T temp=a[i];
		a[i]=a[large];
		a[large]=temp;
		max_heapfy(a,large,heapsize);
	}
}

template<typename T>
void build_max_heap(T a[],int n)
{
	for (int i=n/2-1;i>=0;i--)//从n/2开始是叶子
	{
		max_heapfy(a,i,n);
	}
}

template<typename T>
void heap_sort(T a[],int n) 
{
	build_max_heap(a,n);
	for (int i=n-1;i>0;i--)
	{
		T temp=a[i];
		a[i]=a[0];
		a[0]=temp;
		max_heapfy(a,0,i-1);
	}
}
//--------------------------------------------------

//----------------merge sort------------------------

template<typename T>
void merge_array(T a[], int beg, int end)
{
	int center = (beg + end) / 2;
	for (int i=beg, j=center+1; i<=end && j<=end;) {
		if (a[i] > a[j]) {
			T tm = a[j];
			for(int k=j; k!=i; --k)
				a[k] = a[k-1];
			a[i] = tm;
			j++;
			i++;
		}
		else
			i++;
	}
}

template<typename T>
void m_sort(T a[], int left, int right)
{
	if (left < right) {
		int center = (left + right) / 2;
		m_sort(a,left,center);
		m_sort(a,center+1,right);
		merge_array(a,left,right);
	}
}

template<typename T>
void mergesort(T a[], int n)
{
	m_sort(a,0,n-1);
}
//--------------------------------------------------

//------------------quick sort----------------------
template<typename T>
int partion(T a[],int begin,int end)
{
	T pivot=a[end];
	int i=begin-1;//比pivot小的元素序列末尾
	for (int j=begin;j<end;j++)
	{
		if (a[j]<=pivot)
		{
			i++;
			T temp=a[j];
			a[j]=a[i];
			a[i]=temp;
		}

	}
	i++;
	T temp=a[i];
	a[i]=a[end];
	a[end]=temp;
	return i;
}

template<typename T>
void quick_sort(T a[],int begin,int end)
{
	if(begin<end)
	{
		int q=partion(a,begin,end);
		quick_sort(a,begin,q-1);
		quick_sort(a,q+1,end);
	}
}
//--------------randomized quick sort----------------
template<typename T>
int randomized_partition(T a[],int begin,int end)
{
	srand((unsigned int)time(0));
	int i=rand()%(end-begin+1)+begin;
	T temp=a[end];
	a[end]=a[begin];
	a[begin]=temp;
	return partion(a,begin,end);
}

template<typename T>
void randomized_quicksort(T a[],int begin,int end)
{
	if (begin<end)
	{
		int q=randomized_partition(a,begin,end);
		randomized_quicksort(a,begin,q-1);
		randomized_quicksort(a,q+1,end);
	}
}
//---------------------------------------------------
//--------------------------------------------------
//------------------counting sort--------------------
//假设n个输入元素每个都是0~k之间的整数，k=O(n)
template<typename T>
void counting_sort(T a[],int n)
{
	//找最大元素
	int max=0;
	for (int i=0;i<n;i++)
	{
		if (a[i]>max)
		{
			max=a[i];
		}
	}
	int* count=new int[max+1];//0 to max
	int* tempResult=new int[n];
	memset(count,0,sizeof(int)*(max+1));
	memset(tempResult,0,sizeof(int)*n);
	for (int j=0;j<n;j++)//计数
	{
		count[a[j]]++;
	}
	
	for (int k=1;k<=max;k++)//累积
	{
		count[k]=count[k]+count[k-1];
	}
	for (int l=n-1;l>=0;l--)//从后往前实现,保证稳定性
	{
		tempResult[count[a[l]]-1]=a[l];//注意tempResult从0~n-1
		count[a[l]]--;
	}
	for (int m=0;m<n;m++)
	{
		a[m]=tempResult[m];
	}
	delete[] count;
	delete[] tempResult;
}
//---------------------------------------------------

//---------------------------------------------------
//--------------radix_sort-----------------
#define MAX 20
#define BASE 10
void radix_sort(int *a, int n) {
	int i, b[MAX], m = a[0], exp = 1;

	for (i = 1; i < n; i++) {
		if (a[i] > m) {
			m = a[i];
		}
	}

	while (m / exp > 0) {
		int bucket[BASE] = { 0 };

		for (i = 0; i < n; i++) {
			bucket[(a[i] / exp) % BASE]++;
		}

		for (i = 1; i < BASE; i++) {
			bucket[i] += bucket[i - 1];
		}

		for (i = n - 1; i >= 0; i--) {
			b[--bucket[(a[i] / exp) % BASE]] = a[i];
		}

		for (i = 0; i < n; i++) {
			a[i] = b[i];
		}

		exp *= BASE;
	}
}

//--------------------------------------------
//----------bucket_sort----------------------
struct barrel {   
	int node[10];   
	int count;/* the num of node */  
};   

void bucket_sort(int data[], int size)   
{   
	int max, min, num, pos;   
	int i, j, k;   
	struct barrel *pBarrel;   

	max = min = data[0];   
	for (i = 1; i < size; i++) {   
		if (data[i] > max) {   
			max = data[i];   
		} else if (data[i] < min) {   
			min = data[i];   
		}   
	}   
	num = (max - min + 1) / 10 + 1;   
	pBarrel = (struct barrel*)malloc(sizeof(struct barrel) * num);   
	memset(pBarrel, 0, sizeof(struct barrel) * num);   

	/* put data[i] into barrel which it belong to */  
	for (i = 0; i < size; i++) {   
		k = (data[i] - min + 1) / 10;/* calculate the index of data[i] in barrel */  
		(pBarrel + k)->node[(pBarrel + k)->count] = data[i];   
		(pBarrel + k)->count++;   
	}   

	pos = 0;   
	for (i = 0; i < num; i++) {   
		quick_sort((pBarrel+i)->node, 0, (pBarrel+i)->count);/* sort node in every barrel */  

		for (j = 0; j < (pBarrel+i)->count; j++) {   
			data[pos++] = (pBarrel+i)->node[j];   
		}   
	}   
	free(pBarrel);   
}   
//-----------------------------------------------------------------------------------------
#endif