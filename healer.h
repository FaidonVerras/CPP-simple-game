#pragma once
#include "pawn.h"

class Healer : public Pawn
{
	int special_damage;
	const int damage;

public:

	Healer(float x, float y, int hp, int id, int p, std::string tn, std::string tt,
		bool t, char n[], char dc[], int n_size, int dc_size, int dmg, int sdmg)
		:Pawn(x, y, hp, id, p, tn, tt, t, n, dc, n_size, dc_size), damage(dmg), special_damage(sdmg)
	{};

	bool commitMove(Pawn* p);

	void setSpecialDamage(int sd) { special_damage = sd; }
	int getSpecialDamage() { return special_damage; }
};