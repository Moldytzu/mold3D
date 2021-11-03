#include "mold3D/3D.h"
mold::render::objects::Pyramid pyramid;
mold::render::objects::Cube cube;
mold::render::objects::Camera camera;
mold::render::objects::Plane ground;

mold::core::EventSystem eventSystem;

void Redraw()
{
   bool* keys = mold::core::input::GetKeyStates();
   float delta = mold::core::time::GetDeltaTime();

   if(keys['d'] || keys['D'])
      camera.Move(mold::Direction::Right, 5 * delta);

   if(keys['a'] || keys['A'])
      camera.Move(mold::Direction::Left, 5 * delta);

   if(keys['w'] || keys['W'])
      camera.Move(mold::Direction::Forward, 5 * delta);

   if(keys['s'] || keys['S'])
      camera.Move(mold::Direction::Backward, 5 * delta);


   cube.Draw();
   pyramid.Draw();
   ground.Draw();
}

int main()
{
   pyramid = mold::render::objects::Pyramid({0, 0, 0}, {5.0f, 1.0f, 0}, 1.0f);
   cube = mold::render::objects::Cube({0, 0, 0}, {1.0f, 1.0f, 1.0f}, 1.0f);
   ground = mold::render::objects::Plane({0,0,0}, {0.0f, 1.0f, 0.0f}, 3.0f);

   camera = mold::render::objects::Camera({0.0f, 1.0f, 1.5f});

   eventSystem.AttachCallback(mold::core::EventType::Redraw,(void*)Redraw);

   mold::core::Init(&camera, &eventSystem, 640, 480);
   mold::core::Run();
   return 0;
}