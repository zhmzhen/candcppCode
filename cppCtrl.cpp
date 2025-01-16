#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
class CFX {
public:
	void display(void) {
		std::cout << "\t\tFunction name: <" << __func__ << ">"  << std::endl;
	}
};

void ifctl(void) {
	std::cout << "\ttry: enter" << std::endl;
	int i = 0;
	if (CFX cfx; i > 0 ) {
		std::cout << "\tin if " << std::endl;
		cfx.display();
	}
	else if ( i < 0) [[unlikely]]{
		std::cout << "\tin elseif" << std::endl;
		cfx.display();
	}
	else [[likely]] {
		std::cout << "\tin else" << std::endl;
		cfx.display();
	}
	switch (i) {
	case 1:
		[[fallthrough]];
	[[unlikely]] case 2:
		break;
	[[likely]] case 0:
		std::cout << "\t case 0" << std::endl;
		break;
	default:
		break;
	}
	std::cout << "\ttry: exit" << std::endl;
}
int main() {
	std::cout << "main: enter" << std::endl;
        ifctl();
	std::cout << "main: exit" << std::endl;
	return 0;
}
