#ifndef SERPENT_STATE_H
#define SERPENT_STATE_H

#include "Player.h"
#include "Planet.h"
#include "Boundaries.h"
#include "Airplane.h"
#include "Rocket.h"
#include <Zeni/Gamestate.h>
#include <Zeni/Timer.h>
#include <sstream>

namespace Serpent {

  class Serpent_State : public Zeni::Gamestate_Base {
    struct Controls {
      Controls() : forward(false), left(false), back(false), right(false) {}

      bool forward;
      bool left;
      bool back;
      bool right;
    } m_controls;

  public:
    Serpent_State();
    ~Serpent_State();

    void on_key(const SDL_KeyboardEvent &event);
    void on_mouse_motion(const SDL_MouseMotionEvent &event);
	void on_mouse_button(const SDL_MouseButtonEvent &event);

    void perform_logic();

    void render();

  private:
    void partial_step(const float &time_step, const Zeni::Vector3f &velocity);

	void spawnPlanes();

	void advanceObjects(const float timeStep);

	void collideObjects(const float curTime);

    Zeni::Time_HQ time_passed;
	Zeni::Light m_light;

	bool gameover;

	std::list<Planet *> _planets;
	std::list<Airplane *> _airplanes;
	Planet * _mars;
    Player m_player;
	Boundaries m_boundaries;

    bool m_moved;
  };

}

#endif
