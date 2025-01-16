#include <iostream>
#include <string>
class CFX {
public:
	void display(void) {
		std::cout << "\t\tFunction name: <" << __func__ << ">"  << std::endl;
	}
};

[[nodiscard("Have to handle the return value")]] int ignoreReturnV() {
//int ignoreReturnV() {
	return 42;
}

//void maybeUnused(int para1) {
void maybeUnused([[maybe_unused]] int para1) {
}
void FunAtt() {
	std::cout << "\tFunAtt: enter" << std::endl;
	maybeUnused(12);

	//ignore return value
	//ignoreReturnV();
	std::cout << "\tFunAtt: " << ignoreReturnV() << std::endl;

	std::cout << "\tFunAtt: exit" << std::endl;
}
int main() {
	std::cout << "main: enter" << std::endl;
        FunAtt();
	std::cout << "main: exit" << std::endl;
	return 0;
}
