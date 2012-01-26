#ifndef BRANCH_H
#define BRANCH_H

#include <cmath>
#include <iostream>
#include <vector>
#include <OpenGL/gl.h>
#include "Vector.h"

using std::vector;
using std::cout;
using std::endl;

class Branch
{
	int my_id;
	
	int branch_num;
	
	float age;
	
	float size;
	float length;
	
	float tilt_angle;
	math::vector tilt_vector;
	
	math::vector position;
	
	float branch_chance;
	
	vector<Branch*> branches;
	
	float GetRand(float a, float b);
	
	void DrawSelf();
	
	void Age();
	
	static GLint GetMaxBranchDepth();
public:
	Branch(int age, int branch_num = 1,
		   float size = 1.0, float length = 1.0,
		   float tilt_angle = 0.0, float direction_angle = 0.0,
		   float position_angle = 0.0, float position_length = 0.0);
	~Branch();
	
	int GetAge() { return age; }
	
	void Age(int time);
	void Draw();
};

#endif