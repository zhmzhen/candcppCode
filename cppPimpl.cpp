#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdlib>
#include "userPimpl.h"

//Private implementation
//define the base Mutex

/* |IMPLEMENTATION| User.cpp file */

#include "User.h"
#include <iostream>
using namespace std;

struct User::Impl {

	Impl(string name)
		: name(move(name)){
		cout << "Co User::Impl" << name << endl;
	};

	~Impl() {
		cout << "~Co User::Impl" << name << endl;
	};

	void welcomeMessage()
	{
		cout << "Welcome, " << name << endl;
	}

	string name;
	int salary = -1;
};

// Constructor connected with our Impl structure
User::User(string name)
	: pimpl(new Impl(move(name)))
{
	pimpl->welcomeMessage();
}

// Default Constructor
User::~User() = default;

// Assignment operator and Copy constructor

User::User(const User& other)
	: pimpl(new Impl(*other.pimpl))
{
}

User& User::operator=(User rhs)
{
	swap(pimpl, rhs.pimpl);
	return *this;
}

// Getter and setter
int User::getSalary()
{
	return pimpl->salary;
}

void User::setSalary(int salary)
{
	pimpl->salary = salary;
	cout << "Salary set to "
		<< salary << endl;
}

int main() {
	std::cout << "main: enter" << std::endl;

	std::cout << "main: exit" << std::endl;
	return 0;
}
