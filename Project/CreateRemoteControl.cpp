#include<Windows.h>
#include<iostream>
#include "CreateRemoteThreadDemo.h"
#define _MAP_ "�����ڴ�"
LPTSTR lMapView;
BOOL Init() {
	//1 �����¼������������ڴ� ����ҳ
	HANDLE hMapFile=CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 0x1000, _MAP_);
	if (NULL ==hMapFile) {
		std::cout << "���������ڴ�ʧ��" << std::endl;
		return FALSE;
	}
	//2 ӳ���ڴ�
	 lMapView=(LPTSTR)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,BUFSIZ);
	if (NULL == lMapView) {
		std::cout << "ӳ���ڴ�ʧ��" << std::endl;
		return FALSE;
	}
	return TRUE;

}
void RemoteControlTest() {

	if (!Init()) {
		return;
	}
	//1 ע�� Dll
	std::string strExe = "NewConsoleApplication.exe";
	std::string str = "D:\\c++\\Dll\\Debug\\Dll.dll";
	LoadDll(GetProcessIdFromName((char*)strExe.c_str()), (char*)str.c_str());
	//ִ��
	int c[4] = {1,2,3,4};
	for (int i = 0; i < 4;i++) {
		CopyMemory(lMapView, &c[i], 4);
	}
		
	



}