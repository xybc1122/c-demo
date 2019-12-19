#include<Windows.h>
#include<iostream>
#include "CreateRemoteThreadDemo.h"
#define _MAP_ "共享内存"
LPTSTR lMapView;
BOOL Init() {
	//1 创建事件，创建共享内存 物理页
	HANDLE hMapFile=CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 0x1000, _MAP_);
	if (NULL ==hMapFile) {
		std::cout << "创建共享内存失败" << std::endl;
		return FALSE;
	}
	//2 映射内存
	 lMapView=(LPTSTR)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,BUFSIZ);
	if (NULL == lMapView) {
		std::cout << "映射内存失败" << std::endl;
		return FALSE;
	}
	return TRUE;

}
void RemoteControlTest() {

	if (!Init()) {
		return;
	}
	//1 注入 Dll
	std::string strExe = "NewConsoleApplication.exe";
	std::string str = "D:\\c++\\Dll\\Debug\\Dll.dll";
	LoadDll(GetProcessIdFromName((char*)strExe.c_str()), (char*)str.c_str());
	//执行
	int c[4] = {1,2,3,4};
	for (int i = 0; i < 4;i++) {
		CopyMemory(lMapView, &c[i], 4);
	}
		
	



}