#include "game.h"
#include "config.h"
#include <sgg/graphics.h>

void Game::draw()
{
	graphics::Brush br;
	graphics::Brush br2;

	if (m_state == STATE_LOADING) 
	{
		graphics::setFont(std::string(ASSET_PATH) + "ARCADE.TTF");
		char info[40];
		sprintf_s(info,"  LOADING . . .");
		graphics::drawText(CANVAS_WIDTH/2.5, CANVAS_HEIGHT/2, 50, info, br);
		
		return;
	}
	else if (m_state == STATE_MENU)
	{
		drawBackground(br);//draw background

		br.fill_color[0] = .0f;
		br.fill_color[1] = .4f;
		br.fill_color[2] = 1.f;
		graphics::setFont(std::string(ASSET_PATH) + "ANTICLIMAX.TTF");
		
		char info[30];
		sprintf_s(info, "PAWN FIGHTERS");
		br2.fill_color[0] = .8f;
		br2.fill_color[1] = .8f;
		br2.fill_color[2] = .8f;
		br2.fill_secondary_color[0] = .0f;
		br2.fill_secondary_color[1] = .5f;
		br2.fill_secondary_color[2] = .5f;
		br2.gradient = true;
		br2.gradient_dir_v = 1.f;
		br2.gradient_dir_v = 1.f;
		graphics::drawText(240, 150 , 100, info, br2);

		for (auto b : buttons) { b->draw(); }
		mute_button->draw();
	}
	else if (m_state == STATE_HELP)
	{
		drawBackground(br);//draw background

		br.texture = std::string(ASSET_PATH) + "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.0f;
		br.outline_color[0] = 1.0f;
		br.outline_color[1] = 1.0f;
		br.outline_color[2] = 1.0f;
		br.fill_opacity = 0.5f;
		br.outline_width = 33.f;
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 800.f, 400.f, br);

		int txt_size = 20;
		char txt[12][93] = { {"THE  GAME  CONSISTS  OF  TWO  TEAMS , "},{" AND "},{" ."},
			{"THE  OBJECTIVE  IS  TO  ELIMINATE  THE  OPPONENT  TEAM ."}, {"YOU  CAN  ATTACK  THE  OPPONENTS  PAWNS "},
			{" BY  CLICKING AND  DRAGGING A PAWN  FROM  YOUR  TEAM  OVER  A  OPPONENTS  PAWN ."},
			{"EACH  PAWN  HAS  SPECIAL  ABILITIES ."},{"HOVERING  YOUR  MOUSE  POINTER  OVER  A  PAWN  REVEALS  ITS  ABILITIES ."},
			{"EACH  TEAMS  TURN  IS  DETERMINED  BY  A  RECTANGULAR  OUTLINE  THAT  ENCOMPASSES  A  TEAM ."},
			{"GOOD  LUCK ,  PLAN  YOUR  EACH  MOVE  ACCORDINGLY ."},{" RED  TEAM " },{" BLUE  TEAM "} };
		int txt_x[10] = { 230, 580, 700, 230, 230, 230, 230, 230, 230, 230 };
		int txt_y[10] = { 140, 140, 140, 180, 220, 260, 300, 340, 380, 420 };


		graphics::setFont(std::string(ASSET_PATH) + "Maldini.TTF");

		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		br.fill_opacity = 1.f;

		for (int i = 0; i < 10; i++) 
		{
			graphics::drawText( txt_x[i], txt_y[i], txt_size, txt[i], br);
		}

		br.fill_color[0] = 0.9f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;

		graphics::drawText(500, 140, txt_size, txt[10], br);

		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.4f;
		br.fill_color[2] = 1.0f;

		graphics::drawText(620, 140, txt_size, txt[11], br);

		X_button->draw();
		mute_button->draw();
	}
	else if (m_state == STATE_GAMEPLAY)
	{
		drawBackground(br);//draw background

		br.fill_color[0] = 0.15f;
		br.fill_color[1] = 0.15f;
		br.fill_color[2] = 0.15f;
		br.fill_secondary_color[0] = 0.25f;
		br.fill_secondary_color[1] = 0.25f;
		br.fill_secondary_color[2] = 0.25f;
		br.gradient = false;
		br.texture = std::string(ASSET_PATH) + "base.png";

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				graphics::drawRect(bases_x[i][j] + 5, bases_y[i][j] + 40, PLAYER_SIZE * 2.75f, PLAYER_SIZE * 2.75f, br);
			}
		}

		for (auto pawn : red_team) { if (pawn != active_pawn) { pawn->draw(); } }
		for (auto pawn : blue_team) { if (pawn != active_pawn) { pawn->draw(); } }
		if (active_pawn != nullptr) { active_pawn->draw(); }

		br.texture = "";
		float h;
		if (turn) {
			br.outline_color[0] = 1.f;
			br.outline_color[1] = 0.f;	
			br.outline_color[2] = 0.f;
			h = 100.f;
		}
		else
		{
			br.outline_color[0] = 0.f;
			br.outline_color[1] = 0.4f;
			br.outline_color[2] = 1.f;
			h = 467.f;
		}
		br.fill_opacity = 0.f;
		br.outline_opacity = .5f;
		br.outline_width = 2.f;
		graphics::drawRect(600, h,1100, 150, br);
		br.texture = "";
		br.outline_opacity = 0.f;
		br.outline_width = 0.f;

		mute_button->draw();
	}
	else if (m_state == STATE_END)
	{
		graphics::setFont(std::string(ASSET_PATH) + "ARCADE.TTF");
		char info[30];

		br.fill_color[0] = .8f;
		br.fill_color[1] = .8f;
		br.fill_color[2] = .8f;
		br.fill_secondary_color[0] = .0f;
		br.fill_secondary_color[1] = .5f;
		br.fill_secondary_color[2] = .5f;
		br.gradient = true;
		br.gradient_dir_v = 1.f;
		br.gradient_dir_v = 1.f;
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

		if (redPawnsAlive > bluePawnsAlive)
		{
			br.fill_color[0] = 1.f;
			br.fill_color[1] = 0.f;
			br.fill_color[2] = 0.f;
			sprintf_s(info, "RED TEAM WON");
		}
		else
		{
			br.fill_color[0] = 0.f;
			br.fill_color[1] = 0.f;
			br.fill_color[2] = 1.f;
			sprintf_s(info, "BLUE TEAM WON");
		}
		br.gradient = false;
		graphics::drawText(CANVAS_WIDTH / 3.5, CANVAS_HEIGHT / 2.5, 100, info, br);

		for (Button* b : end_buttons) { b->draw(); }
		mute_button->draw();
	}
}

void Game::drawBackground(graphics::Brush& br)
{
	br.outline_opacity = 0.f;
	br.texture = std::string(ASSET_PATH) + "bg.png";
	br.fill_color[0] = .3f;
	br.fill_color[1] = .15f;
	br.fill_color[2] = .4f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}

void Game::update()
{
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	float mx = graphics::windowToCanvasX(mouse.cur_pos_x);
	float my = graphics::windowToCanvasY(mouse.cur_pos_y);

	if (m_state == STATE_LOADING)
	{
		graphics::preloadBitmaps(ASSET_PATH);
		m_state = STATE_MENU;
	}
	if (m_state == STATE_MENU)
	{
		if (!menu_initiated) { initMenu(); }

		Button* current_button = nullptr;

		for (auto b : buttons) {

			if (b->contains(mx, my))
			{
				b->setHighlighted(true);
				current_button = b;
			}
			else { b->setHighlighted(false); }

			if (mouse.button_left_released && current_button)
			{
				if (current_button->getText() == "START") { m_state = STATE_GAMEPLAY; }
				else if (current_button->getText() == "HELP") { m_state = STATE_HELP; }
				graphics::playSound(std::string(ASSET_PATH) + "button_click.wav", 0.5, false);
			}
		}
	}
	if (m_state == STATE_HELP) {
		if (X_button->contains(mx, my))
		{
			X_button->setHighlighted(true);

			if (mouse.button_left_released)
			{
				if (X_button->getText() == "X") { m_state = STATE_MENU; }
				graphics::playSound(std::string(ASSET_PATH) + "button_click.wav", 0.5, false);
			}
		}
		else { X_button->setHighlighted(false); }
	}
	if (m_state == STATE_GAMEPLAY) {

		if (!game_initiated) { init(); }

		for (auto pawn : red_team) { pawn->update(); }
		for (auto pawn : blue_team) { pawn->update(); }

		for (auto p : red_team) { p->setTurn(turn); }
		for (auto p : blue_team) { p->setTurn(!turn); }

		Pawn* current_pawn = nullptr;

		for (auto pawn : red_team) {
			if (pawn->contains(mx, my))
			{
				pawn->setHighlighted(true);
				current_pawn = pawn;
			}
			else
				pawn->setHighlighted(false);
		}

		for (auto pawn : blue_team) {
			if (pawn->contains(mx, my))
			{
				pawn->setHighlighted(true);
				current_pawn = pawn;
			}
			else
				pawn->setHighlighted(false);
		}

		if (mouse.button_left_pressed && current_pawn)//dragging
		{
			active_pawn = current_pawn;
			active_pawn->setActive(true);

			setNotActive(red_team, active_pawn);
			setNotActive(blue_team, active_pawn);
		}

		if (mouse.button_left_released && active_pawn != nullptr) {
			active_pawn->setActive(false);

			move(red_team, active_pawn);
			move(blue_team, active_pawn);

		}

		deleteDead(red_team);
		deleteDead(blue_team);

		countAlive(red_team, redPawnsAlive);
		countAlive(blue_team, bluePawnsAlive);

		if (redPawnsAlive == 0 || bluePawnsAlive == 0) { m_state = STATE_END; }

	}
	if (m_state == STATE_END)
	{
		if (!end_initiated) { initEnd(); }
		game_initiated = false;

		for (Button* b : end_buttons) 
		{
			if(b->contains(mx, my))
			{
				b->setHighlighted(true);
				if (mouse.button_left_released && b->getText() == "REPLAY")
				{
					graphics::playSound(std::string(ASSET_PATH) + "button_click.wav", 0.5, false);

					active_pawn = nullptr;
					red_team.clear();
					blue_team.clear();
					bool game_initiated = false;

					m_state = STATE_MENU;
				}
				else if (mouse.button_left_released && b->getText() == "QUIT")
				{
					graphics::playSound(std::string(ASSET_PATH) + "button_click.wav", 0.5, false);
					graphics::stopMessageLoop();
				}
			}
			else { b->setHighlighted(false); }
		}

		return;
	}
	
	if (m_state != STATE_LOADING && mute_button->contains(mx, my))//MUTE toggle
	{
		mute_button->setHighlighted(true);

		if  (mouse.button_left_released)
		{
			if (music_muted) 
			{ 
				graphics::playMusic(std::string(ASSET_PATH) + "game_music.mp3", 0.1f, true, 1000); 
				char l[] = "MUTE";
				mute_button->setText(l);
				mute_button->set_size(20.f, 5.f);
			}
			else 
			{
				graphics::stopMusic(700); 
				char l[] = "UNMUTE";
				mute_button->setText(l);
				mute_button->set_size(15.f, 3.5f);
			}
			music_muted = !music_muted;
			graphics::playSound(std::string(ASSET_PATH) + "button_click.wav", 0.5, false);
		}
		else { mute_button->setHighlighted(false); }
		return;
	}
}

inline void Game::init()//Initiate pawns
{
	game_initiated = true;
	const int hp[] = { 6,10,8,6,12 };
	int damage[] = { -1,-2,-1,-1,-1 };
	const int specialDamage[] = { 2,NULL,-4,NULL,-2 };
	const int probability[] = { NULL,25,33,50,NULL };
	std::string team_names[2] = { "Red Team","Blue Team" };
	std::string textures[5][2] = { {"healer_red.png","healer_blue.png"},{"knight_red.png","knight_blue.png"},
								   {"gladiator_red.png","gladiator_blue.png"},{"archer_red.png","archer_blue.png"},
								   {"orc_red.png","orc_blue.png" } };
	char names[5][10] = { {"Healer"}, {"Knight"}, {"Gladiator"}, {"Archer"}, {"Tank"} };
	char descriptions[5][95] = {{"Can heal a teammate by 1 whole heart"},
								{"1/4 chance to eliminate enemy if enemy has <50% of his health left. Always does 2 damage"},
								{"Has 1/3 chance to do 2 hearts of damade on an enemy"},
								{"1/2 of the time his damage may vary, he can do up to 2 hearts of damage, but he may miss"},
								{ "Has higher chance of doing double damage, the more of his hearts are remaining"} };

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			float x = ((PLAYER_WIDTH_RANGE)*i / 4.f) + 100;
			float y = ((PLAYER_HEIGTH_RANGE)*j / 1.5f) + 100;

			bases_x[j][i] = x;
			bases_y[j][i] = y;

			char* n = names[i];
			char* dc = descriptions[i];
			if (i == 0) {
				Healer* p = new Healer(x, y, hp[i], i, probability[i], team_names[j], textures[i][j], j,
							names[i], descriptions[i], 10, 90, damage[i], specialDamage[i]);

				if (j == 0) { red_team.push_back(p); }
				else { blue_team.push_back(p); }
			}
			else {
				Attacker* p = new Attacker(x, y, hp[i], i, probability[i], team_names[j], textures[i][j], j,
					names[i], descriptions[i], 10, 90, damage[i], specialDamage[i]);

				if (j == 0) { red_team.push_back(p); }
				else { blue_team.push_back(p); }
			}
		}
	}
}

void Game::initMenu()
{
	menu_initiated = true;

	if (!music_muted) { graphics::playMusic(std::string(ASSET_PATH) + "game_music.mp3", 0.15f, true, 7000); }

	float buttons_x[] = { CANVAS_WIDTH / 2, CANVAS_WIDTH / 2};
	float buttons_y[] = { CANVAS_HEIGHT / 2 , CANVAS_HEIGHT / 2 + 120.f};
	float buttons_w[] = { 200.f, 180.f};
	float buttons_h[] = { 80.f, 70.f};
	float offset[] = { 8.f, 20.f};
	char label[4][10] = { {"START"}, {"HELP"} ,{"MUTE"}, {"X"} };

	for (int i = 0; i < 2; i++)
	{
		Button *b = new Button(buttons_x[i], buttons_y[i], buttons_w[i], buttons_h[i], buttons_h[i], offset[i], label[i]);
		buttons.push_front(b);
	}

	//Mute button
	Button* mb = new Button(1150.f, 570.f, 50.f, 20.f, 20.f, 5.f, label[2]);
	mute_button = mb;

	//Help screen close button
	Button* xb = new Button(980.f, 115.f, 20.f, 20.f, 20.f, 5.f, label[3]);
	X_button = xb;
}

void Game::initEnd()
{
	end_initiated = true;
	char r[] = "REPLAY";
	Button* rb = new Button(CANVAS_WIDTH / 2.0, 360.0, 180.f, 70.f, 60.f, 2.f, r);
	end_buttons.push_back(rb);

	char q[] = "QUIT";
	Button* qb = new Button(CANVAS_WIDTH / 2.0, 460.0, 180.f, 70.f, 60.f, 30.f, q);
	end_buttons.push_back(qb);
}

void Game::setNotActive(std::vector<Pawn*> pawns, Pawn* active_pawn)
{
	for (auto pawn : pawns)
	{
		if (pawn != active_pawn) { pawn->setActive(false); }
	}
}

bool Game::isColliding(Pawn* p1, Pawn* p2) 
{
	
	Disk d1 = p1->getCollisionHull();
	Disk d2 = p2->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;
}

void Game::move(std::vector<Pawn*>& pawns, Pawn* active_pawn)
{
	for (auto pawn : pawns)
	{
		if (pawn != active_pawn && isColliding(active_pawn, pawn) && pawn->isAlive() && 
			(pawn->getTeamName() != active_pawn->getTeamName() || active_pawn->getName() == "Healer"))
		{
			bool done = active_pawn->commitMove(pawn);
			if (done) { turn = !turn; }
		}
	}
}

void Game::deleteDead(std::vector<Pawn*>& pawns)
{
	int i = 0;
	for(auto pawn : pawns)
	{
		if (!pawn->isAlive()) 
		{
			pawns.erase(pawns.begin() + i);
			delete pawn;
			break; 
		}
		i++;
	}
}


Game* Game::getInstance()
{
	if (!m_instance) { m_instance = new Game(); }
	return m_instance;
}
Game* Game::m_instance = nullptr;

Game::~Game()
{
	for (auto p : red_team) { delete p; }
	for (auto p : blue_team) { delete p; }
	red_team.clear();
	blue_team.clear();
	buttons.clear();
	end_buttons.clear();
}