#include<Windows.h>
#include "Log.h"
//#pragma comment(lib,"Dll.lib")


//extern "C" _declspec(dllexport) int add(int x, int y);

//extern "C" _declspec(dllexport) int sub(int x, int y);


typedef int(*pAdd)(int, int);

typedef int(*pSub)(int, int);
//����dll  ����
void  DllTest() {
	LPCSTR dllName = TEXT("Dll.dll");
	//����DLL			
	HMODULE hDll=LoadLibrary(dllName);
	if (hDll!=NULL) {
		//���غ���
		pAdd fp1 = (pAdd)(GetProcAddress(hDll, TEXT("add")));
		if (fp1 != NULL) {
			int x = fp1(1, 2);
		}
		//ж��dll��һ�������ж�أ�����ռ���ڴ�
		FreeLibrary(hDll);
		return;
	}
	Log("����dll�ļ�ʧ��");
}

void  DllImplicit() {
	Log("����dll�ļ�");



	//int x= add(1,2);

}