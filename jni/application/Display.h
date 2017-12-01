#ifndef DISPLAY_H
#define DISPLAY_H

#include <Zeni/Vector2f.h>
#include "Score.h"
#include "Health.h"

namespace Serpent
{
	class Display
	{
	public:
		Display::Display();

		void render();
		void update();
		void changeScore(const int amount_);
		const int getScore() const;
		void loseLife();
		void addLife();
		const int getLives() const;
		/*
		crosshair render
		health render
		score render
		*/
	private:
		Score m_score;
		Health m_health;
	};
}

#endif
