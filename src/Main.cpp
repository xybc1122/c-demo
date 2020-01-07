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


//选择排序 O(n^2)级别 
template<typename T>
void selectSort(T arr[], int n) {

	for (int i = 0; i < n; i++)
	{
		int tempMin = i;
		
		for (int j = i + 1; j < n; j++)
		{	
			//这里是在找最小的一个元素
			if (arr[j] < arr[tempMin]) {
				tempMin = j;
			}
		}
		//下面将第i小的元素放在第i个位置上，并将原来第i个位置的元素挪到后面
		/*int tmp = arr[i];
		arr[i] = arr[tempMin];
		arr[tempMin] = tmp;*/
		//交换 等价上面的代码
		swap(arr[i], arr[tempMin]);
	}

}
//插入排序
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
//希尔排序
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

//归并排序
template<typename T>
void mergeSort(T arr[],int n) {

	__mergeSort(arr,0,n-1);


}
int start = 123456789;
int main() {
	//ShellCodeTest();

	//隐藏dll 失败
	/* std::cout << "start隐藏" <<std::endl;
	 getchar();
	 hudeModule((char*)"kernel32.dll");
	 printf("****隐藏模块完成*****");
	 getchar();
	 getchar();*/
	


	//注入dll 控制进制 demo
	//RemoteControlTest();




	//远程线程注入
	std::string str = "D:\\c++\\hook_dll\\Debug\\hook_dll.dll";
	LoadDll(14144, (char*)str.c_str());


	//创建远程线程 未验证 暂时还不知道如何获得线程函数地址
	//进程pid
	//DWORD dwProcessId = 13976;
	////线程函数地址
	//DWORD dwProcAddr = 0x1111;
	//CreateRemoteThreadTest(dwProcessId, dwProcAddr);



	//隐式调用
	//DllImplicit();

    //动态调用dll 
	//DllTest();

	//创建文件 没实现
	//CreateFileTest();

	//创建线程
	//CreateThreadTest();

	//获得进程PID
	/*ProcessInfo* p = new ProcessInfo();
	p->traverseProcesses();
	delete p;*/


	//创建进程
	//PCTSTR pszApplicationName = TEXT("C:\\Users\\Administrator\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe");
	//win32 创建进程
	//CreateProcessTest(pszApplicationName, NULL);


	//消息弹窗
	//TCHAR strSr[]=TEXT("就送 3800");
	//TCHAR title[] = TEXT("标题");	
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

