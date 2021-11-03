#include "mold3D/3D.h"
mold::render::objects::Pyramid pyramid;
mold::render::objects::Cube cube;
mold::render::objects::Camera camera;

void draw()
{
   bool* keys = mold::core::input::GetKeyStates();
   float delta = mold::core::time::GetDeltaTime();

   if(keys['d'] || keys['D'])
      camera.Move(DIRECTION_RIGHT, 5 * delta);

   if(keys['a'] || keys['A'])
      camera.Move(DIRECTION_LEFT,5 * delta);

   if(keys['w'] || keys['W'])
      camera.Move(DIRECTION_FORWARD,5 * delta);

   if(keys['s'] || keys['S'])
      camera.Move(DIRECTION_BACKWARD,5 * delta);

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

int main()
{
   pyramid = mold::render::objects::Pyramid({0, 0, 0}, {5.0f, 1.0f, 0}, 1.0f);
   cube = mold::render::objects::Cube({0, 0, 0}, {1.0f, 1.0f, 1.0f}, 1.0f);
   camera = mold::render::objects::Camera({0.0f, 1.0f, 1.5f});

   mold::core::EventSystem e;
   e.AttachCallback(610,(void*)10);
   std::map<int, void*> m = e.GetMap();
   printf("%d\n",m[610]);
   e.DetachCallback(610);
   m = e.GetMap();
   printf("%d\n",m[610]);

   mold::core::Init(&camera, draw, 640, 480);
   mold::core::Run();
   return 0;
}