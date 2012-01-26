/*
 *  mathObjects.h
 *	assortment of useful math objects (vectors, quaternions(not finished))
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

namespace math {
	class vector {
	public:
		vector();
		vector(float x, float y, float z);
		vector(const float set[3]);
		vector(const vector &toSet);
		
		float dot(const vector toDot) const;
		vector cross(const vector toCross) const;
		
		float dot(const float toDot[3]) const;
		vector cross(const float toCross[3]) const;
		
		vector operator+(const vector &toAdd) const;
		vector operator-(const vector &toSub) const;
		vector operator=(const vector &toSet);
		
		vector operator+(const float toAdd[3]) const;
		vector operator-(const float toSub[3]) const;
		vector operator=(const float toSet[3]);
		
		vector operator*(const float &toMult) const;
		vector operator/(const float &toDiv) const;
		
		vector unit();
		float len() const;
		
		float i,j,k;
	};
	
	vector v(float i, float j, float k);
}

#endif