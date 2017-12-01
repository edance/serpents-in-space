#pragma once
#include <zenilib.h>

using namespace std;
using namespace Zeni;

namespace Serpent
{
	class Health
	{
	public:
		Health();
		void render() const;
		void addLife();
		void removeLife();
		const int getNumLives() const;

	private:
		int _numLives;
	};

}