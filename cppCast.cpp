#include <iostream>
#include <functional>
#include <string>

class Birds {
	public:
	 Birds() {};
	 virtual ~Birds(){};
     virtual void Fly() {
        std::cout << "I am  a bird and I am flying" << std::endl;
     }
};

//燕子
class Swallow : public Birds {
public:
    Swallow(){}
    ~Swallow(){}
    void Fly() override {
        std::cout << "I am  a Swallow and I am flying" << std::endl;
    }
};
//大雁
class WildGoose : public Birds{
public:
    WildGoose(){}
    ~WildGoose(){}
    void Fly() override {
        std::cout << "I am  a Wild Goose and I am flying" << std::endl;
    }
	void show(void) {
        	std::cout << " Wild Goose show" << std::endl;
	}
};
//模拟鸟的飞行
void Fly(Birds& b){
    b.Fly();
}

void cfx_static_cast(void)
{
	// From sun to father cast, it is safe
	WildGoose goose;
	auto base = static_cast <Birds *>(&goose);
	base->Fly();
	
	// From  father to sun cast, it is Not safe
	Birds bird;
	auto goose2 = static_cast <WildGoose *>(&bird);
	goose2->Fly();
	goose2->show();
	return;
}
int main() {
	std::cout << "main: enter" << std::endl;
    WildGoose goose;
    Swallow s;
    Fly(s);
    Fly(goose);
	std::cout << "\tstatic cast" << std::endl;
	cfx_static_cast();
	std::cout << "main: exit" << std::endl;
	return 0;
}
