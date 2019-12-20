#include<string>

using namespace std;



class ThreadInfo
{
public:
	ThreadInfo() {
	
	};
	ThreadInfo(string name,int count) {
		this->count = count;
		this->name = name;
	};
	

	string getName() {

		return this->name;
	}

	int getCount() {

		return this->count;
	}

private:
	string name; 
	int  count;
};