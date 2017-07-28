#include "Save.h"
#include "Map.h"
#include "util.h"

Map::Map () {
	tiles = mem::new2DArray<Tile> (size.x, size.y);
	for (uint16_t y = 0; y < size.y; y++)
		for (uint16_t x = 0; x < size.x; x++) {}
	}

Map::~Map () {
	mem::delete2DArray (tiles);
}

void Map::draw () {
	glLineWidth (2.0);
	glEnableClientState (GL_VERTEX_ARRAY);
	for (uint16_t y = 0; y < size.y; y++)
		for (uint16_t x = 0; x < size.x; x++)
			tiles[y][x].draw ();
	glDisableClientState (GL_VERTEX_ARRAY);
}

void Map::getHoveredTile (GLdouble x, GLdouble y, int16_t *tileX, int16_t *tileY) {
	struct {
		int16_t x; // Coordinates of centers
		int16_t y; // of the two nearest tiles
		GLdouble dist; // distance from point to tile center
	} tCntr[2];
	GLdouble x_hex = x / Tile::hex_r;           // Coordinates of the point in
	GLdouble y_hex = y / (Tile::hex_l * 3 / 2); // the tiles coordinate system
	int16_t y_floor = (int16_t) std::floor (y_hex);
	tCntr[0].x = (int16_t) std::floor (x_hex); // Choose nearest tiles
	tCntr[1].x = (int16_t) std::ceil (x_hex);
	if ((tCntr[0].x & 1) == (y_floor & 1)) { // Hard to explain
		tCntr[0].y = (int16_t) std::floor (y_hex);
		tCntr[1].y = (int16_t) std::ceil (y_hex);
	} else {
		tCntr[0].y = (int16_t) std::ceil (y_hex);
		tCntr[1].y = (int16_t) std::floor (y_hex);
	}
	for (int i = 0; i < 2; i++) // Calculate distance to the nearest tile center
	{
		GLdouble dist_x = x - tCntr[i].x * Tile::hex_r;
		GLdouble dist_y = y - tCntr[i].y * Tile::hex_l * 3 / 2;
		tCntr[i].dist = std::sqrt (dist_x * dist_x + dist_y * dist_y);
	}
	if (tCntr[0].dist < tCntr[1].dist) { // Return the nearest tile center
		*tileX = tCntr[0].x >> 1;
		*tileY = tCntr[0].y;
	} else {
		*tileX = tCntr[1].x >> 1;
		*tileY = tCntr[1].y;
	}
}
