#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <cstdio>
#include <cstdint>
class CFX {
public:
	void display(void) {
		std::cout << "\t\tFunction name: <" << __func__ << ">"  << std::endl;
	}
};
// function template
template <typename DataType>
void swap (DataType& a, DataType& b) {
	DataType tmp = a;
	a = b;
	b = tmp;
}

template <typename DataType>
int compare(const DataType &v1, const DataType &v2)			
{			
        if (v1 < v2) return -1;			
        if (v1 > v2) return 1;			
        return 0;			
}			

void simpleFunc(void) {
	int i=2, j=3;
	std::cout << "\tsimpleFunc: before i= " << i << " j= " << j << std::endl;
	swap(i,j);
	std::cout << "\tsimpleFunc: after i= " << i << " j= " << j << std::endl;
	return;
}
// multiple arguments
template <typename T>
T add(T value) {
    return value;
}

template <typename T, typename... Args>
T add(T first, Args... rest) {
    return first + add(rest...);
}
void multipleArgs(void) {
    std::cout << "\tmultipleArgs: add(1, 2, 3, 4, 5): " << add(1, 2, 3, 4, 5) << std::endl;  // 输出：15
    std::cout << "\tmultipleArgs: add(1.1, 2.2, 3.3): " << add(1.1, 2.2, 3.3) << std::endl;  // 输出：6.6
}

// class template
template <typename T> class CTBlob {						
public:						
        CTBlob() {}						
        CTBlob(T age):mAge(age) {}						
        ~CTBlob(){}						
        T getAge() { return (mAge); }						
        T compareD(const T &v1, const T &v2) {						
                if (v1 < v2) return (T)-1;						
                if (v1 > v2) return (T)1;						
                return (T)0;						
        }						
						
private:						
        T mAge;						
};						

void class_template(void)						
{						
        std::cout << "\tclass_template enter" << std::endl;						
        CTBlob <int> ctBlob(20); //用int实例化						
        std::cout << "\t\tctBlob(20).age= "<<ctBlob.getAge()<< std::endl;						
}

//end
template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
onlyForIntegers(T value) {
    return value * 2;
}

int main() {
	std::cout << "main: enter" << std::endl;
        //simpleFunc();  
        multipleArgs();
        class_template();
       std::cout << "\t onlyForIntegers: 2 = " << onlyForIntegers(1) << std::endl;  // 输出：15
	std::cout << "main: exit" << std::endl;
	return 0;
}
