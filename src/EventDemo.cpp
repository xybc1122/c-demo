#include <Windows.h>
//创建事件
HANDLE CreateEventProTest() {
	//第二个参数 FALSE = 互斥 ，TRUE =通知  //第三个参数 TRUE让启动马上就有能获得信号
	return CreateEvent(NULL, FALSE,TRUE,NULL);
}


//创建消费者者事件
HANDLE CreateEventConTest() {
	//第二个参数 FALSE = 互斥 ，TRUE =通知  
	return CreateEvent(NULL, FALSE, FALSE, NULL);

}