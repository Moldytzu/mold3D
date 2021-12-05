#include "mold3D/3D.h"

using namespace mold;
using namespace mold::core;

render::objects::Pyramid pyramid;
render::objects::Cube cube;
render::objects::Plane ground;

float turnSpeed = 1.0f;

void RedrawEvent()
{
   if (!gui::GlobalConsole.Enabled)
   {
      if (input::KeyStates[input::Key::RIGHT])
         render::GlobalCamera.Rotate(Direction::Right, turnSpeed * time::DeltaTime);

      if (input::KeyStates[input::Key::LEFT])
         render::GlobalCamera.Rotate(Direction::Left, turnSpeed * time::DeltaTime);

      if (input::KeyStates[input::Key::UP])
         render::GlobalCamera.Rotate(Direction::Forward, turnSpeed * time::DeltaTime);

      if (input::KeyStates[input::Key::DOWN])
         render::GlobalCamera.Rotate(Direction::Backward, turnSpeed * time::DeltaTime);

      if (input::KeyStates[input::Key::D])
         render::GlobalCamera.Move(Direction::Right, turnSpeed * time::DeltaTime);
      if (input::KeyStates[input::Key::A])
         render::GlobalCamera.Move(Direction::Left, turnSpeed * time::DeltaTime);
      if (input::KeyStates[input::Key::W])
         render::GlobalCamera.Move(Direction::Forward, turnSpeed * time::DeltaTime);
      if (input::KeyStates[input::Key::S])
         render::GlobalCamera.Move(Direction::Backward, turnSpeed * time::DeltaTime);
   }

   ground.Draw();
   cube.Draw();
   //pyramid.Draw();
}

void ResizeEvent()
{
   render::SetProjection(90.0f);
}

bool BeforeExitEvent()
{
   return false; // don't prevent exit
}

bool OnCommandEvent(const char *command, gui::Console *console)
{
   if (strcmp(command, "hello") == 0)
   {
      logging::Info("Hello, World!");
      return true;
   }
   return false;
}

int main()
{
   Init(800, 600);
   render::SetProjection(90.0f);

   render::texture::Texture img = mold::render::texture::LoadRGBBitmap("texture.bmp");

   input::LockCursor = true;

   gui::GlobalConsole.AddHelpCommand("hello");

   pyramid = render::objects::Pyramid({0, 5, 0}, {1.0f, 1.0f, 0.0f}, 2.0f, render::texture::UseTexture(img));
   cube = render::objects::Cube({0, 5, 0}, {1.0f, 1.0f, 0.0f}, 1.0f, render::texture::UseTexture(img));
   ground = render::objects::Plane({0, 5, 0}, {0.0f, 1.0f, 0.0f}, 3.0f, render::texture::UseTexture(img));
   render::GlobalCamera = render::objects::Camera({0.0f, 5.5f, 1.5f});

   render::GlobalCamera.MovementIgnoreRotationX = false;

   GlobalEventSystem.AttachCallback(EventType::Redraw, (void *)RedrawEvent);
   GlobalEventSystem.AttachCallback(EventType::Resize, (void *)ResizeEvent);
   GlobalEventSystem.AttachCallback(EventType::BeforeExit, (void *)BeforeExitEvent);
   GlobalEventSystem.AttachCallback(EventType::OnCommand, (void *)OnCommandEvent);

   Run();
   return 0;
}