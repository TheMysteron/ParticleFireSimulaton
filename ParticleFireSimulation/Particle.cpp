#include "Particle.h"
#include <stdlib.h>
#include <math.h>
#include <corecrt_math_defines.h>

using namespace std;

namespace jcs {

	Particle::Particle() : m_x(0), m_y(0) {
		m_direction = (2 * M_PI * rand()) / RAND_MAX;
		m_speed = (SPEED_MOD * rand()) / RAND_MAX;

		m_xSpeed = m_speed * cos(m_direction);
		m_ySpeed = m_speed * sin(m_direction);
	}


	Particle::~Particle() {
	}

	void Particle::update(int interval) {

		if (m_x < -1.0 || m_x >= 1.0) {
			m_xSpeed = -m_xSpeed;
		}
		if (m_y < -1.0 || m_x >= 1.0) {
			m_ySpeed = -m_ySpeed;
		}

		m_x += (m_xSpeed * interval);
		m_y += (m_ySpeed * interval);
	}

}