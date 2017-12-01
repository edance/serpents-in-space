#include "Health.h"
#include <zenilib.h>


using namespace std;
using namespace Zeni;

namespace Serpent
{
	Health::Health()
		: _numLives(3)
	{
	}

	void Health::render()
		const
	{
		Video &vr = get_Video();
		const float height = get_Window().get_height();
		vr.apply_Texture((String)"heart");
		for (int i = 0; i < _numLives; ++i)
		{
			Vertex2f_Texture v0(Point2f(5.0f + 50.0f * i, height - 65.0f), Point2f(0.0f, 0.0f));
			Vertex2f_Texture v1(Point2f(5.0f + 50.0f * i, height - 25.0f), Point2f(0.0f, 1.0f));
			Vertex2f_Texture v2(Point2f(45.0f + 50.0f * i, height - 25.0f), Point2f(1.0f, 1.0f));
			Vertex2f_Texture v3(Point2f(45.0f + 50.0f * i, height - 65.0f), Point2f(1.0f, 0.0f));
			Quadrilateral<Vertex2f_Texture> hquad(v0, v1, v2, v3);
			vr.render(hquad);
		}
		vr.unapply_Texture();
	}

	void Health::addLife()
	{
		++ _numLives;
	}

	void Health::removeLife()
	{
		-- _numLives;
	}

	const int Health::getNumLives() const
	{
		return _numLives;
	}
}