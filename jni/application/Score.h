#ifndef SCORE_H
#define SCORE_H
#include <zenilib.h>

using namespace std;
using namespace Zeni;

namespace Serpent
{
	class Score
	{
	public:
		Score();
		void render() const;
		void changeScore(const int amount_);
		void resetScore();
		const int getScore() const;

	private:
		int _currentScore;
	};
}
#endif