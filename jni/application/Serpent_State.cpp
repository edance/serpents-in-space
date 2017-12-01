#include <zenilib.h>

#include "Serpent_State.h"
#include <math.h>

using namespace Zeni;
using namespace Zeni::Collision;

namespace Serpent
{
	Serpent_State::Serpent_State()
		: m_player(Camera(Point3f(-4000.0f, 4000.0f, 0),
		Quaternion(),1.0f, 10000.0f), 
		Vector3f(0.0f, 0.0f, -39.0f),
		11.0f),
		m_boundaries(), gameover(false)
	{
		set_pausable(true);
		_planets.push_back(new Planet((String)"sun", 0.0f, Zeni::Vector3f(30.0f, 30.0f, 30.0f)));
		_planets.push_back(new Planet((String)"mercury", 500.0f, Zeni::Vector3f(7.5f, 7.5f, 7.5f)));
		_planets.push_back(new Planet((String)"venus", 1000.0f, Zeni::Vector3f(12.0f, 12.0f, 12.0f)));
		_planets.push_back(new Planet((String)"earth", 1500.0f, Zeni::Vector3f(13.5f, 13.5f, 13.5f)));
		_planets.push_back((_mars = new Planet((String)"mars", 2000.0f, Zeni::Vector3f(12.0f, 12.0f, 12.0f))));
		_planets.push_back(new Planet((String)"jupiter", 2500.0f, Zeni::Vector3f(21.0f, 21.0f, 21.0f)));
		_planets.push_back(new Planet((String)"saturn", 3000.0f, Zeni::Vector3f(13.5f, 13.5f, 13.5f)));
		_planets.push_back(new Planet((String)"uranus", 3500.0f, Zeni::Vector3f(10.5f, 10.5f, 10.5f)));
		_planets.push_back(new Planet((String)"neptune", 4000.0f, Zeni::Vector3f(9.0f, 9.0f, 9.0f)));

		_airplanes.push_back(new Airplane(Point3f(0.0f, 0.0f, 400.0f), Vector3f(10.0f, 10.0f, 10.0f)));

		m_light.position = Point3f(0.0f, 0.0f, 0.0f);

		get_Window().mouse_grab(true);
		get_Window().mouse_hide(true);
	}

	Serpent_State::~Serpent_State() {
		get_Window().mouse_grab(false);
		get_Window().mouse_hide(false);
	}

	void Serpent_State::on_key(const SDL_KeyboardEvent &event) {
		switch(event.keysym.sym) {
		case SDLK_w:
			m_controls.forward = event.type == SDL_KEYDOWN;
			break;

		case SDLK_a:
			m_controls.left = event.type == SDL_KEYDOWN;
			break;

		case SDLK_s:
			m_controls.back = event.type == SDL_KEYDOWN;
			break;

		case SDLK_d:
			m_controls.right = event.type == SDL_KEYDOWN;
			break;

		case SDLK_RETURN:
			if (gameover)
				get_Game().pop_state();
			break;

		case SDLK_SPACE:
			if(event.type == SDL_KEYDOWN) {
				m_player.jump();
				m_moved = true;
			}
			break;

		default:
			Gamestate_Base::on_key(event);
			break;
		}
	}

	void Serpent_State::on_mouse_motion(const SDL_MouseMotionEvent &event) {
		if (!gameover)
		{
			m_player.adjust_pitch(event.yrel / 400.0f);
			m_player.turn_left_xy(-event.xrel / 400.0f);
		}
	}

	void Serpent_State::on_mouse_button(const SDL_MouseButtonEvent &event)
	{
		if(event.button == SDL_BUTTON_LEFT && 
			event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN &&
			!gameover)
				m_player.fire();
	}

	void Serpent_State::perform_logic()
	{
		const Time_HQ current_time = get_Timer_HQ().get_time();
		float processing_time = float(current_time.get_seconds_since(time_passed));
    
		if (processing_time >= 1.0f / 40.0f && !gameover)
		{
			if (m_player.display.getLives() < 0)
				gameover = true;
			time_passed = current_time;

			/** Get forward and left vectors in the XY-plane **/
			const Vector3f forward = m_player.get_camera().get_forward().normalized();

			/** Get velocity vector split into a number of axes **/
			/* Increase speed as time goes on */
			const Vector3f velocity = m_player.getSpeed() * forward;

			/** Physics processing loop**/
			partial_step(processing_time, velocity.get_i());
			partial_step(processing_time, velocity.get_j());
			partial_step(processing_time, velocity.get_k());


			advanceObjects(processing_time);

			collideObjects(float(current_time.get_seconds_passed()));

			spawnPlanes();

			m_player.display.update();

			m_player.increaseSpeed();

			/* Dispose of old Rockets */
			for (list<Rocket *>::const_iterator it = m_player.rockets.begin(); it != m_player.rockets.end();)
			{
				if ((*it)->isTerminated())
				{
					delete (*it);
					it = m_player.rockets.erase(it);
					break;
				}
				else
					++it;
			}


		}
	}

	void Serpent_State::render()
	{
		Video &vr = get_Video();

		vr.set_lighting(true);
		vr.set_ambient_lighting(Color(1.0f, 0.0f, 0.0f, 0.0f));
		vr.set_Light(0, m_light);

		vr.set_3d(m_player.get_camera());

		for (list<Planet *>::const_iterator it = _planets.begin(); it != _planets.end(); ++it)
			(*it)->render();
		for (list<Airplane *>::const_iterator it = _airplanes.begin(); it != _airplanes.end(); ++it)
			(*it)->render();
		for (list<Rocket *>::const_iterator it = m_player.rockets.begin(); it != m_player.rockets.end(); ++it)
			(*it)->render();


		vr.set_lighting(false);

		m_boundaries.render();
		m_player.display.render();

		if (gameover)
		{
			const float width = (float)get_Window().get_width();
			const float height = (float)get_Window().get_height();
			// render game over screen
			vr.set_2d();
			Zeni::Color black = Color(0.5f, 0.0f, 0.0f, 0.0f);	
			Vertex2f_Color v1(Point2f(0.0f, 0.0f), black);
			Vertex2f_Color v2(Point2f(0.0f, height), black);
			Vertex2f_Color v3(Point2f(width, height), black);
			Vertex2f_Color v4(Point2f(width, 0.0f), black);
			Zeni::Quadrilateral <Vertex2f_Color> quad(v1, v2, v3, v4);
			vr.render(quad);
			// render score

			
			Font &fr = get_Fonts()["system_36_x600"];

			ostringstream oss;
			oss << "Game Over\nScore: " << m_player.display.getScore() << "\nPress Enter to Continue";

			fr.render_text(
				(String)oss.str(),
				Point2f(width / 2.0f, height / 2.0f - (0.5f * fr.get_text_height() * 3)),
						get_Colors()["title_text"],
						ZENI_CENTER);
			
		}
	}

	void Serpent_State::partial_step(const float &time_step, const Vector3f &velocity)
	{
		m_player.set_velocity(velocity);
		const Point3f backup_position = m_player.get_camera().position;

		m_player.step(time_step);

	}

	void Serpent_State::spawnPlanes()
	{
		int randNum = rand();
		if (randNum % 40  == 0)
		{
			const float theta = (float)rand() / Global::pi;
			_airplanes.push_back(new Airplane(Point3f(4500.0f * (float)cos(theta), 4500.0f * (float)sin(theta), 400.0f), Vector3f(5.0f, 5.0f, 5.0f)));
		}
	}

	void Serpent_State::advanceObjects(const float timeStep)
	{
		/* Advance every planet */
		for (list<Planet *>::const_iterator it = _planets.begin(); it != _planets.end(); ++it)
		(*it)->move_orbit(timeStep);

		/* Advance every plane */
		for (list<Airplane *>::const_iterator it = _airplanes.begin(); it != _airplanes.end(); ++it)
		(*it)->move(timeStep, _mars->get_position());

		/* Advance every rocket */
		for (list<Rocket *>::const_iterator it = m_player.rockets.begin(); it != m_player.rockets.end(); ++it)
		(*it)->move(timeStep);
	}

	void Serpent_State::collideObjects(const float curTime)
	{
		
		/* Collision detection between planets and others */
		for (list<Planet *>::const_iterator it = _planets.begin(); it != _planets.end(); ++it)
		{
			/* Player */
			if ((*it)->get_body().intersects(m_player.get_body()))
			{
				if (m_player.display.getLives() == 0)
					gameover = true;
				else
					m_player.respawn();
			}

			/* Manuel's airplanes */
			for (list<Airplane *>::const_iterator plane = _airplanes.begin(); plane != _airplanes.end(); ++plane)
				if ((*it)->get_body().intersects((*plane)->get_body()))
				{
					//explode airplanes
				}
		}

		/* Player collide with Airplane */
		for (list<Airplane *>::const_iterator plane = _airplanes.begin(); plane != _airplanes.end(); ++plane)
			if ((*plane)->get_body().intersects(m_player.get_body()))
			{
				if (m_player.display.getLives() == 0)
					gameover = true;
				else
					m_player.respawn();
			}

		/* Shooting Airplanes (Not Good) */
		for (list<Rocket *>::const_iterator it = m_player.rockets.begin(); it != m_player.rockets.end(); ++it)
		{
			for (list<Airplane *>::const_iterator plane = _airplanes.begin(); plane != _airplanes.end();)
			{
				if ((*it)->get_body().intersects((*plane)->get_body()))
				{
					(*it)->explode(curTime);
					delete (*plane);
					plane = _airplanes.erase(plane);
					m_player.display.changeScore(1000);
					break;
				}
				else 
					++plane;
			}
		}

		/* Shooting planets (Nothing happens) */
		for (list<Rocket *>::const_iterator it = m_player.rockets.begin(); it != m_player.rockets.end(); ++it)
		{
			for (list<Planet *>::const_iterator planet = _planets.begin(); planet != _planets.end(); ++planet)
			{
				if ((*it)->get_body().intersects((*planet)->get_body()))
				{
					(*it)->explode(curTime);
				}
			}
		}
	}
}
