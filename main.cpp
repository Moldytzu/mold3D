#include "mold3D/3D.h"
mold::objects::Pyramid pyramid;
mold::objects::Cube cube;
mold::objects::Camera camera;

void draw()
{
   // Draw ground
   glColor3f(0, 1, 0);
   glBegin(GL_QUADS);
   glVertex3f(-10.0f, 0, -10.0f);
   glVertex3f(-10.0f, 0, 10.0f);
   glVertex3f(10.0f, 0, 10.0f);
   glVertex3f(10.0f, 0, -10.0f);
   glEnd();

   cube.Draw();
   pyramid.Draw();
}

int main(int argc, char **argv)
{
   mold::core::Init(argc, argv, &camera, draw, 640, 480);

   pyramid = mold::objects::Pyramid({0, 0, 0}, {5.0f, 1.0f, 0}, 1.0f);
   cube = mold::objects::Cube({0, 0, 0}, {1.0f, 1.0f, 1.0f}, 1.0f);
   camera = mold::objects::Camera({0.0f, 1.0f, 1.5f});

   // enter GLUT event processing cycle
   mold::core::Run();

   return 0;
}