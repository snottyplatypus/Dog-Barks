#pragma once
enum gui_layer {
	MAIN_LAYER,
};

inline void resize_main(rltk::layer_t *l, int w, int h) {
	l->w = w;
	l->h = h;
}