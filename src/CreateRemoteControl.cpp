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
	std::string exeName = "NewConsoleApplication.exe";
	std::string str = "D:\\c++\\Dll\\Debug\\Dll.dll";
	LoadDll(GetProcessIdFromName((char*)exeName.c_str()), (char*)str.c_str());
	//ִ��
	int index = 0;
	for (;;) {
		std::cin >> index;
		switch (index) {
		case 1:
			std::cout << "����" << std::endl;
			break;
		case 2:
			std::cout << "PUT" << std::endl;
			break;
		case 3:
			std::cout << "DEL" << std::endl;
			break;
		case 4:
			std::cout << "UP" << std::endl;
			break;
		}
		CopyMemory(lMapView, &index, 4);
	}
		
	



}