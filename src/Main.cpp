#include<iostream>
#include "Log.h"
#include "Help.h"
#include "Student.h"
#include<Windows.h>
#include "CreateProcessDemo.h"
#include <locale.h>
#include "ProcessInfo.h"
#include "CreateThreadDemo.h"
#include "CreateFileDemo.h"
#include "TransferDll.h"
#include "CreateRemoteThreadDemo.h"
#include "CreateRemoteControl.h"
#include "HideModuleDemo.h"
#include "ShellCode.h"


int Multipyl(int a,int b);


//ѡ������ O(n^2)���� 
template<typename T>
void selectSort(T arr[], int n) {

	for (int i = 0; i < n; i++)
	{
		int tempMin = i;
		
		for (int j = i + 1; j < n; j++)
		{	
			//������������С��һ��Ԫ��
			if (arr[j] < arr[tempMin]) {
				tempMin = j;
			}
		}
		//���潫��iС��Ԫ�ط��ڵ�i��λ���ϣ�����ԭ����i��λ�õ�Ԫ��Ų������
		/*int tmp = arr[i];
		arr[i] = arr[tempMin];
		arr[tempMin] = tmp;*/
		//���� �ȼ�����Ĵ���
		swap(arr[i], arr[tempMin]);
	}

}
//��������
template<typename T>
void insertSort(T arr[],int n) {

	for (int i = 1; i < n; i++)
	{ 
		T e =arr[i];	
		int j;
		for (j =i; j >0 && arr[j-1] >e; j--)
		{
			arr[j] = arr[j - 1];
		} 
		arr[j] = e;
	}
}
//ϣ������
void shellsort3(int a[], int n)
{
	int i, j, gap;
	for (gap = n / 2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap)
				swap(a[j], a[j + gap]);
}

template<typename T>
void __merge(T arr[], int l, int mid,int r) {
	

}

template<typename T>
void __mergeSort(T arr[], int l,int r) {
	if (l>= r) {
		return;
	}
	int mid = (l+r) / 2;
	__mergeSort(arr,l,mid);
	__mergeSort(arr, mid+1 ,r);
	__merge(arr,l,mid,r);

}

//�鲢����
template<typename T>
void mergeSort(T arr[],int n) {

	__mergeSort(arr,0,n-1);


}
int start = 123456789;
int main() {
	//ShellCodeTest();

	//����dll ʧ��
	/* std::cout << "start����" <<std::endl;
	 getchar();
	 hudeModule((char*)"kernel32.dll");
	 printf("****����ģ�����*****");
	 getchar();
	 getchar();*/
	


	//ע��dll ���ƽ��� demo
	//RemoteControlTest();




	//Զ���߳�ע��
	std::string str = "D:\\c++\\hook_dll\\Debug\\hook_dll.dll";
	LoadDll(14144, (char*)str.c_str());


	//����Զ���߳� δ��֤ ��ʱ����֪����λ���̺߳�����ַ
	//����pid
	//DWORD dwProcessId = 13976;
	////�̺߳�����ַ
	//DWORD dwProcAddr = 0x1111;
	//CreateRemoteThreadTest(dwProcessId, dwProcAddr);



	//��ʽ����
	//DllImplicit();

    //��̬����dll 
	//DllTest();

	//�����ļ� ûʵ��
	//CreateFileTest();

	//�����߳�
	//CreateThreadTest();

	//��ý���PID
	/*ProcessInfo* p = new ProcessInfo();
	p->traverseProcesses();
	delete p;*/


	//��������
	//PCTSTR pszApplicationName = TEXT("C:\\Users\\Administrator\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe");
	//win32 ��������
	//CreateProcessTest(pszApplicationName, NULL);


	//��Ϣ����
	//TCHAR strSr[]=TEXT("���� 3800");
	//TCHAR title[] = TEXT("����");	
	//MessageBox(0, strSr, title, MB_OKCANCEL);



#ifdef DEBUG
	int  n = 10;	
	int* arr = Help::generateRandomArray(n,0,n);	
	Help::testSort("selectSort", selectSort, arr, n);

	int* arr1 = Help::copyArray(arr, n);
	Help::testSort("insertSort", insertSort, arr1, n);

	int* arr2 = Help::copyArray(arr, n);
	Help::testSort("mergeSort", mergeSort, arr2, n);
	delete[] arr;
	delete[] arr1;
	delete[] arr2;
	string arr1[4] = { "A","B","D","E" };
	selectSort(arr1, 4);
	Help::printArray(arr1, 4);



	Student d[4] = { {"A",1},{"B",88},{"D",88},{"E",99} };
	selectSort(d, 4);
	for (int i = 0; i < 4; i++)
	{
		cout << d[i];
	}
	cout << endl;

	Log("Main_Hello Word");
	std::cin.get();
	int i= Multipyl(9,10);
	long v = 10;
	char c = 'A';
	float f = 1.1f;
	std::cout << sizeof v << std::endl;
	std::cout << sizeof c << std::endl;
	std::cout << sizeof f << std::endl;
	std::cout << sizeof i << std::endl;

#endif // 0

	return 0;


}

