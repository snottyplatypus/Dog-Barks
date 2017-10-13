#include "include/rltk/rltk.hpp"
#include "utils/gui.hpp"
#include "systems/PlayerSystem.hpp"
#include "level/Level.hpp"

Level level;

void tick(double duration_ms) {
	rltk::term(MAIN_LAYER)->clear();
	level.update();
}

int main()
{
	rltk::init(rltk::config_advanced("../assets", 720, 480));
	rltk::gui->add_layer(MAIN_LAYER, 0, 0, 720, 480, "8x8", resize_main);
	rltk::get_window()->setFramerateLimit(60);
	rltk::run(tick);
	return 0;
}