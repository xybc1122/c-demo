#include<Windows.h>
#include "Log.h"
//#pragma comment(lib,"Dll.lib")


//extern "C" _declspec(dllexport) int add(int x, int y);

//extern "C" _declspec(dllexport) int sub(int x, int y);


typedef int(*pAdd)(int, int);

typedef int(*pSub)(int, int);
//调用dll  测试
void  DllTest() {
	LPCSTR dllName = TEXT("Dll.dll");
	//加载DLL			
	HMODULE hDll=LoadLibrary(dllName);
	if (hDll!=NULL) {
		//加载函数
		pAdd fp1 = (pAdd)(GetProcAddress(hDll, TEXT("add")));
		if (fp1 != NULL) {
			int x = fp1(1, 2);
		}
		//卸载dll，一般用完就卸载，避免占用内存
		FreeLibrary(hDll);
		return;
	}
	Log("加载dll文件失败");
}

void  DllImplicit() {
	Log("加载dll文件");



	//int x= add(1,2);

}