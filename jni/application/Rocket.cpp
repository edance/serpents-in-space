#include <zenilib.h>

#include "Rocket.h"
#include <math.h>

using namespace Zeni;
using namespace Zeni::Collision;

namespace Serpent
{
	Rocket::Rocket(const Zeni::Point3f &position_, const Zeni::Vector3f &velocity_)
		: m_corner(position_),
		m_scale(Zeni::Vector3f(3.0f, 3.0f, 3.0f)),
		m_velocity(velocity_), exploded(false), timeExploded(0.0f),
		_terminated(false)
	{
		if (!m_model)
			m_model = new Zeni::Model("models/rocket.3DS");

		if (!m_explosion)
			m_explosion = new Zeni::Model("models/sun.3DS");
		
		float angle = m_velocity.get_ij().angle_between(Vector3f(0.0f, -1.0f, 0.0f));
		angle = (m_velocity.i < 0.0f) ? 2.0f * Global::pi - angle : angle;
		m_rotation = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), angle);
		create_body();
	}

	Rocket & Rocket::operator=(const Rocket &rhs)
	{
		return *this;
	}

	Rocket::~Rocket()
	{
	}

	void Rocket::render()
	{
		if (!exploded)
		{
			const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();

			m_model->set_translate(m_corner);
			m_model->set_scale(m_scale);
			m_model->set_rotate(rotation.second, rotation.first);


			m_model->render();
		}
		else
		{
			if (m_scale.i < 7.0f)
			{
				m_explosion->set_translate(m_corner);
				m_explosion->set_scale(m_scale);
				m_explosion->render();
			}
			else
				_terminated = true;
		}
	}

    void Rocket::create_body()
	{
		m_body = Sphere(m_corner, m_scale.i * 10.0f);
	}

	const Zeni::Point3f Rocket::get_position() const
	{
		return m_corner;
	}

	void Rocket::move(const float timeStep)
	{
		if (!exploded)
		{
			m_corner += m_velocity * 100.0f;
			create_body();

			if (m_corner.x <= -4400.0f || m_corner.x >= 4400.0f || 
				m_corner.y <= -4400.0f || m_corner.y >= 4500.0f ||
				m_corner.z <= -390.0f || m_corner.z >= 390.0f)
			{
				explode(float(get_Timer_HQ().get_time().get_seconds_passed()));
			}
		}
		else
			m_scale += Vector3f(0.3f, 0.3f, 0.3f);
	}

	void Rocket::explode(const float curTime)
	{
		timeExploded = curTime;
		exploded = true;
	}

	const bool Rocket::isTerminated() const
	{
		return _terminated;
	}

	Model * Rocket::m_model = 0;
	Model * Rocket::m_explosion = 0;
}
