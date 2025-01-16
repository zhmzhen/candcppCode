#include <iostream>
#include <string>
#include <typeinfo>

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
		std::cout << "\t\t\tCFXWisePointerC: CName_ size:" << CName_.size() << std::endl;
		std::cout << "\t\t\tCFXWisePointerC: Pvalues size:" << Pvalues_.size() << std::endl;
	}
private:
	std::string CName_{"CFXWisePointerC"};
	std::string Pvalues_{"Pvalues"};
};
void cfx_string(void)
{
	std::cout << "\tenter " << __func__ << std::endl;
	std::string cfxwpc ("cfx");
	std::cout << "\t" << __func__ << ":cfxwpc type: "<< typeid(cfxwpc).name() << std::endl;
	std::cout << "\t" << __func__ << ":cfxwpc string size: "<< cfxwpc.size() << std::endl;
	std::cout << "\t" << __func__ << ":cfxwpc string len: "<< cfxwpc.length() << std::endl;
	std::cout << "\t" << __func__ << ":cfxwpc string capacity: "<< cfxwpc.capacity() << std::endl;

	std::string cfxwpd ("cfx");
	cfxwpd.reserve(30);
	std::cout << "\t" << __func__ << ":cfxwpd type: "<< typeid(cfxwpd).name() << std::endl;
	std::cout << "\t" << __func__ << ":cfxwpd string size: "<< cfxwpd.size() << std::endl;
	std::cout << "\t" << __func__ << ":cfxwpd string len: "<< cfxwpd.length() << std::endl;
	std::cout << "\t" << __func__ << ":cfxwpd string capacity: "<< cfxwpd.capacity() << std::endl;
	
	std::cout << "\texit " << __func__ << std::endl;
	return;
}
int main() {
	std::cout << "main: enter" << std::endl;
	cfx_string();
	std::cout << "main: exit" << std::endl;
	return 0;
}
