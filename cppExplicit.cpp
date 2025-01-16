#include <iostream>
class Complex {
public:
    explicit Complex(int real, int imag = 0) : re(real), im(imag) {}
private:
    int re, im;
};
void display(const Complex& c) {
    std::cout << "Complex number" << std::endl;
}
int main() {
    Complex c1(10, 5);
    display(c1);
    //Complex c2 = 20; // This will cause a compilation error
    return 0;
}
