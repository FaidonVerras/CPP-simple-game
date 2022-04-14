#include "attacker.h"

bool Attacker::commitMove(Pawn* p)
{

	std::string sound_effect = "shooting_sound.wav";
	float r = std::rand() % 100;
	int d = damage;

	if (getTeamName() != p->getTeamName()) {

		if (get_p_id() == 1)//Buff Guy
		{
			if (p->get_hp() * 2 <= p->get_init_hp() && r < get_probability())
			{
				d = -p->get_hp();
			}
		}
		else if (get_p_id() == 2)//Gladiator
		{
			if (r <= get_probability())
			{
				d = special_damage;
			}
		}
		else if (get_p_id() == 3)//Archer
		{
			if (r <= get_probability())
			{
				d = -std::rand() % 5;
				if (d == 0) { sound_effect = "miss.wav"; }
			}
		}
		else if (get_p_id() == 4)//Tank
		{
			set_probability(1 / (13 - get_hp()) * 100);
			if (r < get_probability())
			{
				d = special_damage;
			}
		}

		p->alterHP(d);
		graphics::playSound(std::string(ASSET_PATH) + sound_effect, 0.5, false);
		return true;
	}
}