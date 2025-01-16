#include <iostream>
#include <functional>
#include <string>

using FilterFactoryCb = std::function<void(std::string & pStr)>;
class Tclass {
public:
	Tclass () {
		std::cout << "\t\tCon fun of Tclass is called" << std::endl;
	}

	//Tclass(const Tclass& pTC) = delete;/*{
	Tclass(const Tclass& pTC) {

		std::cout << "\t\tCopy Construct Tclass is called" << std::endl;
		this->name = pTC.name;
	}
	~Tclass () {
		std::cout << "\t\tDeConstruct fun of ~Tclass is called" << std::endl;
	}
	void display() const {
		std::cout << "\t\tTclass::display,class name: " << name << std::endl;
	}
private:
	std::string name="Tclass";
};

//FilterFactoryCb returnLamdaFunc(std::string & pStr) {
//https://cloud.tencent.com/developer/article/2322118
auto returnLamdaFunc(std::string & pStr) {
	Tclass t;
	std::cout << "\treturnLamdaFunc: passed from returnLamdaFunc pStr: " << pStr << std::endl;
	//std::reference_wrapper<Tclass> t = t1;
	//t = std::cref(t1);
	return [t] (std::string& pLstring) -> void {
		std::cout << "\tL:Before remove t" << std::endl;
		t.display();
		std::cout << "\tL:after remove t" << std::endl;
		std::cout << "\tL:Passed pLstring: " << pLstring << std::endl;
	};
}

int main() {
	std::cout << "main: enter" << std::endl;
	std::cout << "main: before define aMain " << std::endl;
	std::string l_l_str = "assignment";
	auto aMain = returnLamdaFunc(l_l_str);
	std::cout << "main: after define aMain " << std::endl;
	std::string l_amain = "Call aMain";
	std::cout << "main: before call aMain " << std::endl;
	aMain(l_amain);
	std::cout << "main: after call aMain " << std::endl;
	std::cout << "main: exit" << std::endl;
	return 0;
}
