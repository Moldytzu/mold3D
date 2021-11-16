#include "mold3D/3D.h"
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl.h>

mold::render::objects::Pyramid pyramid;
mold::render::objects::Cube cube;
mold::render::objects::Camera camera;
mold::render::objects::Plane ground;

mold::core::EventSystem eventSystem;

float turnSpeed = 1.5f;
float moveSpeed = 3.0f;

void Redraw()
{
   ImGui_ImplOpenGL2_NewFrame();
   ImGui_ImplSDL2_NewFrame();
   ImGui::NewFrame();

   ImGui::ShowDemoWindow();

   bool *keys = mold::core::input::GetKeyStates();
   float delta = mold::core::time::GetDeltaTime();

   if (keys[SDL_KeyCode::SDLK_RIGHT] || keys['D'] || keys['d'])
      camera.Rotate(mold::Direction::Right, turnSpeed * delta);

   if (keys[SDL_KeyCode::SDLK_LEFT] || keys['a'] || keys['A'])
      camera.Rotate(mold::Direction::Left, turnSpeed * delta);

   if (keys[SDL_KeyCode::SDLK_UP] || keys['w'] || keys['W'])
      camera.Rotate(mold::Direction::Forward, turnSpeed * delta);

   if (keys[SDL_KeyCode::SDLK_DOWN] || keys['s'] || keys['S'])
      camera.Rotate(mold::Direction::Backward, turnSpeed * delta);

   cube.Draw();
   pyramid.Draw();
   ground.Draw();

   ImGui::Render();
   ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void Resize()
{
   mold::render::SetProjection(90.0f);
}

bool BeforeExit()
{
   return false; // don't prevent exit
}

int main()
{
   mold::core::Init(&camera, &eventSystem, 800, 600);
   mold::render::SetProjection(90.0f);

   // Setup Dear ImGui context
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO &io = ImGui::GetIO();
   (void)io;
   //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
   //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

   // Setup Dear ImGui style
   //ImGui::StyleColorsDark();
   ImGui::StyleColorsClassic();

   // Setup Platform/Renderer backends
   ImGui_ImplSDL2_InitForOpenGL(mold::core::GetWindow(), mold::core::GetGLContext());
   ImGui_ImplOpenGL2_Init();

   pyramid = mold::render::objects::Pyramid({0, 0, 0}, {5.0f, 1.0f, 0}, 1.0f);
   cube = mold::render::objects::Cube({0, 0, 0}, {1.0f, 1.0f, 1.0f}, 1.0f);
   ground = mold::render::objects::Plane({0, 0, 0}, {0.0f, 1.0f, 0.0f}, 3.0f);

   camera = mold::render::objects::Camera({0.0f, 1.0f, 1.5f});

   eventSystem.AttachCallback(mold::core::EventType::Redraw, (void *)Redraw);
   eventSystem.AttachCallback(mold::core::EventType::Resize, (void *)Resize);
   eventSystem.AttachCallback(mold::core::EventType::BeforeExit, (void *)BeforeExit);

   bool show_demo_window = true;
   bool show_another_window = false;
   ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

   mold::core::Run();
   return 0;
}