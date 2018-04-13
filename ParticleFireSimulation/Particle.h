#pragma once

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Screen.h"

namespace jcs {
	struct Particle {
		double m_x;
		double m_y;
	public:
		Particle();
		virtual ~Particle();
		void update(int interval);
	private:
		const double SPEED_MOD = 0.04;
		double m_speed;
		double m_direction;
		const double X_RATIO = (double)Screen::SCREEN_WIDTH / Screen::SCREEN_HEIGHT;
		const double Y_RATIO = (double)Screen::SCREEN_HEIGHT / Screen::SCREEN_WIDTH;
	private:
		void init();
	};
}

#endif // !PARTICLE_H_