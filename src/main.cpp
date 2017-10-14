#include <sstream>
#include "include/rltk/rltk.hpp"
#include "utils/gui.hpp"
#include "systems/PlayerSystem.hpp"
#include "level/Level.hpp"

Level level;

void tick(double duration_ms) {
	rltk::term(MAIN_LAYER)->clear();
	rltk::term(GUI_LAYER)->clear();
	rltk::term(MISC_LAYER)->clear();
	level.update();
}

int main()
{
	rltk::init(rltk::config_advanced("../assets", 720, 480));
	int windowWidth = 720;
	int windowHeight = 480;
	rltk::gui->add_layer(MAIN_LAYER, 0, 0, windowWidth, windowHeight, "8x8", resize_main);
	rltk::gui->add_layer(GUI_LAYER, 0, 0, windowWidth, windowHeight, "8x8", resize_main);
	rltk::gui->add_layer(MISC_LAYER, 0, 0, windowWidth, windowHeight, "8x8", resize_main);
	rltk::get_window()->setFramerateLimit(60);
	rltk::run(tick);
	return 0;
}