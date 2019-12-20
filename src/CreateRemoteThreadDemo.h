

//创建远程线程
void CreateRemoteThreadTest(DWORD dwProcessId, DWORD dwProcAddr);
// 加载注入dll
void LoadDll(DWORD dwProcessId, char* pathName);

//通过名字获得PID
DWORD GetProcessIdFromName(char* name);