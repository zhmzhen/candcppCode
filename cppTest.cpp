#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <cstdio>
#include <cstdint>
#include <vector>
class CFX {
public:
	void display(void) {
		std::cout << "\t\tFunction name: <" << __func__ << ">"  << std::endl;
	}
};

void ptry(int i) {
	(void) i;
	std::cout << "\ttry: enter" << std::endl;
	CFX cfx;
	cfx.display();
	std::cout << "\ttry: exit" << std::endl;
}
int main() {
	std::cout << "main: enter" << std::endl;
        ptry(2);
		std::vector<int> cfx_v;
		cfx_v.assign({1});
	std::cout << cfx_v.at(0) << std::endl;
	std::cout << "main: exit" << std::endl;
	return 0;
}
