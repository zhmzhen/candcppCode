#include <iostream>
#include <functional>
#include <string>

using FilterFactoryCb = std::function<void(std::string & pStr)>;
class Tclass {
public:
	Tclass () {
		std::cout << "Con fun of Tclass is called" << std::endl;
	}
	~Tclass () {
		std::cout << "Con fun of ~Tclass is called" << std::endl;
	}
	void display() const {
		std::cout << "class name:" << name << std::endl;
	}
	void set(int iV)  {
		i = iV;
	}
	int get(void) const {
		std::cout << "get:  i= " << i << std::endl;
		return i;
	}
private:
	std::string name="Tclass";
	int i = 0;
};

FilterFactoryCb returnLamdaFunc(std::string & pStr) {
	Tclass *t = new Tclass();
	std::cout << "passed from returnLamdaFunc pStr:" << pStr << std::endl;
	return [t] (std::string& pLstring) -> void {
		std::cout << "Before remove t" << std::endl;
		t->display();
		delete t;
		std::cout << "after remove t" << std::endl;
		std::cout << "Passed pLstring: " << pLstring << std::endl;
	};
}
void olambda(void) {
	std::cout << "main: before define aMain " << std::endl;
	std::string l_l_str = "assignment";
	FilterFactoryCb aMain = returnLamdaFunc(l_l_str);
	std::cout << "main: after define aMain " << std::endl;
	std::string l_amain = "Call aMain";
	std::cout << "main: before call aMain " << std::endl;
	aMain(l_amain);
	std::cout << "main: after call aMain " << std::endl;
	return;

}
int gval = 9;
auto f_g = [] {
	std::cout << "f_g: gval= " << ++gval << std::endl;
};
void vlambda (void) {
	using namespace std;
	int i=6;
	Tclass tc; 
	tc.set(8);
	auto f = [=] (int a) -> int {
		cout << "\tIn lambda a= " << a << endl;
		tc.display();
		tc.get();
		int j = i+1;
		cout << "j= " << j << endl;
		cout << "gval= " << ++gval << endl;
		cout << "\t exit lambda" << endl;
		return i;
	};
	f(1);
	cout << "out of lambda i= " << i << endl;
	f_g();
	return;
}

void Addrlambda (void) {
	using namespace std;
	Tclass tc; 
	tc.set(8);
	int i = 6;
	auto f = [&] (int a) -> int {
		cout << "\tIn Address lambda a= " << a << endl;
		tc.display();
		tc.set(9);
		tc.get();
		i = i+1;
		cout << "i= " << i << endl;
		cout << "\t exit lambda" << endl;
		return i;
	};
	f(1);
	cout << "out of lambda i= " << i << endl;
	return;
}

void mutablelambda (void) {
	using namespace std;
	int i = 6;
	auto f = [i] (int a) mutable -> int {
		cout << "\tIn Address lambda a= " << a << endl;
		i = i+1;
		cout << "\ti= " << i << endl;
		cout << "\t&i= " << &i << endl;
		cout << "\t exit lambda" << endl;
		return a;
	};
	cout << "before call lambda i= " << i << endl;
	cout << "call f(1)  i= " << i << endl;
	f(1);
	cout << "call2 f(1)  i= " << i << endl;
	f(1);
	cout << "call3 f(1)  i= " << i << endl;
	f(1);
	cout << "out of lambda i= " << i << endl;
	cout << "out of lambda &i= " << &i << endl;
	return;
}
int main() {
	std::cout << "main: enter" << std::endl;
	//Addrlambda();
	mutablelambda();
	std::cout << "main: exit" << std::endl;
	return 0;
}
