#include <iostream>
#include <string>
#include <typeinfo>
#include <functional>
//wisepointer
#include <memory>

using FilterFactoryCb = std::function<void(std::string & pStr)>;
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
	}
private:
	std::string CName_{"CFXWisePointerC"};
	std::string Pvalues_{"Pvalues"};
};
/*
 * pass by ref is good one
 main: enter
        enter cfx_shared_pointer
                        *****CFXWisePointerC: Con is called
                        CFXWisePointerC: name is:CFXWisePointerC
                        CFXWisePointerC: Pvalues is:CFXPvalues
        cfx_shared_pointer:object pointer 0xf1f2d0
        cfx_shared_pointer:shared pointer counter 1
        cfx_shared_pointer:shared pointer pointer 0x7ffe7c7e18e0
                enter cfx_use_shared_pointer_by_para_val
                        CFXWisePointerC: name is:CFXWisePointerC
                        CFXWisePointerC: Pvalues is:CFXPvalues
                exit cfx_use_shared_pointer_by_para_val
        exit cfx_shared_pointer
                        ~~~~CFXWisePointerC: De-Con is called
main: exit
*/
void cfx_use_shared_pointer_by_para_ref(std::shared_ptr<CFXWisePointerC>& pSharedPointer)
{
	std::cout << "\t\tenter " << __func__ << std::endl;
	std::cout << "\t\t" << __func__ << ":object pointer "<< pSharedPointer.get() << std::endl;
	std::cout << "\t\t" << __func__ << ":shared pointer counter "<< pSharedPointer.use_count() << std::endl;
	std::cout << "\t\t" << __func__ << ":shared pointer pointer "<< &pSharedPointer << std::endl;
	pSharedPointer->display();
	std::cout << "\t\texit " << __func__ << std::endl;
	return;
}
/*
 * pass by value isn't good one
 main: enter
        enter cfx_shared_pointer
                        *****CFXWisePointerC: Con is called
                        CFXWisePointerC: name is:CFXWisePointerC
                        CFXWisePointerC: Pvalues is:CFXPvalues
        cfx_shared_pointer:object pointer 0x210c2d0
        cfx_shared_pointer:shared pointer counter 1
        cfx_shared_pointer:shared pointer pointer 0x7ffe75168a70
                enter cfx_use_shared_pointer_by_para_val
                cfx_use_shared_pointer_by_para_val:object pointer 0x210c2d0
                cfx_use_shared_pointer_by_para_val:shared pointer counter 2
                cfx_use_shared_pointer_by_para_val:shared pointer pointer 0x7ffe75168a80
                        CFXWisePointerC: name is:CFXWisePointerC
                        CFXWisePointerC: Pvalues is:CFXPvalues
                exit cfx_use_shared_pointer_by_para_val
        exit cfx_shared_pointer
                        ~~~~CFXWisePointerC: De-Con is called
main: exit
*/
void cfx_use_shared_pointer_by_para_val(std::shared_ptr<CFXWisePointerC> pSharedPointer)
{
	std::cout << "\t\tenter " << __func__ << std::endl;
	std::cout << "\t\t" << __func__ << ":object pointer "<< pSharedPointer.get() << std::endl;
	std::cout << "\t\t" << __func__ << ":shared pointer counter "<< pSharedPointer.use_count() << std::endl;
	std::cout << "\t\t" << __func__ << ":shared pointer pointer "<< &pSharedPointer << std::endl;
	pSharedPointer->display();
	std::cout << "\t\texit " << __func__ << std::endl;
	return;
}
/*
 * Return shared Ptr is safe
 */
std::shared_ptr <CFXWisePointerC> cfx_factory(std::string pStr)
{
	std::shared_ptr <CFXWisePointerC> p1 = std::make_shared<CFXWisePointerC>(pStr);
	std::cout << "\n" << std::endl;
	std::cout << "\t\t\t" << __func__ << ":object pointer "<< p1.get() << std::endl;
	std::cout << "\t\t\t" << __func__ << ":shared pointer counter "<< p1.use_count() << std::endl;
	std::cout << "\t\t\t" << __func__ << ":shared pointer pointer "<< &p1 << std::endl;
	return p1;
}
void use_cfx_factory(void)
{
	std::cout << "\n" << std::endl;
	std::shared_ptr <CFXWisePointerC> p1 = cfx_factory ("use_cfx_factory_para");
	std::cout << "\t\t" << __func__ << ":object pointer "<< p1.get() << std::endl;
	std::cout << "\t\t" << __func__ << ":shared pointer counter "<< p1.use_count() << std::endl;
	std::cout << "\t\t" << __func__ << ":shared pointer pointer "<< &p1 << std::endl;
	
	return;
}
void cfx_shared_pointer(void)
{
//https://zhuanlan.zhihu.com/p/547647844#:~:text=1.shared_ptr%3CT%3E%20ptr%3B%2F%2Fptr%20%E7%9A%84%E6%84%8F%E4%B9%89%E5%B0%B1%E7%9B%B8%E5%BD%93%E4%BA%8E%E4%B8%80%E4%B8%AA%20NULL%20%E6%8C%87%E9%92%88%202.shared_ptr%3CT%3E%20ptr%20%28new,3.shared_ptr%3CT%3E%20ptr2%20%28ptr1%29%3B%20%2F%2F%20%E4%BD%BF%E7%94%A8%E6%8B%B7%E8%B4%9D%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%E7%9A%84%E6%96%B9%E6%B3%95%EF%BC%8C%E4%BC%9A%E8%AE%A9%E5%BC%95%E7%94%A8%E8%AE%A1%E6%95%B0%E5%8A%A0%201%20%2F%2Fshared_ptr%20%E5%8F%AF%E4%BB%A5%E5%BD%93%E4%BD%9C%E5%87%BD%E6%95%B0%E7%9A%84%E5%8F%82%E6%95%B0%E4%BC%A0%E9%80%92%EF%BC%8C%E6%88%96%E8%80%85%E5%BD%93%E4%BD%9C%E5%87%BD%E6%95%B0%E7%9A%84%E8%BF%94%E5%9B%9E%E5%80%BC%E8%BF%94%E5%9B%9E%EF%BC%8C%E8%BF%99%E4%B8%AA%E6%97%B6%E5%80%99%E5%85%B6%E5%AE%9E%E4%B9%9F%E7%9B%B8%E5%BD%93%E4%BA%8E%E4%BD%BF%E7%94%A8%E6%8B%B7%E8%B4%9D%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%E3%80%82
	std::cout << "\tenter " << __func__ << std::endl;
	//                                      class name        paras
	//auto l_shared_ptr1 = std::make_shared <CFXWisePointerC>("CFXPvalues");
	auto l_shared_ptr1 = std::make_shared <int>(16);
	std::cout << "\t" << __func__ << ":object l_shared_ptr1 type is  "<< typeid(l_shared_ptr1).name() << std::endl;
	//l_shared_ptr1->display();
	std::cout << "\t" << __func__ << ":CFX object pointer "<< l_shared_ptr1.get() << std::endl;
	std::cout << "\t" << __func__ << ":shared pointer counter "<< l_shared_ptr1.use_count() << std::endl;
	std::cout << "\t" << __func__ << ":shared pointer pointer "<< &l_shared_ptr1 << std::endl;
	int cfx_i=9;
	std::cout << "\t" << __func__ << ":cfx_i pointer "<< &cfx_i << std::endl;

	// pass reference, pointer in this function, use_count not increased
	//cfx_use_shared_pointer_by_para_ref(l_shared_ptr1);
	
	// pass value, pointer is copy as another one and use_count will be 2
	// Notes: Try not use pass by value
	//cfx_use_shared_pointer_by_para_val(l_shared_ptr1);
	std::cout << "\texit " << __func__ << std::endl;
	return;
}
int main() {
	std::cout << "main: enter" << std::endl;
	cfx_shared_pointer();
	std::cout << "\n" << std::endl;
	//use_cfx_factory();
	std::cout << "\nmain: start type" << std::endl;
	auto l_shared_ptr1 = std::make_shared <CFXWisePointerC>("CFXPvalues");
	std::cout << "\t" << __func__ << ":object l_shared_ptr1 type is  "<< typeid(l_shared_ptr1).name() << std::endl;
	std::cout << "main: exit" << std::endl;
	return 0;
}
