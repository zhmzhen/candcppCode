#include <iostream>
#include <functional>
#include <string>

using FilterFactoryCb = std::function<void(std::string & pStr)>;
class Tclass {
public:
	Tclass () {
		std::cout << "Con fun of Tclass is called" << std::endl;
	}

	//Tclass(const Tclass& pTC) = delete;/*{
	Tclass(const Tclass& pTC) {

		std::cout << "Con fun of CC Tclass is called" << std::endl;
		this->name = pTC.name;
	}
	~Tclass () {
		std::cout << "Con fun of ~Tclass is called" << std::endl;
	}
	void display() const {
		std::cout << "class name:" << name << std::endl;
	}
private:
	std::string name="Tclass";
};

FilterFactoryCb returnLamdaFunc(std::string & pStr) {
	Tclass t;
	std::cout << "passed from returnLamdaFunc pStr:" << pStr << std::endl;
	return [t] (std::string& pLstring) -> void {
		std::cout << "Before remove t" << std::endl;
		t.display();
		std::cout << "after remove t" << std::endl;
		std::cout << "Passed pLstring: " << pLstring << std::endl;
	};
}

int main() {
	std::cout << "main: enter" << std::endl;
	std::cout << "main: before define aMain " << std::endl;
	std::string l_l_str = "assignment";
	FilterFactoryCb aMain = returnLamdaFunc(l_l_str);
	
	returnLamdaFunc(l_l_str);
	std::cout << "main: after define aMain " << std::endl;
	std::string l_amain = "Call aMain";
	std::cout << "main: before call aMain " << std::endl;
	aMain(l_amain);
	std::cout << "main: after call aMain " << std::endl;
	std::cout << "main: exit" << std::endl;
	Tclass tt;
	auto x = tt;
	x.display();
	return 0;
}
