#include<Windows.h>
#include<iostream>  
#include "Log.h"


//��������
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
		FALSE,//�Ƿ񿪷ż̳о��
		0,
		NULL,
		NULL,
		&si,
		&pi)) {
		Log("create process success");
		//printf("PID: %x - ���̾��: %x \n",pi.dwProcessId,pi.hProcess);

		//�ͷž��
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		
		//�õ�ģ��·��
		char strModule[256];
		GetModuleFileName(NULL, strModule,256);
		char strWord[1000];
		GetCurrentDirectory(1000, strWord);

		printf("�õ�ģ��·�� %s  ����·�� %s\n", strModule, strWord);

		//B���̴�A����ȥ�ر�
		//��� һ��A�ľ��
		HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS, //ӵ�е�Ȩ��
			FALSE, //�Ƿ�̳�
			0xFFFF // A�����PID
		);
		if (!TerminateProcess(hProcess,0)) {
			Log("��ֹ���� error");
			return;
		}
		Log("success");
	}
	else {
		Log("failed to create process");
	};

}
