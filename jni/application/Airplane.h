#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <Zeni/Collision.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Sound.h>
#include <Zeni/Vector3f.h>

namespace Serpent
{
	class Airplane
	{
	public:
		Airplane(const Zeni::Point3f &corner_, const Zeni::Vector3f &scale_);
		Airplane & operator=(const Airplane &rhs);
		~Airplane();

		void render();

		const Zeni::Collision::Capsule & get_body() const {return m_body;}

		void move(const float timeStep, const Zeni::Point3f marsLocation);

		void explode();

	private:
		void create_body();
		Zeni::Vector3f m_velocity;
		bool exploded;

		// Level 1
		static Zeni::Model * m_model;

		// Level 2
		Zeni::Point3f m_corner;
		Zeni::Vector3f m_scale;
		Zeni::Quaternion m_rotation;

		// Level 3
		Zeni::Collision::Capsule m_body; // not motion so much as collision
	};
}

#endif
