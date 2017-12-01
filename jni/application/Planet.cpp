#include <zenilib.h>

#include "Planet.h"
#include <math.h>

using namespace Zeni;
using namespace Zeni::Collision;

namespace Serpent
{
	Planet::Planet(Zeni::String model, const float distFromSun, const Zeni::Vector3f &scale_)
		: m_corner(Zeni::Point3f(distFromSun, 0.0f, 0.0f)),
		m_scale(scale_),
		m_rotation(Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f)),
		_distFromSun(distFromSun),
		_theta(0.0f)
	{
		m_model = new Zeni::Model("models/" + model + ".3DS");
		create_body();
	}

	Planet & Planet::operator=(const Planet &rhs)
	{
		return *this;
	}

	Planet::~Planet()
	{
		delete m_model;
	}

	void Planet::render()
	{
		const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();

		m_model->set_translate(m_corner);
		m_model->set_scale(m_scale);
		m_model->set_rotate(rotation.second, rotation.first);


		m_model->render();
	}

    void Planet::create_body()
	{
		m_body = Sphere(m_corner, m_scale.i * 10.0f);
	}

	void Planet::move_orbit(const float timeStep)
	{
		if (_distFromSun)
		{
			_theta += Zeni::Global::pi * timeStep / (_distFromSun / 100.0f);
			m_corner.x = _distFromSun * cos(_theta);
			m_corner.y = _distFromSun * sin(_theta);
			create_body();
		}
	}

	const Zeni::Point3f Planet::get_position() const
	{
		return m_corner;
	}
}
