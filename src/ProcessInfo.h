//定义结构：进程PID、进程名称
#include <vector>
#include<Windows.h>


using namespace std;
class ProcessInfo {
private:
	DWORD PID;
	string PName;

public:
	bool traverseProcesses();


	ProcessInfo() {

	}

	ProcessInfo(DWORD PID, string PNmae) {
		this->PID = PID;
		this->PName = PName;
	}

	//排序条件：PID 从小到大降序
	bool operator < (const ProcessInfo& rhs) const {
		return (PID < rhs.PID);
	}



};