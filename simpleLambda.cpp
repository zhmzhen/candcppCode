#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include <iostream>
using namespace std;
 
class Lambda
{
public:
    void sayHello() {
        std::cout << "Hello" << std::endl;
    };

    void lambda() {
        auto function = (
	// pass value of this
        //std::cout << "lambda enter" << std::endl;
	[this]{ 
            std::cout << "lambda after this" << std::endl;
            this->sayHello(); 
        });

        function();
    }
};

int main() {
	std::cout << "main: enter" << std::endl;
	std::vector<int> data = {1,2,3,4,5};
	//Define the lambda function, only define a iterater, the [](auto it){return it>3;}
	//not be run
	int cnt = std::count_if(
		std::cbegin(data),
		std::cend(data),
		[] (auto it) {
			return it>3;
		}
		);
	//The [](auto it){return it>3;} is called per each item in data
	std::cout << "count of data that is great than 3 is " << cnt << std::endl;

	std::cout << "pass this value in lamda" << std::endl;
	Lambda demo;
	demo.lambda();
	std::cout << "mutalble in lamda" << std::endl;
	int m{0}, n{0};
	auto mutable_f = [&, n] (int pI) mutable -> int {
		m = ++n + pI;
		return n;
	};
	n = mutable_f(4);
	std::cout << "mutalble in lamda, m from 0 to 5? :" << m << std::endl;
	std::cout << "mutalble in lamda, n from 0 to 1? :" << n << std::endl;
	std::cout << "main: exit" << std::endl;
	return 0;
}
