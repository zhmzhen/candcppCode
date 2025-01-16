#include <iostream>
#include <string>
#include <typeinfo>
#include <map>
#include <memory>

/*
 *
enum Color {
	red,
	white,
	black
};

Error because white has been used above
bool white = true; */
// limit domain enum
enum class ColorClass {
        red,
        white,
        black
};
bool white = true;
/*
 * [[noreturn]] void terminate();
 * [[deprecated(" try funY"]] void funX();
 * [[fallthrough]];
 * [[nodiscard]] int connect();
 */
class Btest {
public:
	Btest(){
		std::cout << "\t\t Co Btest" << std::endl;
	}
	~Btest() {
		std::cout << "\t\t ~Co Btest" << std::endl;
	}
private:
	int m_c_;
};
class A {
public:
	A()= default;
	~A() {}
	A(const A& a) = delete;
	A& operator =(const A& b) = delete;
	virtual void display() {
		std::cout << "\t class A" << std::endl;
	}
};
class B final : public A {
public:
	B(){
		std::cout << "\t\t Co B" << std::endl;
	}
	~B() {
		std::cout << "\t\t ~Co B" << std::endl;
	}
	B(std::string pNewName):new_name_(pNewName) {
		std::cout << "\t\t Co B2" << std::endl;
	}
	B(std::string pNewName, int a):new_name_(pNewName),m_a_(a),m_btest_usp(std::make_unique<Btest>()) {
		std::cout << "\t\t Co B3" << std::endl;
	}
	B(const B& b) = delete;
	B& operator =(const B& b) = delete;
	virtual void display() override {
		std::cout << "\t\t class B" << std::endl;
	};
	void displayNew() {
		std::cout << "\t\t new class name:" << new_name_ << std::endl;
	};
private:
	std::string new_name_;
	int m_a_;
	//std::unique_ptr<Btest> m_btest_usp = std::make_unique<Btest>();
	const std::unique_ptr<Btest> m_btest_usp;
};
void cfx_sp(void)
{
/*
 * unique
 */
	std::cout << "\n\tcfx_sp: start Smart pointer" << std::endl;
/*
	std::unique_ptr <B> sp_u_ptr = std::make_unique<B>("For cliff");
	sp_u_ptr->displayNew();
	std::unique_ptr <B> sp2_u_ptr = std::move(sp_u_ptr);
	if (sp_u_ptr == nullptr) {
		std::cout << "\tcfx_sp: move sp_u_ptr succ " << std::endl;
		sp2_u_ptr->displayNew();
	}
	else {
		std::cout << "\tcfx_sp: failed to move sp_u_ptr" << std::endl;
	}
*/
	/*B *p = new B("cliff3", 2);
	p->displayNew();
	delete p;
	*/
	std::unique_ptr <B> sp_u_ptr = std::make_unique<B>("For cliff");
	sp_u_ptr->displayNew();
	//.reset is release object
	//sp_u_ptr.reset();
	//.release() only give up ownership, the original pointer is still there
	//must delete manually
	B* bPtr = sp_u_ptr.release();
	if (sp_u_ptr) {
		std::cout << "\t\tcfx_sp: sp_u_ptr.operator" << std::endl;
	}
	delete bPtr;
	std::cout << "\n\tcfx_sp: The end of unique Smart pointer" << std::endl;
	/*
 * shared ptr
 */
	//init
	std::cout << "\n\tcfx_sp: start shared pointer" << std::endl;
	std::shared_ptr<Btest> sp1(new Btest());
	std::cout << "\n\tcfx_sp: use_count:" << sp1.use_count() << " after sp1(new Btest()" << std::endl;
	std::shared_ptr<Btest> sp2(sp1);
	std::cout << "\n\tcfx_sp: use_count:" << sp1.use_count() << " after copy co sp2(sp1)" << std::endl;
	sp2.reset();
	std::cout << "\n\tcfx_sp: use_count:" << sp1.use_count() << " after sp2 sp2.reset()" << std::endl;
	{
		// use = co sp3
		std::shared_ptr<Btest> sp3 = sp1;
		std::cout << "\n\t\tcfx_sp: use_count:" << sp1.use_count() << " after sp3 =sp1" << std::endl;
	}

	std::cout << "\n\tcfx_sp: use_count:" << sp1.use_count() << " after left sp3 domain" << std::endl;
	return;
}
int main() {
	std::cout << "main: C17 enter" << std::endl;
	[[maybe_unused]] int cfx;
	B bl;
	bl.display();
	std::map<int, std::string> l_mem;
	//auto [iter, isInsertedSucc] = l_mem.emplace(std::make_pair(1, "cliff"));
	auto [iter, isInsertedSucc] = l_mem.try_emplace(1, "cliff");
	if (isInsertedSucc) {
		std::cout << "\t 1, cliff is inserted succ" << std::endl;
	}
	else {
		std::cout << "\t 1, cliff is inserted failure" << std::endl;
	}
	l_mem.emplace(std::make_pair(2, "lily"));
	/*
 	 * auto
 	 * for complex data struct use, old way as below
	 * for (auto iter = l_mem.begin(); iter != l_mem.end(); iter++)
	 * because it use pointer
	 * 	std::cout << iter->first << "\t" << iter->second << std::endl;
	 * for single type, like int, use for each as below
	 */
	for (auto iter : l_mem)
	{
		std::cout << iter.first << "\t" << iter.second << std::endl;
	}
	/*
 * struct binding
 */
	// Must use reference, then you can change value
	for (auto& [mem_num, mem_name] : l_mem)
	{
		if (mem_num == 1) {
			mem_name.append(" chen");
		}
	}
	// it can not be use reference, but you have copy during run
	for (auto [mem_num, mem_name] : l_mem)
	{
		std::cout << mem_num << "\t" << mem_name << std::endl;
	}

	cfx_sp();
	std::cout << "main: C17 exit" << std::endl;
	return 0;
}
