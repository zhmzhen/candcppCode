#include <iostream>
#include <string>
#include <typeinfo>
#include <pthread.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

//define the base Mutex
//RAII (Resource Acquisition Is Initialization)
//https://zhuanlan.zhihu.com/p/34660259
//三个步骤a.获取资源 b.使用资源 c.销毁资源
class Mutex {
public:
	Mutex();
	~Mutex();
	
	void Lock();
	void Unlock(); 
private:
	pthread_mutex_t mu_;
	// No copying
	Mutex(const Mutex&);
	void operator=(const Mutex&);
};

Mutex::Mutex() {
	if (pthread_mutex_init(&mu_, NULL) != 0) {
		std::cout << "\t" << __func__ << ": pthread_mutex_init failed" << std::endl;
	}
	std::cout << "\t" << __func__ << ": pthread_mutex_init" << std::endl;
}

Mutex::~Mutex() {
	if (pthread_mutex_destroy(&mu_) != 0) {
		std::cout << "\t" << __func__ << ": pthread_mutex_destroy failed" << std::endl;
	}
	std::cout << "\t" << __func__ << ": pthread_mutex_destroy" << std::endl;
}

void Mutex::Lock() {
	if (pthread_mutex_lock(&mu_) != 0) {
		std::cout << "\t" << __func__ << ": pthread_mutex_lock failed" << std::endl;
	}
	std::cout << "\tMutex::" << __func__ << ": pthread_mutex_lock" << std::endl;
}
	
void Mutex::Unlock() {
	if (pthread_mutex_unlock(&mu_) != 0) {
		std::cout << "\t" << __func__ << ": pthread_mutex_unlock failed" << std::endl;
	}
	std::cout << "\tMutex::" << __func__ << ": pthread_mutex_unlock" << std::endl;
	pthread_mutex_unlock(&mu_);
}

//Use class to define a class mutex lock
class  MutexLock {
public:
	explicit MutexLock(Mutex *mu) : mu_(mu) {
		this->mu_->Lock();
		std::cout << "\t\t\tMutexLock:" << num_ << ": ***Mutex is locked " << std::endl;
	}
	~MutexLock() { 
		this->mu_->Unlock();
		std::cout << "\t\t\tMutexLock:" << num_ << ": ~~~Mutex is Unlocked\n" << std::endl;
	}
	void setNum(int pNum)
	{
		num_ = pNum;
		return;
	}
private:
	Mutex *const mu_;
	int num_;
	// No copying allowed
	MutexLock(const MutexLock&);
	void operator=(const MutexLock&);
};

#define    NUM_THREADS     10

int num=0;
//Global varible for mutex, namely, all 10000 thread use the same mutex
Mutex mutex;

void *count(void *args) {
	/*
	 * in each thread, it can see global mutex
	 * then it only define mutexLock in each thread, when define it
	 * then it try to lock, only lock, then MutexLock contruct will be done,
	 * namely lock object is created
	 */
	MutexLock lock(&mutex);
	std::cout << "\t\t\t\t" << __func__ << ":" << num << " enter after lock" << std::endl;
	lock.setNum(num);
	num++;
	/* after exit this function, lock will released because it is lock varibale
 	 * at the same time, in MutexLock de-Contruct, it will unlock it
 	 * so user don't care about lock and unlock, just define a variable
 	 */
	//std::cout << "  " << __func__ << "exit after lock\n" << std::endl;
	return (void*) nullptr;
}

typedef struct cfxt {
	bool isCFX;
	int age;
	cfxt():isCFX(true), age(18) {}
/*
	cfxt() {
		isCFX = true;
		age = 18;
	}
*/
} CFXT;
	
int main() {
	std::cout << "main: enter" << std::endl;

	pthread_t thread[NUM_THREADS];
	for( int t = 0; t < NUM_THREADS; t++) {
		int ret = pthread_create(&thread[t], NULL, count, NULL);
		if(ret) {
			return -1;
		}
	}

	for( int t = 0; t < NUM_THREADS; t++) {
		pthread_join(thread[t], NULL);
	}
	// if num is equal with NUM_THREADS, then lock it good
	std::cout << num << std::endl;

	CFXT cfx;
	std::cout << "main: cfx.age: " << cfx.age << std::endl;
	std::cout << "main: exit" << std::endl;
	return 0;
}
