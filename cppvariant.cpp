#include <iostream>
#include <string>
#include <variant>
#include <algorithm>

int main() {
	std::cout << "enter main" << std::endl;
	std::variant<int, double, std::string> myVariant;
        std::cout << "space: index in myVariant= " << myVariant.index() << std::endl;
    myVariant = 42; // Assign an int
    // Access the int
    if (holds_alternative<int>(myVariant)) {
        std::cout << "int: index in myVariant= " << myVariant.index() << std::endl;
        std::cout << get<int>(myVariant) << std::endl;
    }

    myVariant = 3.14; // Assign a double
    // Access the double
    if (holds_alternative<double>(myVariant)) {
        std::cout << "double: index in myVariant= " << myVariant.index() << std::endl;
        std::cout << get<double>(myVariant) << std::endl;
    }

    //myVariant = "Hello, Variant!"; // Assign a string
    myVariant.emplace<std::string>("Hello, Variant!");
    // Access the string
    if (holds_alternative<std::string>(myVariant)) {
        std::cout << "String: index in myVariant= " << myVariant.index() << std::endl;
        std::cout << "String: value= " << get<std::string>(myVariant) << std::endl;
    }

	return 0;
}

