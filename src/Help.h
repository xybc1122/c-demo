#include<iostream>
#include<ctime>
#include<cassert>
using namespace std;



namespace Help {
	//�������n Ԫ�� �趨��l ��ʼ�� r����
	int* generateRandomArray(int n,int l ,int r) {
		//����
		assert(l<=r);
		int* arr = new int[n];
		srand(time(NULL));
	
		for (int i = 0; i < n; i++)
		{	
			//���������
			arr[i] = rand()%(r-l+1)+l;
			
		}
		return arr;
	}


	template<typename T>
	bool isSorted(T arr[], int n) {
		for (int i = 0; i < n-1; i++)
		{
			if (arr[i] > arr[i+1]) {
				return false;
			}
			
		}
	
		return true;
	}
				
		
	template<typename T>
	void testSort(string sortName,void(*sort)(T[],int),T arr[],int n) {
		clock_t startTime= clock();
		sort(arr,n);
		clock_t endTime = clock();
		assert(isSorted(arr,n));
		cout << sortName << ":" << double(endTime - startTime)/ CLOCKS_PER_SEC<< "s" << endl;
		
		return;
	}



	int * copyArray(int a[],int n) {
		int* arr = new int[n];
		copy(a,a+n,arr);
		return arr;
			
	
	
	}




}