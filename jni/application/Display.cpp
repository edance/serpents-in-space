#include <zenilib.h>

#include "Display.h"

using namespace Zeni;
using namespace Zeni::Collision;

namespace Serpent
{

	Display::Display()
		:m_score(), m_health()
	{
	}

	void Display::render()
	{
		Video &vr = Zeni::get_Video();
		const float height = get_Window().get_height() / 2 - 20.0f;
		const float width = get_Window().get_width() / 2 - 20.0f;
		vr.set_2d();
		Colors &cr = get_Colors();
		/* Crosshair render */
		vr.apply_Texture((String)"crosshair");
		Vertex2f_Texture v1(Point2f(width, height), Point2f(0.0f, 0.0f));
		Vertex2f_Texture v2(Point2f(width, height + 40.0f), Point2f(0.0f, 1.0f));
		Vertex2f_Texture v3(Point2f(width + 40.0f, height + 40.0f), Point2f(1.0f, 1.0f));
		Vertex2f_Texture v4(Point2f(width + 40.0f, height), Point2f(1.0f, 0.0f));

		Zeni::Quadrilateral<Vertex2f_Texture> quad(v1, v2, v3, v4);

		vr.render(quad);
		vr.unapply_Texture();
		/* Score render */
		m_score.render();

		/* Health render */
		m_health.render();

	}

	void Display::changeScore(const int amount_)
	{
		m_score.changeScore(amount_);
	}

	void Display::update()
	{
		m_score.changeScore(1);
	}

	void Display::addLife()
	{
		m_health.addLife();
	}

	void Display::loseLife()
	{
		m_health.removeLife();
	}

	const int Display::getLives() const
	{
		return m_health.getNumLives();
	}

	const int Display::getScore() const
	{
		return m_score.getScore();
	}

}
