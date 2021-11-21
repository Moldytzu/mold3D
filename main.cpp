#include "mold3D/3D.h"

mold::render::objects::Pyramid pyramid;
mold::render::objects::Cube cube;
mold::render::objects::Plane ground;

float turnSpeed = 1.0f;

void Redraw()
{
   bool *keys = mold::core::input::GetKeyStates();
   float delta = mold::core::time::GetDeltaTime();

   if (!mold::gui::GlobalConsole.Enabled)
   {
      if (keys[mold::core::input::Key::_RIGHT] || keys['D'] || keys['d'])
         mold::render::GlobalCamera.Rotate(mold::Direction::Right, turnSpeed * delta);

      if (keys[mold::core::input::Key::_LEFT] || keys['a'] || keys['A'])
         mold::render::GlobalCamera.Rotate(mold::Direction::Left, turnSpeed * delta);

      if (keys[mold::core::input::Key::_UP] || keys['w'] || keys['W'])
         mold::render::GlobalCamera.Rotate(mold::Direction::Forward, turnSpeed * delta);

      if (keys[mold::core::input::Key::_DOWN] || keys['s'] || keys['S'])
         mold::render::GlobalCamera.Rotate(mold::Direction::Backward, turnSpeed * delta);
   }

   cube.Draw();
   pyramid.Draw();
   ground.Draw();
}

void Resize()
{
   mold::render::SetProjection(90.0f);
}

bool BeforeExit()
{
   return false; // don't prevent exit
}

bool OnCommand(const char *command, mold::gui::Console *console)
{
   if (strcmp(command, "hello") == 0)
   {
      mold::core::logging::Info("Hello, World!");
      return true;
   }
   return false;
}

int main()
{
   mold::core::Init(800, 600);
   mold::render::SetProjection(90.0f);

   mold::gui::GlobalConsole.AddHelpCommand("hello");

   pyramid = mold::render::objects::Pyramid({0, 0, 0}, {5.0f, 1.0f, 0}, 1.0f);
   cube = mold::render::objects::Cube({0, 0, 0}, {1.0f, 1.0f, 1.0f}, 1.0f);
   ground = mold::render::objects::Plane({0, 0, 0}, {0.0f, 1.0f, 0.0f}, 3.0f);
   mold::render::GlobalCamera = mold::render::objects::Camera({0.0f, 1.0f, 1.5f});

   mold::core::GlobalEventSystem.AttachCallback(mold::core::EventType::Redraw, (void *)Redraw);
   mold::core::GlobalEventSystem.AttachCallback(mold::core::EventType::Resize, (void *)Resize);
   mold::core::GlobalEventSystem.AttachCallback(mold::core::EventType::BeforeExit, (void *)BeforeExit);
   mold::core::GlobalEventSystem.AttachCallback(mold::core::EventType::OnCommand, (void *)OnCommand);

   mold::core::Run();
   return 0;
}