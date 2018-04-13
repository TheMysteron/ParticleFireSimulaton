#include "Particle.h"
#include <stdlib.h>
#include <math.h>

using namespace std;

namespace jcs {

	Particle::Particle() {
		init();
	}

	Particle::~Particle() {
	}

	void Particle::init() {
		m_x = 0;
		m_y = 0;
		m_direction = (2 * M_PI * rand()) / RAND_MAX;
		m_speed = (SPEED_MOD * rand()) / RAND_MAX;

		m_speed *= m_speed;
	}

	void Particle::update(int interval) {
		if (rand() / RAND_MAX > 0.75) {
			init();
		}
		else {
			m_direction += interval * 0.0003;

			double m_xSpeed = m_speed * cos(m_direction);
			double m_ySpeed = m_speed * sin(m_direction);

			if (m_x < -X_RATIO || m_x >= X_RATIO || m_y < -Y_RATIO || m_y >= Y_RATIO) {
				init();
			}

			m_x += (m_xSpeed * interval);
			m_y += (m_ySpeed * interval);
		}
	}
}