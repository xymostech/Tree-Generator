#include "Branch.h"

GLint Branch::GetMaxBranchDepth()
{
	static GLint depth = 0;
	
	if(depth == 0)
	{
		glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &depth);
		depth /= 2;
	}
	
	return depth;
}

float Branch::GetRand(float a, float b)
{
	float randnum = rand() / (float)RAND_MAX;
	
	return (randnum * (b-a)) + a;
}

Branch::Branch(int new_age, int branch_num,
			   float size, float length,
			   float tilt_angle, float direction_angle,
			   float position_angle, float position_length) :
		age(0), size(size), length(length), tilt_angle(tilt_angle), 
		tilt_vector(cos(direction_angle), sin(direction_angle), 0),
		position(position_length*cos(position_angle),
				 position_length*sin(position_angle), 0),
		branch_chance(0), branch_num(branch_num)
{
	my_id = rand();
	
	while(age < new_age)
	{
		Age();
	}
}

Branch::~Branch()
{
	Branch *branch;
	
	for(int i=0; i<branches.size(); ++i)
	{
		branch = branches.at(i);
		
		delete branch;
	}
}

void Branch::Age(int time)
{
	for(; time > 0; --time)
	{
		Age();
	}
}

void Branch::Age()
{
	if(branches.size() == 0 && 
	   size > 0.2 && 
	   branch_chance > GetRand(0.3, 1.0) &&
	   branch_num < Branch::GetMaxBranchDepth())
	{
		float type = GetRand(0.0, 10.0);
		
		if(type < 2) // Split
		{
			int num_branch = floor(pow(GetRand(1.0, 1.06),20)) + 1;
			
			for(; num_branch > 0; --num_branch)
			{
				branches.push_back(new Branch(0,
											  branch_num + 1,
											  size / GetRand(1.2, 2.0),
											  1,
											  GetRand(10, 70),
											  GetRand(0, 2*M_PI),
											  GetRand(0, 2*M_PI),
											  GetRand(0, 1)));
			}
		}
		else // Branch
		{
			int num_branch = floor(pow(GetRand(1.0, 1.06),20));
			
			for(; num_branch > 0; --num_branch)
			{
				branches.push_back(new Branch(0, 
											  branch_num + 1,
											  size / GetRand(1.5, 2.5),
											  1,
											  GetRand(10, 50),
											  GetRand(0, 2*M_PI),
											  GetRand(0, 2*M_PI),
											  GetRand(0, 1)));
			}
			
			branches.push_back(new Branch(0,
										  branch_num + 1,
										  size * GetRand(.9, 1),
										  1));
		}
	}
	
	++age;
	branch_chance += 0.04;
	size *= GetRand(1.005, 1.02);
	length *= GetRand(1.005, 1.02);
	
	vector<Branch*>::iterator it=branches.begin(),
							  end=branches.end();
	for(; it!=end; ++it)
	{
		(*it)->Age();
	}
}

void Branch::DrawSelf()
{
	float angle, height;
	
	glBegin(GL_LINE_LOOP);
	
	for(int i=0; i<22; ++i)
	{
		angle = i * M_PI / 10.0;
		
		if(i % 2)
			height = length / 2;
		else
			height = 0;
		
		glVertex3f(size * sin(angle), size * cos(angle), height);
	}
	
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	
	for(int i=1; i<23; ++i)
	{
		angle = i * M_PI / 10.0;
		
		if(i % 2)
			height = length / 2;
		else
			height = length;
		
		glVertex3f(size * sin(angle), size * cos(angle), height);
	}
	
	glEnd();
}

void Branch::Draw()
{
	glPushMatrix();
	
	DrawSelf();
	
	glTranslatef(0, 0, length);
	
	vector<Branch*>::iterator it=branches.begin(),
							  end=branches.end();
	Branch* branch;
	for(; it!=end; ++it)
	{
		branch = *it;
		
		glPushMatrix();
		
		glTranslatef(branch->size * branch->position.i,
					 branch->size * branch->position.j, 
					 0);
		
		glRotatef(branch->tilt_angle, 
				  branch->tilt_vector.i, 
				  branch->tilt_vector.j,
				  0);
		
		branch->Draw();
		
		glPopMatrix();
	}
	
	glPopMatrix();
}
