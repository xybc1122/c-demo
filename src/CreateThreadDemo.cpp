#include<Windows.h>
#include<iostream>
#include "ThreadInfo.h"
#include "Log.h"
#include "EventDemo.h"

HANDLE heventPro;
HANDLE heventCon;
int number = 0;
//执行的线程方法
DWORD WINAPI ThreadProcPro(LPVOID lpParam) {
	ThreadInfo* t = (ThreadInfo*)lpParam;
	for (int i = 0; i < t->getCount(); i++) {
		//线程等待 每次得到信号一致性 就会更改 事件的第三个参数 0=FALSE 
		WaitForSingleObject(heventPro, INFINITE);
		number++;
		std::cout << "线程名称: " << t->getName() << "生产了: " << number << std::endl;
		//唤醒消费者 事件第三个参数 1 =TRUE
		SetEvent(heventCon);
	}
	return 0;
}

DWORD WINAPI ThreadProcCon(LPVOID lpParam) {
	//线程等待
	ThreadInfo* t = (ThreadInfo*)lpParam;
	for (int i = 0; i < t->getCount(); i++) {
		WaitForSingleObject(heventCon, INFINITE);
		number--;
		std::cout << "线程名称: " << t->getName() << "消费后: " << number << std::endl;
		//唤醒生产者
		SetEvent(heventPro);
	}
	return 0;
}
//创建线程
void CreateThreadTest() {

	heventPro = CreateEventProTest();
	heventCon = CreateEventConTest();

	ThreadInfo t1("thread 1 我是生产者",5);


	DWORD threadID; //线程ID
	HANDLE hThreadArr[2];
	//创建线程函数
	hThreadArr[0] = CreateThread(NULL,0, ThreadProcPro,(LPVOID)&t1,0,&threadID);
	
	ThreadInfo t2("thread 2 我是消费者", 5);

	hThreadArr[1] = CreateThread(NULL, 0, ThreadProcCon, (LPVOID)&t2, 0, &threadID);

	//线程等待函数
	WaitForMultipleObjects(2, hThreadArr, TRUE, INFINITE);




}
