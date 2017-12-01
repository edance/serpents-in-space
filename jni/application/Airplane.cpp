#include <zenilib.h>

#include "Airplane.h"
#include <math.h>

using namespace Zeni;
using namespace Zeni::Collision;

namespace Serpent
{
	Airplane::Airplane(const Zeni::Point3f &corner_, const Zeni::Vector3f &scale_)
		: m_corner(corner_),
		m_scale(scale_),
		m_rotation(Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f)),
		m_velocity(1.0f, 0.0f, 0.0f), exploded(false)
	{
		if (!m_model)
			m_model = new Zeni::Model("models/airplane.3DS");
		create_body();
	}

	Airplane & Airplane::operator=(const Airplane &rhs)
	{
		return *this;
	}

	Airplane::~Airplane()
	{
	}

	void Airplane::render()
	{
		const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();

		m_model->set_translate(m_corner);
		m_model->set_scale(m_scale);
		m_model->set_rotate(rotation.second, rotation.first);

		m_model->render();

	}

    void Airplane::create_body()
	{
		Vector3f pointer = m_velocity.get_ij().normalized();
		m_body = Capsule(pointer * 20 * m_scale.i + m_corner,
			pointer * -20 * m_scale.i + m_corner, 10.0f);
	}

	void Airplane::move(const float timeStep, const Zeni::Point3f marsLocation)
	{
		/* given mars position head there */
		m_velocity = Vector3f (marsLocation.x - m_corner.x, marsLocation.y - m_corner.y, marsLocation.z - m_corner.z);
		m_velocity.normalize();
		float angle = m_velocity.get_ij().angle_between(Vector3f(0.0f, -1.0f, 0.0f));
		angle = (m_velocity.i < 0.0f) ? 2.0f * Global::pi - angle : angle;
		m_rotation = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), angle);
		m_corner += m_velocity * timeStep * 200.0f;
		create_body();
	}

	void Airplane::explode()
	{
		exploded = true;
	}

	Model * Airplane::m_model = 0;
}
