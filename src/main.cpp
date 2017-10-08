#include "include/rltk.hpp"
#include <sstream>
#include "utils/gui.hpp"
#include "systems/ActorSystem.hpp"

ActorSystem player;

void resize_main(rltk::layer_t *l, int w, int h) {
	l->w = w;
	l->h = h;
}

void tick(double duration_ms) {
	std::stringstream ss;
	//ss << "Frame duration: " << duration_ms << " ms (" << (1000.0 / duration_ms) << " FPS).";
	rltk::term(MAIN_LAYER)->clear();
	player.update();
	//rltk::term(MAIN_LAYER)->print(1, 2, ss.str(), rltk::colors::YELLOW, rltk::colors::BLUE);
}

int main()
{
	rltk::init(rltk::config_advanced("../assets", 720, 480));
	rltk::gui->add_layer(MAIN_LAYER, 0, 0, 720, 480, "8x8", resize_main);
	rltk::run(tick);
	return 0;
}