#include <iostream>
#include <string>
#include <typeinfo>
#include <functional>
#include <thread>
//wisepointer
#include <memory>

//using FilterFactoryCb = std::function<void(std::string & pStr)>;
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

template <typename T>
void cfx_t_ref(T pV) {
        ++pV;
        std::cout << "\n\t\tcfx_t_ref: pV after ++: " << pV << std::endl;
        return;
}

void cfx_non_t_ref(int pV) {
	++pV;
	std::cout << "\n\t\tcfx_non_t_ref: pV after ++: " << pV << std::endl;
	return;
}

void cfx_ref(void)
{
/*
 * https://blog.csdn.net/u014645632/article/details/78966340?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-78966340-blog-80031948.235%5Ev38%5Epc_relevant_default_base&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-78966340-blog-80031948.235%5Ev38%5Epc_relevant_default_base&utm_relevant_index=2
 *1)
 * std::ref()和引用的区别
 std::ref只是尝试模拟引用传递，并不能真正变成引用，在非模板情况下，std::ref根本没法实现引用传递，
 只有模板自动推导类型时，ref能用包装类型reference_wrapper来代替原本会被识别的值类型，而reference_wrapper能隐式转换为被引用的值的引用类型。
  2)
 * std::cref() is const ref
 * 3) std::reference_wrapper
 *    is a object used to create reference array
 *        int x=5, y=7, z=8;
    	  reference_wrapper<int> arr[] {x,y,z};
    	 for (auto a: arr)
        	cout << a << " ";
 *    see https://segmentfault.com/q/1010000042733944
 * https://blog.csdn.net/guoxiaojie_415/article/details/80031948
 * int int_a
 * auto r=std::ref(int_a);
	//等价于
   std::referencce_wrapper<std::dectype(int_a)> r(int_a);
 *
*/
	std::cout << "\n\tcfx_ref: enter" << std::endl;
	//std::cout << "\n\t" << __func__ << ":object l_shared_ptr1 type is  "<< typeid(l_shared_ptr1).name() << std::endl;
	int i = 1;	
	std::cout << "\n\t before call cfx_non_t_ref: i: " << i << std::endl;
	cfx_non_t_ref(std::ref(i));
/*
 * std::ref(i)返回的对象类型是一个reference_wrapper，而不是对i的直接引用（int&)
 */
	std::cout << "\n\t after call cfx_non_t_ref: i: " << i << std::endl;

	std::cout << "\n\t before call cfx_t_ref: i: " << i << std::endl;
/*
 * std::ref(i)返回的对象类型是一个reference_wrapper，而不是对i的直接引用（int&)
 * but template has ability to conclude it as a reference, therefore, after cfx_t_ref, i is 2
 */
	cfx_t_ref(std::ref(i));
	std::cout << "\n\t after call cfx_t_ref: i: " << i << std::endl;
	std::cout << "\n\tcfx_ref: exit" << std::endl;
	return;
}

void reference(int& v) {
  std::cout << "\t\treference: 左值引用" << std::endl;
}
void reference(int&& v) {
  std::cout << "\t\t右值引用" << std::endl;
}
template <typename T>
void pass(T&& v) {
  std::cout << "\t普通传参:";
  reference(v);
  std::cout << "\tstd::move 传参:";
  reference(std::move(v));
  std::cout << "\tstd::forward 传参:";
  reference(std::forward<T>(v));
}
void rightRef(void) {
  std::cout << "rightRef: 传递右值:" << std::endl;
  pass(1);
  std::cout << "rightRef:传递左值:" << std::endl;
  int v = 1;
  pass(v);
  return;
}
int main() {
	std::cout << "main: enter" << std::endl;
	rightRef();
	std::cout << "main: exit" << std::endl;
	return 0;
}
