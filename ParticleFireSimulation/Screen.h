#pragma once

#ifndef SCREEN_H_
#define SCREEN_H_


#include <SDL.h>

namespace jcs {
	struct Screen {
		const static int SCREEN_WIDTH = 1000;
		const static int SCREEN_HEIGHT = 1000;
	public:
		Screen();
		virtual ~Screen();
		bool init();
		void close();
		bool processEvents();
		void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		void update();
		void boxBlur();
	private:
		SDL_Window * m_window;
		SDL_Renderer *m_renderer;
		SDL_Texture *m_texture;
		Uint32 *m_buffer1;
		Uint32 *m_buffer2;
	};
}

#endif // !SCREEN_H_