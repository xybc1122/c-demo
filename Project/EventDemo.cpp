#include <Windows.h>
//�����¼�
HANDLE CreateEventProTest() {
	//�ڶ������� FALSE = ���� ��TRUE =֪ͨ  //���������� TRUE���������Ͼ����ܻ���ź�
	return CreateEvent(NULL, FALSE,TRUE,NULL);
}


//�������������¼�
HANDLE CreateEventConTest() {
	//�ڶ������� FALSE = ���� ��TRUE =֪ͨ  
	return CreateEvent(NULL, FALSE, FALSE, NULL);

}