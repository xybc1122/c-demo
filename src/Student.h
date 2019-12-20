#include<iostream>

using namespace std;

struct Student
{
	string name;
	int score;

	//ÖØÔØĞ¡ÓÚºÅ
	bool operator <(const Student & otherStudent) {
		return score < otherStudent.score;
	}

	friend ostream& operator<<(ostream& os,Student & student) {
		os << "Student: " << student.name << " " << student.score << endl;
		return os;
	}
};




