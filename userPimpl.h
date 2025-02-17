/* |INTERFACE| User.h file */

#pragma once
#include <memory> // PImpl
#include <string>
using namespace std;

class User {
public:
	// Constructor and Destructors

	~User();
	User(string name);

	// Assignment Operator and Copy Constructor

	User(const User& other);
	User& operator=(User rhs);

	// Getter
	int getSalary();

	// Setter
	void setSalary(int);

private:
	// Internal implementation class
	class Impl;

	// Pointer to the internal implementation
	unique_ptr<Impl> pimpl;
};

