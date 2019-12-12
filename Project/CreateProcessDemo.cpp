#include<Windows.h>
#include<iostream>  
#include "Log.h"


//创建进程
void  CreateProcessTest(PCTSTR pszApplicationName, PTCHAR cmd ) {
	STARTUPINFO  si;
	PROCESS_INFORMATION   pi;

	ZeroMemory(&si, sizeof(si));

	ZeroMemory(&pi, sizeof(pi));

	si.cb = sizeof(si);
	if (CreateProcess(
		pszApplicationName,
		cmd,
		NULL,
		NULL,
		FALSE,//是否开放继承句柄
		0,
		NULL,
		NULL,
		&si,
		&pi)) {
		Log("create process success");
		//printf("PID: %x - 进程句柄: %x \n",pi.dwProcessId,pi.hProcess);

		//释放句柄
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		
		//得到模块路径
		char strModule[256];
		GetModuleFileName(NULL, strModule,256);
		char strWord[1000];
		GetCurrentDirectory(1000, strWord);

		printf("得到模块路径 %s  工作路径 %s\n", strModule, strWord);

		//B进程打开A进程去关闭
		//获得 一个A的句柄
		HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS, //拥有的权利
			FALSE, //是否继承
			0xFFFF // A句柄的PID
		);
		if (!TerminateProcess(hProcess,0)) {
			Log("终止进程 error");
			return;
		}
		Log("success");
	}
	else {
		Log("failed to create process");
	};

}
