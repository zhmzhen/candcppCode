#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <atomic>
thread_local int tls_int = 0;
void threadproc(int pI) {
	tls_int = pI;
	std::string pPrefixStr = __func__ + std::to_string(pI);
	std::cout <<"\n\t" << pPrefixStr << ": thread I = " << pI << " id = " << std::this_thread::get_id() << std::endl;
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(pI));
		if (pI == 0) {
			break;
		}
		std::cout <<"\t\t" << pPrefixStr << ": pI = " << pI << std::endl;
		std::cout <<"\t\t" << pPrefixStr << ": thread tsl_int = " << tls_int << std::endl;
		pI--;
	}
	return;
}

void testFunc(void) {
	std::thread t1(threadproc, 1);
	t1.detach();
	std::thread t2(threadproc, 2);
	t2.detach();
	return;
}
int main() {
	std::cout << "main: thread enter" << std::endl;
	testFunc();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::cout << "main: thread exit" << std::endl;
	return 0;
}
