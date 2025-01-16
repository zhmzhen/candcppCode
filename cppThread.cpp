#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <atomic>

//1) atomic
//
//2) lock
//2.1) std::mutex
//#include <mutex>
//2.2)std::shared_mutex
//#include <shared_mutex>
//read lock performance is good, read lock
//2.3)std::unique_lock is written lock
//3)std::condition_variale
//#include <condition_variable>
//read lock performance is good, read lock
void threadproc(int pI) {
	while (true) {
		std::cout <<"\n\t" << __func__ << ": thread I = " << pI << " id = " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		if (pI == 0) {
			break;
		}
		pI--;
	}
	return;
}

void testFunc(void) {
	std::thread t(threadproc, 2);
	t.detach();
	return;
}
void atomicSi(void) {
	std::atomic<int> value{99};
	std::cout <<"\n\t" << __func__ << ": value is 100 ? " << ++value <<  std::endl;
	
	return;
}
int main() {
	std::cout << "main: thread enter" << std::endl;
	atomicSi();
	//testFunc();
	std::thread t(threadproc, 2);
	while (true) {
		std::cout <<"\n" << __func__ << ": wait for thread" << std::endl;
		if (t.joinable()) {
			t.join();
			std::cout <<"\n" << __func__ << ": done for t.join" << std::endl;
			break;
		}
		else {
			std::cout <<"\n" << __func__ << ": can't do t.join" << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "main: thread exit" << std::endl;
	return 0;
}
