#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
//创建远程线程

void CreateRemoteThreadTest(DWORD dwProcessId, DWORD dwProcAddr) {
		DWORD dwDesiredAccess= PROCESS_ALL_ACCESS;//访问权限
		BOOL  bInheritHandle = FALSE; //是否继承
		LPDWORD lpThreadId = 0;
	//1 获取进程句柄
	HANDLE  handle =OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	if (handle ==NULL) {
	
		OutputDebugString("OpenProcess error");
		return;
	}
	// 2创建远程线程
	HANDLE hThread=CreateRemoteThread(handle,NULL,0,(LPTHREAD_START_ROUTINE)dwProcAddr,NULL,0,lpThreadId);
	if (hThread == NULL) {
		OutputDebugString("CreateRemoteThread error");
		CloseHandle(handle);
		return;
	}
	//3 关闭
	CloseHandle(handle);
	CloseHandle(hThread);
}


void LoadDll(DWORD dwProcessId, char* pathName) {
	//1 获取进程句柄
	HANDLE  hProcess =OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (hProcess ==NULL) {
		OutputDebugString("OpenProcess error");
		return;
	}
	//2计算Dll 路径名字长度,并加上0结尾的长度
	size_t stLen=strlen(pathName)+1;
	//3 在目标进程分配内存
	LPVOID lpAllocAddr=VirtualAllocEx(hProcess,NULL, stLen, MEM_COMMIT,PAGE_READWRITE);
	if (lpAllocAddr == NULL) {
		OutputDebugString("VirtualAllocEx error");
		CloseHandle(hProcess);
		return;
	}
	//4 写入内存
	BOOL isFlg=WriteProcessMemory(hProcess,lpAllocAddr,pathName, stLen,NULL);

	if (!isFlg) {
		OutputDebugString("WriteProcessMemory error");
		CloseHandle(hProcess);
		return;
	}
	//5 获取Kernel32.dll 模块地址
	HMODULE hMoDule=GetModuleHandleA("Kernel32.dll");
	if (hMoDule == NULL) {
		OutputDebugString("hMODULE error");
		CloseHandle(hProcess);
		return;
	}
	//6 获得 LoadLibrary的地址
	DWORD dwLoadAddr=(DWORD)GetProcAddress(hMoDule,"LoadLibraryA");
	if (dwLoadAddr == NULL) {
		OutputDebugString("dwLoadAddr error");
		CloseHandle(hProcess);
		return;
	}
	//7创建远程线程 注入Dll
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)dwLoadAddr, lpAllocAddr, 0, NULL);
	if (hThread == NULL) {
		OutputDebugString("CreateRemoteThread error");
		CloseHandle(hProcess);
		return;
	}
	CloseHandle(hThread);

	std:: cout << "注入success" << std::endl;

}


DWORD GetProcessIdFromName(char* name) {
	//1创建快照
	HANDLE  hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hsnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "创建快照失败" << std::endl;
		return 0;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	int flag = Process32First(hsnapshot, &pe);

	while (flag != 0)
	{
		if (strcmp(pe.szExeFile, name) == 0)
		{
			return pe.th32ProcessID;
		}
		flag = Process32Next(hsnapshot, &pe);
	}

	CloseHandle(hsnapshot);

	return 0;


}