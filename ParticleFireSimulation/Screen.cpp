#include "Screen.h"
#include <cstring>

using namespace std;

namespace jcs {

	Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL) {
	}


	Screen::~Screen() {
	}

	bool Screen::init() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			return false;
		}

		m_window = SDL_CreateWindow(
			"Particle Fire Simulation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE);

		if (m_window == NULL) {
			SDL_Quit();
			return false;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (m_renderer == NULL) {
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (m_texture == NULL) {
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

		memset(m_buffer1, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
		memset(m_buffer2, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

		return true;
	}

	bool Screen::processEvents() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return false;
			}
		}
		return true;
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
			return;
		}

		Uint32 colour = 0;

		colour += red;
		colour <<= 8;
		colour += green;
		colour <<= 8;
		colour += blue;
		colour <<= 8;
		colour += 0xFF;

		m_buffer1[(y * SCREEN_WIDTH) + x] = colour;
	}

	void Screen::update() {
		SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	void Screen::boxBlur() {

		/*
		Current colouring:
		0 0 0
		0 9 0
		0 0 0

		Wanted colouring:
		1 1 1
		1 1 1
		1 1 1
		*/

		// Swap the buffers, so pixel is in m_buffer2 and we are drawing to m_buffer1.
		Uint32 *temp = m_buffer1;
		m_buffer1 = m_buffer2;
		m_buffer2 = temp;

		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {

				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;

				for (short row = -1; row <= 1; row++) {
					for (short col = -1; col <= 1; col++) {
						int currentX = x + col;
						int currentY = y + row;

						if (currentX >= 0 &&
							currentX < SCREEN_WIDTH &&
							currentY >= 0 &&
							currentY < SCREEN_HEIGHT) {

							Uint32 colour = m_buffer2[(currentY * SCREEN_WIDTH) + currentX];

							Uint8 red = colour >> 24;
							Uint8 green = colour >> 16;
							Uint8 blue = colour >> 8;

							redTotal += red;
							greenTotal += green;
							blueTotal += blue;
						}
					}
				}

				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;

				setPixel(x, y, red, green, blue);
			}
		}
	}

	void Screen::close() {
		delete[] m_buffer1;
		delete[] m_buffer2;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

}