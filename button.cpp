#include "button.h"


void const Button::draw()
{
	if (highlighted) { draw_highlighted(); }

	graphics::Brush br;
	br.outline_opacity = 0.f;
	br.fill_color[0] = .2f;
	br.fill_color[1] = .2f;
	br.fill_color[2] = .2f;
	br.fill_secondary_color[0] = .3f;
	br.fill_secondary_color[1] = .3f;
	br.fill_secondary_color[2] = .3f;
	br.gradient = true;
	br.gradient_dir_u = 1.f;
	br.gradient_dir_v = 1.f;
	graphics::drawRect(pos_x, pos_y, width, height, br);

	br.gradient = false;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 0.0f;
	graphics::setFont(std::string(ASSET_PATH) + "ARCADE.TTF");
	graphics::drawText((pos_x - width/2) + offset, ( pos_y + height/2) , text_size, text, br);
}

void Button::draw_highlighted()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 0.0f;
	br.fill_opacity = 0.8f;
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, width + highlight_border, height + highlight_border, br);
}

bool Button::contains(float x, float y)
{
	bool a = x > pos_x - width / 2;
	bool b = x < pos_x + width / 2;
	bool c = y > pos_y - height / 2;
	bool d = y < pos_y + height / 2;

	return (a && b && c && d);
}

Button::~Button(){}