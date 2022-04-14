#include "healer.h"

bool Healer::commitMove(Pawn* p)
{
	if (getTeamName() == p->getTeamName())
	{
		if (p->get_hp() < 12)
		{
			if (p->get_hp() == 11) { p->alterHP(1); }
			else { p->alterHP(getSpecialDamage()); }
			graphics::playSound(std::string(ASSET_PATH) + "heal.wav", 0.3, false);
			return true;
		}
		else { return false; }
	}
	else if (getTeamName() != p->getTeamName())
	{
		p->alterHP(damage); 
		graphics::playSound(std::string(ASSET_PATH) + "shooting_sound.wav", 0.3, false);
		return true;
	}
}