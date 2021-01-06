#include "Any.hpp"

//#define DEBUG

#ifdef DEBUG
#define D(x) { x }
#else
#define D(x) {}
#endif //ifdef DEBUG

Any::Any() : _n(defaultValue) {
	D(std::cout << "ANY DEFAULT CONSTRUCTOR" << std::endl; )
}

Any::Any(const Any &other) {
	D(std::cout << "ANY COPY CONSTRUCTOR" << std::endl; )
	*this = other;
}

Any::~Any() {
	D(std::cout << "ANY DESTRUCTOR" << std::endl; )
}

Any & Any::operator=(const Any &other)  {
	if (this != &other) {
		_n = other._n;
	}
	return *this;
}

Any::Any(int n) : _n(n) {
	D(std::cout << "ANY INT CONSTRUCTOR" << std::endl; )
}

std::string Any::toString() const  {
	return "Any(" + std::to_string(_n) + ")";
}

int Any::getInt() const {
	return _n;
}

bool Any::operator==(const Any &other) const {
	return (_n == other._n);
}

bool Any::operator<(const Any &other) const {
	return (_n < other._n);
}

std::ostream & operator << (std::ostream & o, const Any & ref) {
	o << ref.toString();
	return o;
}

#undef DEBUG
