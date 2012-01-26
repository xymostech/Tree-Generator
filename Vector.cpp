#include "Vector.h"

using math::vector;

vector::vector() {
	i = 0.0;
	j = 0.0;
	k = 0.0;
}

vector::vector(float x, float y, float z) {
	i = x;
	j = y;
	k = z;
}

vector::vector(const float set[3]) {
	i = set[0];
	j = set[1];
	k = set[2];
}

vector::vector(const class vector &toSet){
	i = toSet.i;
	j = toSet.j;
	k = toSet.k;
}

float vector::dot(const class vector toDot) const {
	return (toDot.i*i+toDot.j*j+toDot.k*k);
}

class vector vector::cross(const class vector toCross) const {
	class vector _cross;
	_cross.i = j*toCross.k - k*toCross.j;
	_cross.j = k*toCross.i - i*toCross.k;
	_cross.k = i*toCross.j - j*toCross.i;
	return _cross;
}

float vector::dot(const float toDot[3]) const {
	return (i*toDot[0]+j*toDot[1]+k*toDot[2]);
}

class vector vector::cross(const float toCross[3]) const {
	class vector _cross;
	_cross.i = j*toCross[2] - k*toCross[1];
	_cross.j = k*toCross[0] - i*toCross[2];
	_cross.k = i*toCross[1] - j*toCross[0];
	return _cross;
}

class vector vector::operator+(const class vector &toAdd) const {
	class vector _add(*this);
	_add.i += toAdd.i;
	_add.j += toAdd.j;
	_add.k += toAdd.k;
	return _add;
}

class vector vector::operator-(const class vector &toSub) const {
	class vector _sub(*this);
	_sub.i -= toSub.i;
	_sub.j -= toSub.j;
	_sub.k -= toSub.k;
	return _sub;
}

class vector vector::operator=(const class vector &toSet) {
	i = toSet.i;
	j = toSet.j;
	k = toSet.k;
	return *this;
}

class vector vector::operator+(const float toAdd[3]) const {
	class vector _add(*this);
	_add.i += toAdd[0];
	_add.j += toAdd[1];
	_add.k += toAdd[2];
	return _add;
}

class vector vector::operator-(const float toSub[3]) const {
	class vector _sub(*this);
	_sub.i -= toSub[0];
	_sub.j -= toSub[1];
	_sub.k -= toSub[2];
	return _sub;
}

class vector vector::operator=(const float toSet[3]) {
	i = toSet[0];
	j = toSet[1];
	k = toSet[2];
	return *this;
}

class vector vector::operator*(const float &toMult) const {
	class vector _mult(*this);
	_mult.i *= toMult;
	_mult.j *= toMult;
	_mult.k *= toMult;
	return _mult;
}

class vector vector::operator/(const float &toDiv) const {
	class vector _div(*this);
	_div.i /= toDiv;
	_div.j /= toDiv;
	_div.k /= toDiv;
	return _div;
}

class vector vector::unit() {
	float length = len();
	i /= length;
	j /= length;
	k /= length;
	return *this;
}

float vector::len() const {
	return sqrt(i*i+j*j+k*k);
}

vector math::v(float i, float j, float k)
{
	return vector(i,j,k);
}
