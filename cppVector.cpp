#include <iostream>
#include <string>
#include <vector>
#include <memory>
class CFX {
public:
	CFX() {std::cout << "\t\tCon is called" << std::endl;}
	// copy
	CFX(const CFX& cfx) {
		std::cout << "\t\tCopy-Con is called" << std::endl;
		this->money_ = cfx.money_;}
	//Assignment
	CFX& operator=(const CFX& cfx) {
		std::cout << "\t\t=-Con is called" << std::endl;
		this->money_ = cfx.money_;
		return *this;
	}
	~CFX() {std::cout << "\t\tDe-Con is called" << std::endl;}
	void display(void) {
		std::cout << "\t\tFunction name: <" << __func__ << "> Money = <" << money_<< ">"  << std::endl;
	}
	void setMoney(int m) { money_ = m;}
	int getMoney() const {return money_;}
private:
	int money_ = 0;
};

void gtry(void) {
	std::cout << "\tgtry enter" << std::endl;
	std::vector<CFX> cfx_v;
	std::cout << "\tgtry: size()=<" << cfx_v.size() << ">"  << std::endl;
	std::cout << "\tgtry: size()=<" << cfx_v.capacity() << ">"  << std::endl;
	std::cout << "\tgtry: size()=<" << std::ssize(cfx_v) << ">"  << std::endl;
}
void ctry(void) {
	std::cout << "\tatry enter" << std::endl;
	std::vector<CFX> cfx_v;
	CFX cfxt;
	cfx_v.push_back(cfxt);
	CFX cfxt2;
	//cfx_v.insert(std::cbegin(cfx_v) + 1, cfxt2);
	//cfx_v.insert(cfx_v.end(), cfxt2);
	//cfx_v.emplace(cfx_v.end(), cfxt2);
	cfx_v.emplace_back(cfxt2);
	std::cout << "\tgtry: size()=<" << cfx_v.size() << ">"  << std::endl;
	std::cout << "\tgtry: size()=<" << cfx_v.capacity() << ">"  << std::endl;
	std::cout << "\tgtry: size()=<" << std::ssize(cfx_v) << ">"  << std::endl;
}

void ratry(void) {
	std::cout << "\trtry enter" << std::endl;
	//store reference to reduce the copy construct
	std::vector<std::reference_wrapper<std::unique_ptr<CFX>>> cfx_v;
	std::unique_ptr<CFX> cfxp1 = std::make_unique<CFX>();
	cfx_v.insert(cfx_v.end(), std::ref(cfxp1));
	auto cfxp2 = std::make_unique<CFX>();
	cfx_v.emplace_back(std::ref(cfxp2));
	auto cfxp3 = std::make_unique<CFX>();
	cfx_v.emplace_back(std::ref(cfxp3));
	std::cout << "\tratry: size()=<" << cfx_v.size() << ">"  << std::endl;
	std::cout << "\tratry: size()=<" << cfx_v.capacity() << ">"  << std::endl;
	std::cout << "\tratry: size()=<" << std::ssize(cfx_v) << ">"  << std::endl;
	std::cout << "\tratry: 0:"  << std::endl;
	cfx_v[0].get()->display();
	cfx_v.front().get()->setMoney(10);
	cfx_v.at(0).get()->display();
	cfx_v.back().get()->display();

	for (auto it=cfx_v.begin(); it !=cfx_v.end(); ) {
		if(it->get()->getMoney() == 10) {
			std::cout << "\tratry: remove current it"  << std::endl;
			cfx_v.erase(it++);
		}
		else {
			it++;
		}
	}
	std::cout << "\tratry: size()after remove =<" << cfx_v.size() << ">"  << std::endl;
	
}
void ptry(void) {
	std::cout << "\tptry enter" << std::endl;
	std::vector<std::unique_ptr<CFX>> cfx_v;
	std::unique_ptr<CFX> cfxp1 = std::make_unique<CFX>();
	cfx_v.insert(cfx_v.end(), std::move(cfxp1));
	cfx_v.insert(cfx_v.end(), std::make_unique<CFX>());
	//auto cfxp2 = std::make_unique<CFX>();
	//cfx_v.insert(std::cbegin(cfx_v) + 1, cfxt2);
	//cfx_v.insert(cfx_v.end(), cfxt2);
	cfx_v.emplace(cfx_v.end(), std::make_unique<CFX>());
	for (const auto ptr : cfx_v) {
		ptr->display();
	}
	//cfx_v.emplace_back(&cfxp2);
	std::cout << "\tptry: size()=<" << cfx_v.size() << ">"  << std::endl;
	std::cout << "\tptry: size()=<" << cfx_v.capacity() << ">"  << std::endl;
	std::cout << "\tptry: size()=<" << std::ssize(cfx_v) << ">"  << std::endl;
}
int main() {
	std::cout << "main: enter" << std::endl;
	gtry();
	//ctry();
	//ratry();
	ptry();
	std::cout << "main: exit" << std::endl;
	return 0;
}
