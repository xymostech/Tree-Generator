#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <GLUT/glut.h>

class Input
{
	bool keys[256];
	bool last_keys[256];
	bool special[0x6C];
	bool last_special[0x6C];
	std::string same_key[2];
	
	int mouse_pos[2];
	bool mouse_button[3];
public:
	Input();
	~Input();
	void KeyFunc(unsigned char key);
	void KeyUpFunc(unsigned char key);
	void SpecialFunc(int key);
	void SpecialUpFunc(int key);
	void MouseMotionFunc(int x, int y);
	void MouseButtonFunc(int button, int state);
	
	bool KeyPressed(int key, int flags = KEY_PRESSED);
	bool SpecialPressed(int special_key, int flags = KEY_PRESSED);
	bool GetMouseButton(int button) { return mouse_button[button]; }
	int  GetMouseX() { return mouse_pos[0]; }
	int  GetMouseY() { return mouse_pos[1]; }
	
	void Update();
	
	enum State {
		KEY_PRESSED=1,
		KEY_RELEASED=2,
		KEY_EDGE=4,
		KEY_HOLD=8
	};
	
	enum Special {
		KEY_F1 = GLUT_KEY_F1,
		KEY_F2 = GLUT_KEY_F2,
		KEY_F3 = GLUT_KEY_F3,
		KEY_F4 = GLUT_KEY_F4,
		KEY_F5 = GLUT_KEY_F5,
		KEY_F6 = GLUT_KEY_F6,
		KEY_F7 = GLUT_KEY_F7,
		KEY_F8 = GLUT_KEY_F8,
		KEY_F9 = GLUT_KEY_F9,
		KEY_F10 = GLUT_KEY_F10,
		KEY_F11 = GLUT_KEY_F11,
		KEY_F12 = GLUT_KEY_F12,
		
		KEY_LEFT = GLUT_KEY_LEFT,
		KEY_RIGHT = GLUT_KEY_RIGHT,
		KEY_UP = GLUT_KEY_UP,
		KEY_DOWN = GLUT_KEY_DOWN,
		
		KEY_PAGEUP = GLUT_KEY_PAGE_UP,
		KEY_PAGEDOWN = GLUT_KEY_PAGE_DOWN,
		KEY_HOME = GLUT_KEY_HOME,
		KEY_END = GLUT_KEY_END,
		KEY_INSERT = GLUT_KEY_INSERT
	};
};

#endif