#include "include/rltk.hpp"
#include <sstream>

using namespace rltk;
using namespace rltk::colors;

void tick(double duration_ms) {
	std::stringstream ss;
	ss << "Frame duration: " << duration_ms << " ms (" << (1000.0 / duration_ms) << " FPS).";
	console->clear();
	console->print(1, 1, "Hello World", WHITE, BLACK);
	console->print(1, 2, ss.str(), YELLOW, BLUE);
}

int main()
{
	init(config_simple("../assets", 80, 50));
	run(tick);
	return 0;
}