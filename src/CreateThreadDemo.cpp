#include<Windows.h>
#include<iostream>
#include "ThreadInfo.h"
#include "Log.h"
#include "EventDemo.h"

HANDLE heventPro;
HANDLE heventCon;
int number = 0;
//ִ�е��̷߳���
DWORD WINAPI ThreadProcPro(LPVOID lpParam) {
	ThreadInfo* t = (ThreadInfo*)lpParam;
	for (int i = 0; i < t->getCount(); i++) {
		//�̵߳ȴ� ÿ�εõ��ź�һ���� �ͻ���� �¼��ĵ��������� 0=FALSE 
		WaitForSingleObject(heventPro, INFINITE);
		number++;
		std::cout << "�߳�����: " << t->getName() << "������: " << number << std::endl;
		//���������� �¼����������� 1 =TRUE
		SetEvent(heventCon);
	}
	return 0;
}

DWORD WINAPI ThreadProcCon(LPVOID lpParam) {
	//�̵߳ȴ�
	ThreadInfo* t = (ThreadInfo*)lpParam;
	for (int i = 0; i < t->getCount(); i++) {
		WaitForSingleObject(heventCon, INFINITE);
		number--;
		std::cout << "�߳�����: " << t->getName() << "���Ѻ�: " << number << std::endl;
		//����������
		SetEvent(heventPro);
	}
	return 0;
}
//�����߳�
void CreateThreadTest() {

	heventPro = CreateEventProTest();
	heventCon = CreateEventConTest();

	ThreadInfo t1("thread 1 ����������",5);


	DWORD threadID; //�߳�ID
	HANDLE hThreadArr[2];
	//�����̺߳���
	hThreadArr[0] = CreateThread(NULL,0, ThreadProcPro,(LPVOID)&t1,0,&threadID);
	
	ThreadInfo t2("thread 2 ����������", 5);

	hThreadArr[1] = CreateThread(NULL, 0, ThreadProcCon, (LPVOID)&t2, 0, &threadID);

	//�̵߳ȴ�����
	WaitForMultipleObjects(2, hThreadArr, TRUE, INFINITE);




}
