#include <zenilib.h>

#include "Boundaries.h"

using namespace Zeni;
using namespace Zeni::Collision;

namespace Serpent
{

	Boundaries::Boundaries()
	{
	}
	
	void Boundaries::render()
	{
		Zeni::Video &vr = Zeni::get_Video();
		Colors &cr = get_Colors();


		Zeni::Vertex3f_Texture p1(Point3f(-4500.0f, -4500.0f, -400.0f), Point2f(0.0f, 0.0f));
		Zeni::Vertex3f_Texture p2(Point3f(-4500.0f, 4500.0f, -400.0f), Point2f(0.0f, 10.0f));
		Zeni::Vertex3f_Texture p3(Point3f(4500.0f, 4500.0f, -400.0f), Point2f(10.0f, 10.0f));
		Zeni::Vertex3f_Texture p4(Point3f(4500.0f, -4500.0f, -400.0f), Point2f(10.0f, 0.0f));

		Zeni::Quadrilateral<Vertex3f_Texture> quad(p1, p2, p3, p4);

		quad.fax_Material(&Material("stars"));
		
		vr.render(quad);

		p1 = Vertex3f_Texture(Point3f(-4500.0f, 4500.0f, 400.0f), Point2f(0.0f, 0.0f));
		p2 = Vertex3f_Texture(Point3f(-4500.0f, 4500.0f, -400.0f), Point2f(0.0f, 1.8f));
		p3 = Vertex3f_Texture(Point3f(4500.0f, 4500.0f, -400.0f), Point2f(10.0f, 1.8f));
		p4 = Vertex3f_Texture(Point3f(4500.0f, 4500.0f, 400.0f), Point2f(10.0f, 0.0f));

		quad = Quadrilateral<Vertex3f_Texture> (p1, p2, p3, p4);
		
		quad.fax_Material(&Material("stars"));
		vr.render(quad);

		
		p1 = Vertex3f_Texture(Point3f(-4500.0f, -4500.0f, 400.0f), Point2f(0.0f, 0.0f));
		p2 = Vertex3f_Texture(Point3f(-4500.0f, -4500.0f, -400.0f), Point2f(0.0f, 1.8f));
		p3 = Vertex3f_Texture(Point3f(4500.0f, -4500.0f, -400.0f), Point2f(10.0f, 1.8f));
		p4 = Vertex3f_Texture(Point3f(4500.0f, -4500.0f, 400.0f), Point2f(10.0f, 0.0f));

		quad = Quadrilateral<Vertex3f_Texture> (p1, p2, p3, p4);
		
		quad.fax_Material(&Material("stars"));
		vr.render(quad);


		
		p1 = Vertex3f_Texture(Point3f(4500.0f, -4500.0f, 400.0f), Point2f(0.0f, 0.0f));
		p2 = Vertex3f_Texture(Point3f(4500.0f, -4500.0f, -400.0f), Point2f(0.0f, 1.8f));
		p3 = Vertex3f_Texture(Point3f(4500.0f, 4500.0f, -400.0f), Point2f(10.0f, 1.8f));
		p4 = Vertex3f_Texture(Point3f(4500.0f, 4500.0f, 400.0f), Point2f(10.0f, 0.0f));

		quad = Quadrilateral<Vertex3f_Texture> (p1, p2, p3, p4);
		
		quad.fax_Material(&Material("stars"));
		vr.render(quad);


		
		p1 = Vertex3f_Texture(Point3f(-4500.0f, -4500.0f, 400.0f), Point2f(0.0f, 0.0f));
		p2 = Vertex3f_Texture(Point3f(-4500.0f, -4500.0f, -400.0f), Point2f(0.0f, 1.8f));
		p3 = Vertex3f_Texture(Point3f(-4500.0f, 4500.0f, -400.0f), Point2f(10.0f, 1.8f));
		p4 = Vertex3f_Texture(Point3f(-4500.0f, 4500.0f, 400.0f), Point2f(10.0f, 0.0f));

		quad = Quadrilateral<Vertex3f_Texture> (p1, p2, p3, p4);
		
		quad.fax_Material(&Material("stars"));
		vr.render(quad);

		
		p1 = Vertex3f_Texture(Point3f(-4500.0f, -4500.0f, 400.0f), Point2f(0.0f, 0.0f));
		p2 = Vertex3f_Texture(Point3f(-4500.0f, 4500.0f, 400.0f), Point2f(0.0f, 10.0f));
		p3 = Vertex3f_Texture(Point3f(4500.0f, 4500.0f, 400.0f), Point2f(10.0f, 10.0f));
		p4 = Vertex3f_Texture(Point3f(4500.0f, -4500.0f, 400.0f), Point2f(10.0f, 0.0f));
		
		quad = Quadrilateral<Vertex3f_Texture> (p1, p2, p3, p4);
		
		quad.fax_Material(&Material("stars"));
		vr.render(quad);
		

	}
}
