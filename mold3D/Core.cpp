#include <mold3D/3D.h>

SDL_Window *Window;
mold::objects::Camera *userCam; //user camera
void (*userDraw)();             //user redraw function
bool keys[0xFFFF];              //keys pressed

void mold::core::Init(objects::Camera *camera, void (*draw)(), int width, int height)
{

   Window = SDL_CreateWindow("mold3D", 0, 0, width, height, SDL_WINDOW_OPENGL);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 128);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   SDL_GLContext Context = SDL_GL_CreateContext(Window);

    //user things
    userCam = camera;
    userDraw = draw;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(75.0f, width * 1.0 / height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
}

void mold::core::Init(objects::Camera *camera, void (*draw)())
{
    Init(camera, draw, 800, 600);
}

void mold::core::Run()
{
   bool Running = 1;
   while (Running)
   {
      SDL_Event Event;
      while (SDL_PollEvent(&Event))
      {
         if (Event.type == SDL_KEYDOWN)
         {
            if (Event.key.keysym.sym < 0xFFFF)
               keys[Event.key.keysym.sym] = true;
         }
         else if (Event.type == SDL_QUIT)
         {
            Running = 0;
         }
         else if (Event.type == SDL_KEYUP)
            if (Event.key.keysym.sym < 0xFFFF)
               keys[Event.key.keysym.sym] = false;
      }

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      userCam->Update(keys);
      userCam->Draw();

    userDraw();

      SDL_GL_SwapWindow(Window);
   }
    //glutMainLoop(); // do the main loop
}