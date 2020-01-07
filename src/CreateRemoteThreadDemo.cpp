#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
//����Զ���߳�

void CreateRemoteThreadTest(DWORD dwProcessId, DWORD dwProcAddr) {
		DWORD dwDesiredAccess= PROCESS_ALL_ACCESS;//����Ȩ��
		BOOL  bInheritHandle = FALSE; //�Ƿ�̳�
		LPDWORD lpThreadId = 0;
	//1 ��ȡ���̾��
	HANDLE  handle =OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	if (handle ==NULL) {
	
		OutputDebugString("OpenProcess error");
		return;
	}
	// 2����Զ���߳�
	HANDLE hThread=CreateRemoteThread(handle,NULL,0,(LPTHREAD_START_ROUTINE)dwProcAddr,NULL,0,lpThreadId);
	if (hThread == NULL) {
		OutputDebugString("CreateRemoteThread error");
		CloseHandle(handle);
		return;
	}
	//3 �ر�
	CloseHandle(handle);
	CloseHandle(hThread);
}


void LoadDll(DWORD dwProcessId, char* pathName) {
	//1 ��ȡ���̾��
	HANDLE  hProcess =OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (hProcess ==NULL) {
		OutputDebugString("OpenProcess error");
		return;
	}
	//2����Dll ·�����ֳ���,������0��β�ĳ���
	size_t stLen=strlen(pathName)+1;
	//3 ��Ŀ����̷����ڴ�
	LPVOID lpAllocAddr=VirtualAllocEx(hProcess,NULL, stLen, MEM_COMMIT,PAGE_READWRITE);
	if (lpAllocAddr == NULL) {
		OutputDebugString("VirtualAllocEx error");
		CloseHandle(hProcess);
		return;
	}
	//4 д���ڴ�
	BOOL isFlg=WriteProcessMemory(hProcess,lpAllocAddr,pathName, stLen,NULL);

	if (!isFlg) {
		OutputDebugString("WriteProcessMemory error");
		CloseHandle(hProcess);
		return;
	}
	//5 ��ȡKernel32.dll ģ���ַ
	HMODULE hMoDule=GetModuleHandleA("Kernel32.dll");
	if (hMoDule == NULL) {
		OutputDebugString("hMODULE error");
		CloseHandle(hProcess);
		return;
	}
	//6 ��� LoadLibrary�ĵ�ַ
	DWORD dwLoadAddr=(DWORD)GetProcAddress(hMoDule,"LoadLibraryA");
	if (dwLoadAddr == NULL) {
		OutputDebugString("dwLoadAddr error");
		CloseHandle(hProcess);
		return;
	}
	//7����Զ���߳� ע��Dll
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)dwLoadAddr, lpAllocAddr, 0, NULL);
	if (hThread == NULL) {
		OutputDebugString("CreateRemoteThread error");
		CloseHandle(hProcess);
		return;
	}
	CloseHandle(hThread);

	std:: cout << "ע��success" << std::endl;

}


DWORD GetProcessIdFromName(char* name) {
	//1��������
	HANDLE  hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hsnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "��������ʧ��" << std::endl;
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