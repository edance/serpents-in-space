/* This file is part of the Zenipex Library (zenilib).
 * Copyleft (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * This source file is simply under the public domain.
 */

#include <zenilib.h>

#include "Serpent_State.h"

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Zeni;

class Instructions_State : public Gamestate_Base {

public:
  Instructions_State(){}

private:
  void on_key(const SDL_KeyboardEvent &event) {
    if(event.keysym.sym == SDLK_ESCAPE) {
      if(event.state == SDL_PRESSED)
        get_Game().pop_state();
    }
  }

  void render() {
    Video &vr = get_Video();
	vr.set_2d(make_pair(Point2f(), Point2f(1280.0f, 800.0f)), true);
	vr.apply_Texture((String)"instructions");
	
	Zeni::Vertex2f_Texture v1(Point2f(0.0f, 0.0f), Point2f(0.0f, 0.0f));
	Zeni::Vertex2f_Texture v2(Point2f(0.0f, 800.0f), Point2f(0.0f, 1.0f));
	Zeni::Vertex2f_Texture v3(Point2f(1280.0f, 800.0f), Point2f(1.0f, 1.0f));
	Zeni::Vertex2f_Texture v4(Point2f(1280.0f, 0.0f), Point2f(1.0f, 0.0f));

	Zeni::Quadrilateral<Vertex2f_Texture> quad(v1, v2, v3, v4);
	vr.render(quad);
	vr.unapply_Texture();
  }
};

class Bootstrap {
  class Gamestate_One_Initializer : public Gamestate_Zero_Initializer {
    virtual Gamestate_Base * operator()() {
      Window::set_title("Serpents in Space");

      get_Joysticks();
      get_Video();
      get_Textures();
      get_Fonts();
      get_Sounds();
      get_Game().joy_mouse.enabled = true;

      return new Title_State<Serpent::Serpent_State, Instructions_State>("Serpents in Space");
    }
  } m_goi;

public:
  Bootstrap() {
    g_gzi = &m_goi;
  }
} g_bootstrap;

int main(int argc, char **argv) {
  return zenilib_main(argc, argv);
}
