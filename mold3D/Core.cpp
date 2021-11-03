#include <mold3D/3D.h>

SDL_Window *Window;
mold::render::objects::Camera *userCam; //user camera
void (*userDraw)();             //user redraw function
bool keys[0xFFFF];              //keys pressed
mold::Clock clock;              //global clock used for delta time calculation

void mold::core::Init(mold::render::objects::Camera *camera, void (*draw)(), int width, int height)
{
    Window = SDL_CreateWindow("mold3D", 0, 0, width, height, SDL_WINDOW_OPENGL);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 128);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GLContext Context = SDL_GL_CreateContext(Window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(75.0f, width * 1.0 / height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    SDL_GL_SetSwapInterval(0);

    //user things
    userCam = camera;
    userDraw = draw;
}

void mold::core::Init(mold::render::objects::Camera *camera, void (*draw)())
{
    Init(camera, draw, 800, 600);
}

void mold::core::Run()
{
    while (1)
    {
        clock.tick();

        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_KEYDOWN)
            {
                if (Event.key.keysym.sym < 0xFFFF)
                    keys[Event.key.keysym.sym] = true;
            }
            else if (Event.type == SDL_KEYUP)
            {
                if (Event.key.keysym.sym < 0xFFFF)
                    keys[Event.key.keysym.sym] = false;
            }
            else if (Event.type == SDL_QUIT)
                return;
        }

        if((int)(1.0f / clock.delta) < 0) {
            SDL_Delay(0);
            continue;
        }

        char windowTitle[1024];
        sprintf(windowTitle,"mold3D : %d FPS", (int)(1.0f / clock.delta));

        SDL_SetWindowTitle(Window,windowTitle);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        userCam->Draw();

        userDraw();

        glFlush();

        SDL_GL_SwapWindow(Window);
    }
}

bool* mold::core::input::GetKeyStates() {
    return keys;
}

float mold::core::time::GetDeltaTime() {
    return clock.delta;
}