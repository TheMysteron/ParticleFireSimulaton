#pragma once
#include "Particle.h"

namespace jcs {
	class Swarm {
	private:
		Particle *m_pParticles;
		int lastTime;
	public:
		const static int NPARTICLES = 5000;
	public:
		Swarm();
		virtual ~Swarm();
		const Particle * const getParticles() { return m_pParticles; }
		void update(int elapsed);
	};
}