#include <iostream>
#include <SDL.h>
#include <math.h>
#include "Screen.h"
#include "Swarm.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace jcs;

int main(int argc, char **argv) {

	srand((int)time(NULL));

	Screen screen;
	if (!screen.init()) {
		cout << "Error initialising SDL: " << SDL_GetError() << endl;
		return 1;
	}

	Swarm swarm;

	const int HALF_WIDTH = Screen::SCREEN_WIDTH / 2;
	const int HALF_HEIGHT = Screen::SCREEN_HEIGHT / 2;

	while (true) {
		// Get time since program started
		int elapsed = SDL_GetTicks();

		// Check for messages/events
		if (!screen.processEvents()) {
			break;
		}

		// Update particles
		screen.clear();
		swarm.update(elapsed);

		// Draw Particles
		unsigned char red = (unsigned char)((1 + cos(elapsed * 0.001)) * 127.5);
		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0008)) * 127.5);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.0005)) * 127.5);

		const Particle * const pParticles = swarm.getParticles();
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * HALF_WIDTH;
			int y = (particle.m_y * HALF_WIDTH) + HALF_HEIGHT;

			screen.setPixel(x, y, red, green, blue);
		}

		/*for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
			for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
				screen.setPixel(x, y, red, green, blue);
			}
		}*/

		// Draw screen
		screen.update();
	}

	screen.close();

	return 0;
}