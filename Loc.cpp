#include <cmath>
#include "Loc.h"

using std::abs;

Loc::Loc():
	_x(-2), _y(-2) {}

Loc::Loc(int a_x, int a_y):
	_x(a_x), _y(a_y) {}

Loc::Loc(const Loc& other):
	_x(other._x), _y(other._y) {}

Loc::Loc(const Mappable& other):
	_x(other.x()), _y(other.y()) {}

bool Loc::operator==(const Loc& rhs) const
{
	return _x == rhs._x && _y == rhs._y;
}

bool Loc::operator!=(const Loc& rhs) const
{
	return !(*this == rhs);
}

bool Loc::operator<(const Loc& rhs) const
{
	int myIndex = _y * 40 + _x;
	int hisIndex = rhs._y * 40 + rhs._x;
	return myIndex < hisIndex;
}

Loc Loc::operator+(const Loc& rhs) const
{
	Loc result;
	result._x = _x + rhs._x;
	result._y = _y + rhs._y;
	return result;
}

int Loc::x() const 
{
	return _x;
}

int Loc::y() const
{
	return _y;
}

int manhattanDistance(Loc start, Loc end)
{
 	return abs(start.x() - end.x()) + abs(start.y() - end.y());
}
