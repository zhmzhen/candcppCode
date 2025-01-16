#include <iostream>
#include <string>
#include <typeinfo>
#include <cmath>
#include <format>
#include <any>
#include <tuple>

class CFXWisePointerC {
public:
	CFXWisePointerC(std::string pV):Pvalues_(pV) {
		std::cout << "\t\t\t*****CFXWisePointerC: Con is called" << std::endl;
	}

	~CFXWisePointerC() {
		std::cout << "\t\t\t~~~~CFXWisePointerC: De-Con is called" << std::endl;
	}
	void display(void) {
		std::cout << "\t\t\tCFXWisePointerC: name is:" << Pvalues_ << std::endl << std::endl;
	}
	void display2(void) {
		std::cout << "\t\t\tCFXWisePointerC: name is:" << CName_ << std::endl;
		std::cout << "\t\t\tCFXWisePointerC: Pvalues is:" << Pvalues_ << std::endl;
		std::cout << "\t\t\tCFXWisePointerC: CName_ size:" << CName_.size() << std::endl;
		std::cout << "\t\t\tCFXWisePointerC: Pvalues size:" << Pvalues_.size() << std::endl;
	}
private:
	std::string CName_{"CFXWisePointerC"};
	std::string Pvalues_{"Pvalues"};
};
//https://nolowiz.com/how-to-get-the-type-of-a-variable-in-cpp/
void cfx_type(void)
{
	std::cout << "\tenter " << __func__ << std::endl;
	//init
	//1.1 Function init
	CFXWisePointerC cfxwpc ("Function_init_cfx");
	cfxwpc.display();
	//1.2 assignment init
	CFXWisePointerC cfxwpc21 ("Assignment_init_cfx");
	CFXWisePointerC cfxwpc2  = cfxwpc21;
	cfxwpc.display();

	//1.3 list table init
	CFXWisePointerC cfxwpc3  = {"List_table_init_cfx"};
	cfxwpc3.display();

	if (typeid(cfxwpc) == typeid(CFXWisePointerC)) {
		std::cout << "\t\t" << __func__ << ":cfxwpc type: "<< typeid(cfxwpc).name() << std::endl;
		std::cout << "\t\t" << __func__ << ":CFXWisePointerC type: "<< typeid(CFXWisePointerC).name() << std::endl;
	}
	
	//std::cout << "\t" << __func__ << ":shared pointer pointer "<< &l_shared_ptr1 << std::endl;
	std::cout << "\texit " << __func__ << std::endl;
	return;
}
void cfx_enum(void) {
	enum class charEnum : char {
		APPLE = 'a',
		BANA = 'b',
		PEAL = 'p',
	};

	charEnum c_apple = charEnum::APPLE;
	std::cout << "\t\tapple enum:  " << static_cast <int>(c_apple) << std::endl;
}

void printCFXany(const std::any& anyRef) {
  try {
	if (anyRef.type() == typeid(CFXWisePointerC)) {
		//CFXWisePointerC tmp = std::any_cast<CFXWisePointerC>(anyRef);
		CFXWisePointerC tmp(std::any_cast<CFXWisePointerC>(anyRef));
		std::cout << "\t\tprintCFXany, CFXWisePointerC* "  << std::endl;
		tmp.display();
	}
  } catch (const std::bad_any_cast& e) {
	std::cout << "\t\tprintCFXany, exception fired when any casetCFXWisePointerC* :<" << e.what()  << std::endl;
  } catch (...) {
	std::cout << "\t\tprintCFXany, exception fired when any casetCFXWisePointerC* "  << std::endl;
  }
}
void cfx_any(void) {
	CFXWisePointerC cfxwpc ("Function_any_type");
	std::any anyCFX = cfxwpc;
	printCFXany(anyCFX);
}
void cfx_tuple(void) {
	std::pair <int, std::string> pIntStr {51, "man"};
	std::cout << "\t\tcfx_tuple,  pIntStr.first: " << pIntStr.first  << std::endl;
	std::cout << "\t\tcfx_tuple,  pIntStr.second: " << pIntStr.second  << std::endl;

	using myTuple = std::tuple<int,bool,std::string, std::string>;
	myTuple cliff {51, true, "Cliff", "Shaanxi"};
	//size of tuple
	std::cout << "\t\tcfx_tuple,  cliff.size " << std::tuple_size<decltype(cliff)>::value  << std::endl;
	//use index to access
	std::cout << "\t\tcfx_tuple,  cliff.age: " << std::get<0>(cliff)  << std::endl;
	std::cout << "\t\tcfx_tuple,  cliff.home: " << std::get<3>(cliff)  << std::endl;
	// access by type
	std::cout << "\t\tcfx_tuple,  cliff.sex: " << std::get<bool>(cliff)  << std::endl;
	// element type
	std::cout << "\t\tcfx_tuple,  cliff.name type: " << typeid(std::tuple_element<2,myTuple>::type).name()  << std::endl;
}
int main() {
	std::cout << "main: enter" << std::endl;
	//cfx_type();
	//cfx_enum();
	//cfx_any();
	cfx_tuple();
	std::cout << "main: exit" << std::endl;
	return 0;
}
