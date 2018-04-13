#pragma once

#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace jcs {
	struct Swarm {
		const static int NPARTICLES = 5000;
	public:
		Swarm();
		virtual ~Swarm();
		const Particle * const getParticles() { return m_pParticles; }
		void update(int elapsed);
	private:
		Particle * m_pParticles;
		int lastTime;
	};
}

#endif // !SWARM_H_