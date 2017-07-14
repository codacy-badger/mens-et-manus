#pragma once

#include <GL/gl.h>
#include <cstdint>

class Tile {
	static GLfloat const hex_l;
	static GLfloat const hex_r;

	struct {
		uint16_t x, y;
	} pos;

public:
	void draw ();
};

