#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <atomic>

class CFXWisePointerC {
public:
        CFXWisePointerC(std::string pV):Pvalues_(pV) {
                std::cout << "\t\t\t*****CFXWisePointerC: Con is called" << std::endl;
        }

        ~CFXWisePointerC() {
                std::cout << "\t\t\t~~~~CFXWisePointerC: De-Con is called" << std::endl;
        }
        void display(void) {
                std::cout << "\t\t\tCFXWisePointerC: name is:" << CName_ << std::endl;
                std::cout << "\t\t\tCFXWisePointerC: Pvalues is:" << Pvalues_ << std::endl;
        }
private:
        std::string CName_{"CFXWisePointerC"};
        std::string Pvalues_{"Pvalues"};
};

auto l_main_shared_ptr = std::make_shared <CFXWisePointerC>("CFXPvaluesMain");
void threadSharedProc() {
	std::cout << "\nthreadSharedProc: thread shared enter" << std::endl;
	int i = 0;
	while (true) {
		std::cout << "\nthreadSharedProc: thread shared loop i:" << i << " pSharedPointer.use_count():" << l_main_shared_ptr.use_count() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		if (i == 2) {
			break;
		}
		i++;
	}
	l_main_shared_ptr.reset();
	std::cout << "\n\tthreadSharedProc: thread shared exit" << std::endl;
	return;
}
void threadSharedWeakProc() {
/*
 * https://blog.csdn.net/weixin_38278993/article/details/104961701?spm=1001.2101.3001.6650.4&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-4-104961701-blog-123195547.235%5Ev38%5Epc_relevant_default_base&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-4-104961701-blog-123195547.235%5Ev38%5Epc_relevant_default_base&utm_relevant_index=5
 * 当你想使用对象，但是并不想管理对象，并且在需要使用对象时可以判断对象是否还存在
 *
 */
	std::cout << "\n\tthreadSharedWeakProc: thread shared weak enter" << std::endl;
	int i = 0;
	while (true) {
		if (l_main_shared_ptr == nullptr) {
			std::cout << "\n\tthreadSharedWeakProc: thread shared loop i:" << i << "NULL****  l_main_shared_ptr" << std::endl;
			break;
		}
		std::cout << "\n\tthreadSharedWeakProc: thread shared loop i:" << i << " pSharedPointer.use_count():" << l_main_shared_ptr.use_count() << std::endl;
		std::weak_ptr<CFXWisePointerC> l_weak_shared_ptr = l_main_shared_ptr;
		std::shared_ptr<CFXWisePointerC> l_real_shared_ptr = l_weak_shared_ptr.lock();
		if (l_real_shared_ptr) {
			std::cout << "\n\tthreadSharedWeakProc: i:" << i << " Use weak lock done shared point before:" <<  l_main_shared_ptr.use_count() << std::endl;
			l_real_shared_ptr->display();
			std::cout << "\n\tthreadSharedWeakProc: i:" << i << " Use weak lock done shared point after:" <<  l_main_shared_ptr.use_count() << std::endl;
		}
                else {
			std::cout << "\n\tthreadSharedWeakProc: l_main_shared_ptr is gone" << std::endl;
                }
		std::this_thread::sleep_for(std::chrono::seconds(3));
		if (i == 3) {
			break;
		}
		i++;
	}
	std::cout << "\n\tthreadSharedWeakProc: thread shared weak exit" << std::endl;
	return;
}


int main() {
	std::cout << "main: thread shared weak enter" << std::endl;
	std::thread t(threadSharedProc);
	std::thread t1(threadSharedWeakProc);
	//l_main_shared_ptr.reset();
	if (t.joinable()) {
		t.join();
		std::cout <<"\n" << __func__ << ": done for t.join" << std::endl;
	}
	if (t1.joinable()) {
		t1.join();
		std::cout <<"\n" << __func__ << ": done for t1.join" << std::endl;
	}
	std::cout << "main: thread shared weak exit" << std::endl;
	return 0;
}
