#pragma once
namespace jcs {
	struct Particle {
		double m_x;
		double m_y;
	private:
		double SPEED_MOD = 0.0001;
		double m_speed;
		double m_xSpeed;
		double m_ySpeed;
		double m_direction;
	public:
		Particle();
		virtual ~Particle();
		void update(int interval);
	};
}