#pragma once

#include <string>
#include <iostream>

class Any {
public:
	static const int	defaultValue = 422;

	Any();
	Any(const Any &other);
	~Any();
	Any & operator = (const Any &other);

	explicit Any(int n);

	std::string		toString() const;
	int				getInt() const;

	bool operator == (const Any & other) const;
	bool operator <  (const Any & other) const;

private:
	int		_n;
};
