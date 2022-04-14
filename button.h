#pragma once
#include "sgg/graphics.h"
#include "config.h"
#include "gameobject.h"
#include <string>

class Button : GameObject
{
	const float pos_x, pos_y;
	const float width, height;
	const int highlight_border = 5;
	float offset;
	float text_size;
	bool highlighted = false;
		
	char text[10];

public:

	Button(float x, float y, float w, float h, float ts, float o, char txt[]) 
		:pos_x(x), pos_y(y), width(w), height(h),text_size(ts), offset(o)
	{
		for (int i = 0; i < sizeof(txt); i++) { text[i] = txt[i]; }
	};

	void const draw();
	void draw_highlighted();
	void setHighlighted(bool h) { highlighted = h; }

	void setText(char txt[]) 
	{
		for (int i = 0; i < sizeof(txt); i++) { text[i] = txt[i]; }
	}
	void set_size(float s, float o) 
	{
		text_size = s; 
		offset = o;
	}

	std::string getText() { return text; }

	bool contains(float x, float y);
	~Button();
};