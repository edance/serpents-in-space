#include "Score.h"
#include <sstream>
#include <zenilib.h>


using namespace std;
using namespace Zeni;
namespace Serpent {
Score::Score()
	: _currentScore(1)
{
}

void Score::render()
	const
{
	int temp = _currentScore;
	float offset = 25.0f;
	const float width = get_Window().get_width();

	while (temp != 0)
	{
		int num = temp % 10;

		ostringstream oss;
		oss << "digit" << num;
		String str;
		str = oss.str();
		Video &vr = get_Video();
		vr.apply_Texture(str);
		Vertex2f_Texture q0(Point2f(width - offset - 40.0f, 2.0f), Point2f(0.0f, 0.0f));
		Vertex2f_Texture q1(Point2f(width - offset - 40.0f, 42.0f), Point2f(0.0f, 1.0f));
		Vertex2f_Texture q2(Point2f(width - offset, 42.0f), Point2f(1.0f, 1.0f));
		Vertex2f_Texture q3(Point2f(width - offset, 2.0f), Point2f(1.0f, 0.0f));
		Quadrilateral<Vertex2f_Texture> quad(q0, q1, q2, q3);
		vr.render(quad);
		temp /= 10;
		offset += 35.0f;
		vr.unapply_Texture();
	}
	
}


void Score::changeScore(const int amount_) 
{
	_currentScore += amount_;
	_currentScore = (_currentScore < 0) ? 0 : _currentScore;
}

void Score::resetScore() 
{
	_currentScore = 0;
}

const int Score::getScore() const
{
	return _currentScore;
}
}