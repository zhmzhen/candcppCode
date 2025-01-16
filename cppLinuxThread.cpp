#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>

//mutex
pthread_mutex_t wait_mutex_int;
pthread_mutexattr_t wait_mutex_int_attr;
//sem
//include<semaphore.h>
//
//Condition Variable
//pthread_cond_init()
// notes: in order to avoid the wait cond' thread is blocked by pthread_cond_wait for ever, 
// it must make sure the other threads which sending cond by pthread_cond_signal/broadcast after the thread
// call pthread_cond_wait
//
// read_write lock
// pthread_rwlock_init()
//  loc current status and other thread request lock type        request readLock     request writeLock
//  no lock							 pass			pass
//  readlock is locked                                           pass                   block
//  writelock is locked nomatter readlock status is lock or not  block                  block
int ret_val = -1;
void* threadproc(void *pT) {
	if (pT == nullptr) return nullptr;
	int* l_pArtT = (int*)pT;
	std::cout <<"\n\t" << __func__ << ": thread I = " << *l_pArtT << " id = " << pthread_self() << std::endl;
	std::cout <<"\n\t" << __func__ << ": thread I = " << *l_pArtT << " id = " << syscall(SYS_gettid) << std::endl;
	int ret = pthread_mutex_unlock(&wait_mutex_int);
	if (ret != 0) {
		std::cout <<"\n\t" << __func__ << ": failed to unlock wait_mutex_int" << std::endl;
	} else {
		std::cout <<"\n\t" << __func__ << ": succ to unlock wait_mutex_int" << std::endl;
	}
	std::cout <<"\n\t" << __func__ << ": Sleep 3 seconds" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	ret_val = 9;
	return (void *)&ret_val;
}

void* threadproc2(void *pT) {
	if (pT == nullptr) return nullptr;
	int* l_pArtT = (int*)pT;
	std::cout <<"\n\t" << __func__ << ": thread I = " << *l_pArtT << " id = " << pthread_self() << std::endl;
	ret_val = 8;
	// will lead all thread exit
	// exit(8);
	std::cout <<"\n\t" << __func__ << ": pthread_exit" << std::endl;
	pthread_exit((void*)&ret_val);
	return nullptr;
}
int main() {
	std::cout << "main: thread enter" << std::endl;
	pthread_t tid, tid2;
	int l_p_i = 1;
	// for mutex, the attr can be null, also it can be set
	pthread_mutexattr_init(&wait_mutex_int_attr);
	//PTHREAD_MUTEX_ERRORCHECK, if lock again, it will return EDEADLK
	//PTHREAD_MUTEX_RECURSIVE, one thread can lock it multiple time, each time, it will
	//  increase refCount, if call unlock, then refCount can be decreased 1, until
	//  refCount is 0, then other thread can lock this mutex
	pthread_mutexattr_settype(&wait_mutex_int_attr, PTHREAD_MUTEX_NORMAL);
	//pthread_mutexattr_gettype(&wait_mutex_int_attr, int * restrict type);
	pthread_mutex_init(&wait_mutex_int, &wait_mutex_int_attr);
	// if the mutex wait_mutex_init is locked, then it will
	// be blocked here 
	// try pthread_mutex_trylock() and it will not be blocked
	int ret = pthread_mutex_lock(&wait_mutex_int);
	if (ret != 0) {
		std::cout << "main: can't lock wait_mutex_int and exit" << std::endl;
		return -1;
	}
	pthread_create(&tid, nullptr, threadproc, &l_p_i);
while(true) {
	int ret = pthread_mutex_lock(&wait_mutex_int);
	if (ret != 0) {
		std::cout << "main: can't lock wait_mutex_int and try again" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		continue;
	}
	break;
}
	l_p_i = 2;
	pthread_create(&tid2, nullptr, threadproc2, &l_p_i);
	pthread_mutex_unlock(&wait_mutex_int);
	ret = pthread_mutex_destroy(&wait_mutex_int);
	if (ret != 0) {
		if (ret == EBUSY) {
			std::cout << "main: can't destroy lock because it is locked" << std::endl;
		}
	} else {
			std::cout << "main: wait_mutex_int lock is destroyed" << std::endl;
	}
	pthread_mutexattr_destroy(&wait_mutex_int_attr);
	while (true) {
		std::cout <<"\n" << __func__ << ": wait for thread" << std::endl;
		int* t_ret_val;
		pthread_join(tid2, (void**)&t_ret_val);
		std::cout <<"\n\t" << __func__ << ":  t_ret_val2 = " << *t_ret_val << std::endl;

		pthread_join(tid, (void**)&t_ret_val);
		std::cout <<"\n\t" << __func__ << ":  t_ret_val1 = " << *t_ret_val << std::endl;
		break;
	}
	std::cout << "main: thread exit" << std::endl;
	return 0;
}
