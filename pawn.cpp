#include "pawn.h"

void const Pawn::draw()
{
	graphics::Brush br;
	graphics::Brush br2;//highlights brush

		
	if (turn && highlighted)
	{ 
		draw_highlighted();
		draw_descriprion(); 
	}
	else { scale = 1.f; }
	
	//draw card
	br.outline_opacity = 0.f;
	br.texture = std::string(ASSET_PATH) + p_texture;
	graphics::drawRect(pos_x, pos_y, PLAYER_SIZE * scale, PLAYER_SIZE * scale, br);

	//draw health
	draw_health(br);

}

void const Pawn::draw_highlighted()
{
	float h = 1.f * highlighted;
	float glow = 0.4f + 0.1f * cosf(graphics::getGlobalTime() / 200);
	scale = 1.15f;
	graphics::Brush br;
	if (init_pos_y < 150)
	{
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
	}
	else
	{
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.4f;
		br.fill_color[2] = 1.0f;
	}
	
	br.fill_opacity = 0.8f + (0.3f * sinf(graphics::getGlobalTime() / 300));
	br.fill_secondary_opacity = 0.0;
	br.fill_secondary_color[0] = .0f;
	br.fill_secondary_color[1] = .0f;
	br.fill_secondary_color[2] = .0f;
	br.gradient = true;
	br.outline_opacity = 0.0f;
	graphics::drawDisk(pos_x, pos_y + 4, PLAYER_SIZE * 1.5f, br);
	 
}

void const Pawn::draw_descriprion()
{
	graphics::Brush br;
	if (init_pos_y < 150)
	{
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
	}
	else
	{
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.4f;
		br.fill_color[2] = 1.0f;
	}
	graphics::setFont(std::string(ASSET_PATH) + "ARCADE.TTF");
	br.gradient = false;
	br.fill_opacity = 1.f - abs(init_pos_x - pos_x) * 0.01f - abs(init_pos_y - pos_y) * 0.01f;
	graphics::drawText(90, 250, 45, name, br);
	graphics::drawText(90, 300, 32, description, br);
}

void const Pawn::draw_health(graphics::Brush &br)
{
	if (hp > 6)
	{
		br.texture = std::string(ASSET_PATH) + "health_" + std::to_string(6) + ".png";

		graphics::drawRect(pos_x, pos_y + (PLAYER_SIZE / 2) + 15, PLAYER_SIZE * .8125f, PLAYER_SIZE * .3125f, br);

		br.texture = std::string(ASSET_PATH) + "health_" + std::to_string(hp - 6) + ".png";
		graphics::drawRect(pos_x, pos_y + (PLAYER_SIZE / 2) + 30, PLAYER_SIZE * .8125f, PLAYER_SIZE * .3125f, br);
	}
	else
	{
		br.texture = std::string(ASSET_PATH) + "health_" + std::to_string(hp) + ".png";
		graphics::drawRect(pos_x, pos_y + (PLAYER_SIZE / 2) + 15, PLAYER_SIZE * .8125f, PLAYER_SIZE * .3125f, br);
	}
}


void Pawn::update()
{
	if (turn) {
		graphics::MouseState mouse;
		graphics::getMouseState(mouse);

		float mx = graphics::windowToCanvasX(mouse.cur_pos_x);
		float my = graphics::windowToCanvasY(mouse.cur_pos_y);

		if (active) {
			setX(mx);
			setY(my);
		}
		else {
			setX(init_pos_x);
			setY(init_pos_y);
		}
	}	
}

bool Pawn::contains(float x, float y)
{
	return distance(x,y,pos_x,pos_y)< PLAYER_SIZE * .4f;
}

Disk Pawn::getCollisionHull() const
{
	Disk player_disk;
	player_disk.cx = pos_x;
	player_disk.cy = pos_y - 27;
	player_disk.radius = 33;
	return player_disk;
}

Pawn::~Pawn(){}