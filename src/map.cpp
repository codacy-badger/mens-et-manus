#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

extern const GLint SCREEN_WIDTH, SCREEN_HEIGHT;
GLfloat camY = -100;

namespace map {
	void Init () {
		glLineWidth (2.0);
		glColor3f (0.1, 0.8, 0.8);
	}

	void Draw () {
		glClear (GL_COLOR_BUFFER_BIT);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		glScalef (1.f / SCREEN_WIDTH, 1.f / SCREEN_HEIGHT, 1.f / SCREEN_HEIGHT);
		gluLookAt (0, camY, 100, 0, 0, -1, 0, 1, 0);

		GLfloat hex_l = 100.f;
		GLfloat hex_r = hex_l * 0.866f; // 3*sqrt(3)
		glEnableClientState (GL_VERTEX_ARRAY);
		for (int i = -2; i <= 2; i++) {
			GLfloat dy = i * hex_l * 3 / 2;
			for (int j = -2; j <= 2; j++) {
				GLfloat dx = j * 2 * hex_r + (i & 1) * hex_r;
				// @formatter:off
				GLfloat vertices[] = {	-hex_r + dx, -hex_l/2 + dy, 0.f,
										 00.0f + dx, -hex_l   + dy, 0.f,
										 hex_r + dx, -hex_l/2 + dy, 0.f,
										 hex_r + dx,  hex_l/2 + dy, 0.f,
										 00.0f + dx,  hex_l   + dy, 0.f,
										-hex_r + dx,  hex_l/2 + dy, 0.f};
				// @formatter:on
				glVertexPointer (3, GL_FLOAT, 0, vertices);
				glDrawArrays (GL_LINE_LOOP, 0, 6);
			}
		}
		glDisableClientState (GL_VERTEX_ARRAY);
	}

	void KeyHandler (SDL_Keycode key) {
		switch (key) {
			case SDLK_UP:
				camY += 4;
				break;
			case SDLK_DOWN:
				camY -= 4;
				break;
		}
	}
}