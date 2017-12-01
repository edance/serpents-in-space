#ifndef ROCKET_H
#define ROCKET_H

#include <Zeni/Collision.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Sound.h>
#include <Zeni/Vector3f.h>

namespace Serpent
{
	class Rocket
	{
	public:
		Rocket(const Zeni::Point3f &position_, const Zeni::Vector3f &velocity_);
		Rocket & operator=(const Rocket &rhs);
		~Rocket();
		
		void render();
		
		const Zeni::Collision::Sphere & get_body() const {return m_body;}

		const Zeni::Point3f get_position() const;

		void move(const float timeStep);

		void explode(const float curTime);

		const bool isTerminated() const;
	
	private:
		void create_body();
		Zeni::Vector3f m_velocity;
		bool exploded;
		float timeExploded;
		bool _terminated;

		// Level 1
		static Zeni::Model * m_model;
		static Zeni::Model * m_explosion;
		
		// Level 2
		Zeni::Point3f m_corner;
		Zeni::Vector3f m_scale;
		Zeni::Quaternion m_rotation;

		// Level 3
		Zeni::Collision::Sphere m_body; // not motion so much as collision
	};
}

#endif
