#ifndef PLANET_H
#define PLANET_H

#include <Zeni/Collision.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Sound.h>
#include <Zeni/Vector3f.h>

namespace Serpent
{
	class Planet
	{
	public:
		Planet(Zeni::String model, const float distFromSun, const Zeni::Vector3f &scale_);
		Planet & operator=(const Planet &rhs);
		~Planet();
		
		void render();
		
		const Zeni::Collision::Sphere & get_body() const {return m_body;}

		void move_orbit(const float timeStep);

		const Zeni::Point3f get_position() const;
	
	private:
		void create_body();
		float _distFromSun;
		float _theta;

		// Level 1
		Zeni::Model * m_model;
		
		// Level 2
		Zeni::Point3f m_corner;
		Zeni::Vector3f m_scale;
		Zeni::Quaternion m_rotation;

		// Level 3
		Zeni::Collision::Sphere m_body; // not motion so much as collision
	};
}

#endif
