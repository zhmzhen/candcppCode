#include <iostream>
#include <string>
#include <vector>
class CFX {
public:
	void display(void) const {
		std::cout << "\t\tFunction name: <" << __func__ << ">"  << std::endl;
	}
protected:
private:
	std::string name;
};

void cNormtry(void) {
	std::cout << "\tcNormtry: enter" << std::endl;
	//const int z = 100; // 常量
	//int x = 100; 
	//const int& rx = x; // 常量引用
	
	//const int* px = &x; // 常量指针, can't change the content of variable
	//*px = 200; //error, you can't change the content by const pointer
	//int z =300;
	//px = &z;

	//const放在*的右边，表示指针是常量（const pointer to int）
	//指针不能被修改，而指向的变量可以被修改
	//int b = 150;
	//int *const py = &x;
	//*py = 102; // success
	//py = &b; // error: Cannot assign to variable 'py' with const-qualified type 'int *const'

	std::cout << "\tcNormtry: exit" << std::endl;
}
int main() {
	std::cout << "main: enter" << std::endl;
	cNormtry();
	std::cout << "main: exit" << std::endl;
	return 0;
}
