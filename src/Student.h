#include<iostream>

using namespace std;

struct Student
{
	string name;
	int score;

	//����С�ں�
	bool operator <(const Student & otherStudent) {
		return score < otherStudent.score;
	}

	friend ostream& operator<<(ostream& os,Student & student) {
		os << "Student: " << student.name << " " << student.score << endl;
		return os;
	}
};




