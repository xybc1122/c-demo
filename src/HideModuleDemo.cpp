// 隐藏模块.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>


/* 所需要的结构体
1. _LDR_DATA_TABLE_ENTRY 链表指向数据
2. _PEB_LDR_DATA 表示其 PEB0x处指向的数据表
3. _LIST_ENTRY 指针指向的链表
*/

typedef struct _LSA_UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
}
UNICODE_STRING, * PUNICODE_STRING;

typedef struct _PEB_LDR_DATA
{
	DWORD Length; // +0x00
	bool Initialized; // +0x04
	PVOID SsHandle; // +0x08
	LIST_ENTRY InLoadOrderModuleList; // +0x0c
	LIST_ENTRY InMemoryOrderModuleList; // +0x14
	LIST_ENTRY InInitializationOrderModuleList;// +0x1c
} PEB_LDR_DATA, * PPEB_LDR_DATA; // +0x24

typedef struct _LDR_MODULE
{
	LIST_ENTRY          InLoadOrderModuleList;
	LIST_ENTRY          InMemoryOrderModuleList;
	LIST_ENTRY          InInitializationOrderModuleList;
	void* BaseAddress;
	void* EntryPoint;
	ULONG               SizeOfImage;
	UNICODE_STRING   FullDllName;
	UNICODE_STRING      BaseDllName;
	ULONG               Flags;
	SHORT               LoadCount;
	SHORT               TlsIndex;
	HANDLE              SectionHandle;
	ULONG               CheckSum;
	ULONG               TimeDateStamp;
} LDR_MODULE, * PLDR_MODULE;

//所谓模块句柄，即该模块的入口地址
void hudeModule(char* szDllName)
{
	HMODULE hMod = GetModuleHandleA(szDllName);
	PLIST_ENTRY Head, Cur;
	PPEB_LDR_DATA ldr;
	PLDR_MODULE ldm;
	__asm
	{
		mov eax, fs: [0x30]
		mov ecx, [eax + 0x0c] //Ldr  
		mov ldr, ecx
	}
	Head = &(ldr->InLoadOrderModuleList);
	Cur = Head->Flink;
	do
	{
		ldm = CONTAINING_RECORD(Cur, LDR_MODULE, InLoadOrderModuleList);
		if (hMod == ldm->BaseAddress)
		{
			// 三个链表同时给断掉
			ldm->InLoadOrderModuleList.Blink->Flink =
				ldm->InLoadOrderModuleList.Flink;
			ldm->InLoadOrderModuleList.Flink->Blink =
				ldm->InLoadOrderModuleList.Blink;

			//
			ldm->InInitializationOrderModuleList.Blink->Flink =
				ldm->InInitializationOrderModuleList.Flink;
			ldm->InInitializationOrderModuleList.Flink->Blink =
				ldm->InInitializationOrderModuleList.Blink;

			//
			ldm->InMemoryOrderModuleList.Blink->Flink =
				ldm->InMemoryOrderModuleList.Flink;
			ldm->InMemoryOrderModuleList.Flink->Blink =
				ldm->InMemoryOrderModuleList.Blink;
			break;
		}
		Cur = Cur->Flink;
	} while (Head != Cur);
}

