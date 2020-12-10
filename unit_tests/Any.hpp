#pragma once

#include <string>
#include <iostream>

//#define DEBUG

#ifdef DEBUG
#define D(x) { x }
#else
#define D(x) {}
#endif //ifdef DEBUG

class Any {
public:
	static const int	defaultValue = 422;

	Any() : _n(defaultValue) {
		D(std::cout << "ANY DEFAULT CONSTRUCTOR" << std::endl; )
	}
	Any(const Any &other) {
		D(std::cout << "ANY COPY CONSTRUCTOR" << std::endl; )
		*this = other;
	}
	~Any() {
		D(std::cout << "ANY DESTRUCTOR" << std::endl; )
	}
	Any & operator = (const Any &other) {
		if (this != &other) {
			_n = other._n;
		}
		return *this;
	}

	explicit Any(int n) : _n(n) {
		D(std::cout << "ANY INT CONSTRUCTOR" << std::endl; )
	}

	std::string		toString() const {
		return "Any(" + std::to_string(_n) + ")";
	}
	const int &		getInt() const {
		return _n;
	}

	bool operator == (const Any & other) const {
		return (_n == other._n);
	}
	bool operator <  (const Any & other) const {
		return (_n < other._n);
	}

private:
	int		_n;
};

std::ostream & operator << (std::ostream & o, const Any & ref) {
	o << ref.toString();
	return o;
}

#undef DEBUG
