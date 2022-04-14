#pragma once
#include "sgg/graphics.h"
#include "config.h"
#include "gameobject.h"
#include <string>

class Pawn : GameObject, Collidable
{
	float pos_x, pos_y;//current position
	const float init_pos_x, init_pos_y;//starting position

	float scale = 1.f;
	bool highlighted = false;
	bool active = false;
	bool turn;//can_be_selected
	bool alive = true;
	
	int hp;
	const int init_hp;;
	int probability;

	const int p_id;
	const std::string team_name;
	const std::string p_texture;
	char name[16];
	char description[160];

public:
	
	void const draw();
	void const draw_highlighted();
	void const draw_descriprion();
	void const draw_health(graphics::Brush& br);
	void update();

	Pawn(float x, float y, int hp, int id, int p, std::string tn, std::string tt, bool t, char n[], char dc[], int n_size, int dc_size)
		:pos_x(x), init_pos_x(x), pos_y(y), init_pos_y(y), hp(hp), init_hp(hp), p_id(id), 
		probability(p), team_name(tn), p_texture(tt), turn(t)
	{	
		for (int i = 0; i < n_size; i++) {
			name[i] = n[i];
		}
		for (int i = 0; i < dc_size; i++) {
			description[i] = dc[i];
		}
	};

	void setTurn(bool t) { turn = t; }
	void setHighlighted(bool h) { highlighted = h; }
	void setActive(bool a) { active = a; }

	float getX() { return pos_x; }
	float getY() { return pos_y; }

	inline void setX(float new_x) { pos_x = new_x; }
	inline void setY(float new_y) { pos_y = new_y; }

	float get_initi_X() { return init_pos_x; }
	float get_initi_Y() { return init_pos_y; }

	std::string getTeamName() { return team_name; }

	int get_init_hp(){ return init_hp; }
	int get_hp() { return hp; }
	void set_hp(int p) { hp -= p; }

	int get_probability() { return probability; }
	void set_probability(int p) { probability = p; }

	void alterHP(int p)
	{
		hp += p;
		if (hp <= 0) { alive = false; }
	}
	bool isAlive() { return alive; }

	virtual bool commitMove(Pawn* p) = 0;
	virtual void setSpecialDamage(int sd) = 0;
	virtual int getSpecialDamage() = 0;

	int get_p_id() { return p_id; }
	std::string getName() { return name; }

	bool contains(float x, float y);

	Disk getCollisionHull() const override;
	~Pawn();
};