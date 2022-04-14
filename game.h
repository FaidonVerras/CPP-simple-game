#pragma once
#include <list>
#include <vector>
#include <string>
#include "pawn.h"
#include "attacker.h"
#include "healer.h"
#include "button.h"
#include "config.h"

class Game
{
public:
	enum  game_state_t { STATE_LOADING, STATE_HELP, STATE_MENU, STATE_GAMEPLAY, STATE_END };

protected:
	static Game* m_instance;
	Pawn* active_pawn = nullptr;
	game_state_t m_state = STATE_LOADING;

	bool turn = true;
	bool music_muted = false;
	bool menu_initiated = false;
	bool game_initiated = false;
	bool end_initiated = false;

	int redPawnsAlive = 5;
	int bluePawnsAlive = 5;

	std::vector<Pawn*> red_team;
	std::vector<Pawn*> blue_team;

	std::list<Button*> buttons;
	Button* mute_button;
	Button* X_button;
	Button* end_button;
	Button* quit_button;
	std::list<Button*> end_buttons;

	Game() {}
	~Game();

public:

	float bases_x[2][5];
	float bases_y[2][5];

	void draw();
	void drawBackground(graphics::Brush& br);

	void update();
	void init();

	void initMenu();
	void initEnd();

	bool isColliding(Pawn* p1, Pawn* p2);

	void setNotActive(std::vector<Pawn*> pawns, Pawn* active_pawns);
	void move(std::vector<Pawn*>& pawns, Pawn* active_pawn);
	void deleteDead(std::vector<Pawn*>& pawns);
	void countAlive(std::vector<Pawn*>& pawns, int& c){ c = pawns.size(); }

	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static Game* getInstance();
};