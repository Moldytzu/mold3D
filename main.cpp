#include "mold3D/3D.h"

mold::render::objects::Pyramid pyramid;
mold::render::objects::Cube cube;
mold::render::objects::Plane ground;

float turnSpeed = 1.0f;

void Redraw()
{
   if (!mold::gui::GlobalConsole.Enabled)
   {
      if (mold::core::input::KeyStates[mold::core::input::Key::RIGHT] || mold::core::input::KeyStates[mold::core::input::Key::D])
         mold::render::GlobalCamera.Rotate(mold::Direction::Right, turnSpeed * mold::core::time::DeltaTime);

      if (mold::core::input::KeyStates[mold::core::input::Key::LEFT] || mold::core::input::KeyStates[mold::core::input::Key::A])
         mold::render::GlobalCamera.Rotate(mold::Direction::Left, turnSpeed * mold::core::time::DeltaTime);

      if (mold::core::input::KeyStates[mold::core::input::Key::UP] || mold::core::input::KeyStates[mold::core::input::Key::W])
         mold::render::GlobalCamera.Rotate(mold::Direction::Forward, turnSpeed * mold::core::time::DeltaTime);

      if (mold::core::input::KeyStates[mold::core::input::Key::DOWN] || mold::core::input::KeyStates[mold::core::input::Key::S])
         mold::render::GlobalCamera.Rotate(mold::Direction::Backward, turnSpeed * mold::core::time::DeltaTime);
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