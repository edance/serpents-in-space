#include <zenilib.h>

#include "Player.h"

using namespace Zeni;
using namespace Zeni::Collision;

namespace Serpent {

  Player::Player(const Camera &camera_,
         const Vector3f &end_point_b_,
         const float radius_)
   : m_camera(camera_),
     m_end_point_b(end_point_b_),
     m_radius(radius_),
     m_is_on_ground(false), m_speed(400.0f), display()
  {
    m_camera.fov_rad = Zeni::Global::pi / 3.0f;

    create_body();
  }

  // Level 2
  void Player::set_position(const Point3f &position) {
    m_camera.position = position;
    create_body();
  }

  void Player::adjust_pitch(const float &phi) {
    const Quaternion backup = m_camera.orientation;
    const Vector3f backup_up = m_camera.get_up();

    m_camera.adjust_pitch(phi);

    if(m_camera.get_up().k < 0.0f && backup_up.k >= 0.0f)
      m_camera.orientation = backup;
  }

  void Player::turn_left_xy(const float &theta) {
    m_camera.turn_left_xy(theta);
  }

  void Player::set_on_ground(const bool &is_on_ground_) {
    m_is_on_ground = is_on_ground_;
    if(m_is_on_ground)
      m_velocity.k = 0.0f;
  }

  void Player::jump() {
    if(m_is_on_ground) {
      m_velocity.k += 60.0f;
      m_is_on_ground = false;
    }
  }

  void Player::step(const float &time_step) {
	  Zeni::Point3f nPoint = m_camera.position + time_step * m_velocity;
	  if (nPoint.x > -4400.0f && nPoint.x < 4400.0f && 
		  nPoint.y > -4400.0f && nPoint.y < 4500.0f &&
		  nPoint.z > -390.0f && nPoint.z < 390.0f)
	  {
		m_camera.position += time_step * m_velocity;
		create_body();
	  }
	  else
		  respawn();
  }

  void Player::create_body() {
    Sound &sr = get_Sound();

    m_body = Capsule(m_camera.position,
                     m_camera.position + m_end_point_b,
                     m_radius);

    sr.set_listener_position(m_camera.position);
    sr.set_listener_forward_and_up(m_camera.get_forward(), m_camera.get_up());
    sr.set_listener_velocity(m_velocity);
  }

  void Player::fire()
  {

	  // Create rocket in position with velocity
	  rockets.push_back(new Rocket(m_camera.position, m_camera.get_forward().normalized()));
  }

  void Player::increaseSpeed()
  {
	  m_speed += 0.25f;
  }

  const float Player::getSpeed() const
  {
	  return m_speed;
  }

  void Player::respawn()
  {
	  display.loseLife();
	  if (display.getLives() >= 0)
	  {
		  m_camera = Camera(Point3f(-4000.f, 4000.0f, 0.0f),
			Quaternion(),1.0f, 10000.0f);
		  create_body();
	  }
  }
}
