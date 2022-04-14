#include "sgg\graphics.h"
#include "config.h"
#include <string>
#include "game.h"
void draw()
{
	Game* mygame = Game::getInstance();
	mygame->draw();
}

void update(float ms)
{
	Game* mygame = Game::getInstance();
	mygame->update();
}

int main(int argc, char** argv) 
{
	graphics::createWindow(CANVAS_WIDTH, CANVAS_HEIGHT, "Pawn Fighters");
	Game* game = Game::getInstance();

	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	graphics::startMessageLoop();

	Game::releaseInstance();
	return 0;
}