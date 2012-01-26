#include "Input.h"

Input::Input() {
	same_key[0] = "zxcvbnm,./asdfghjkl;'qwertyuiop[]\\`1234567890-=";
	same_key[1] = "ZXCVBNM<>?ASDFGHJKL:\"QWERTYUIOP{}|~!@#$%^&*()_+";
	
	for(int i=0; i<256; i++)
	{
		keys[i] = false;
		last_keys[i] = false;
	}
	
	for(int i=0; i<21; i++)
	{
		special[i] = false;
		last_special[i] = false;
	}
	
	for(int i=0; i<2; i++)
	{
		mouse_pos[i] = 0;
		mouse_button[i] = 0;
	}
}

Input::~Input() {
	
}

void Input::Update() {
	memcpy(last_keys, keys, 256);
	memcpy(last_special, special, 0x6C);
}

bool Input::KeyPressed(int key, int flags) {
	bool final=true;
	
	if(flags & KEY_PRESSED)
	{
		final = final && keys[key];
	}
	if(flags & KEY_RELEASED)
	{
		final = final && (!keys[key]);
	}
	if(flags & KEY_EDGE)
	{
		final = final && (keys[key] != last_keys[key]);
	}
	if(flags & KEY_HOLD)
	{
		final = final && (keys[key] == last_keys[key]);
	}
	
	return final;
}

bool Input::SpecialPressed(int special_key, int  flags) {
	bool final=true;
	
	if(flags & KEY_PRESSED)
	{
		final = final && special[special_key];
	}
	if(flags & KEY_RELEASED)
	{
		final = final && (!special[special_key]);
	}
	if(flags & KEY_EDGE)
	{
		final = final && (special[special_key] != last_special[special_key]);
	}
	if(flags & KEY_HOLD)
	{
		final = final && (special[special_key] == last_special[special_key]);
	}
	
	return final;
}

void Input::KeyFunc(unsigned char key) {
	keys[key] = true;
}

void Input::KeyUpFunc(unsigned char key) {
	keys[key] = false;
	
	for(int i=0; i<same_key[0].size(); i++)
	{
		if(same_key[0][i] == key) keys[same_key[1][i]] = false;
		else if(same_key[1][i] == key) keys[same_key[0][i]] = false;
	}
}

void Input::SpecialFunc(int key) {
	special[key] = true;
}

void Input::SpecialUpFunc(int key) {
	special[key] = false;
}

void Input::MouseMotionFunc(int x, int y) {
	mouse_pos[0] = x;
	mouse_pos[1] = y;
}

void Input::MouseButtonFunc(int button, int state) {
	mouse_button[button] = state;
}
