//����ṹ������PID����������
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

	//����������PID ��С������
	bool operator < (const ProcessInfo& rhs) const {
		return (PID < rhs.PID);
	}



};