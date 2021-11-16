#include <mold3D/3D.h>

#define CALL_EVENT(x) ((void (*)(void))events->GetMap()[x])()

SDL_Window *Window;
SDL_GLContext Context;
mold::render::objects::Camera *userCam; //user camera
mold::core::EventSystem *events;        //event system
bool *keys;                             //keys pressed
mold::Clock clock;                      //global clock used for delta time calculation

void stub() {}

void mold::core::Init(mold::render::objects::Camera *camera, EventSystem *eventSystem, int width, int height)
{
    mold::core::logging::Info("Starting mold3D");
    mold::core::logging::Info("Starting SDL subsystem");
    Window = SDL_CreateWindow("mold3D", 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (Window == NULL)
    {
        mold::core::logging::Error("Couldn't create a window!");
        exit(-1);
    }

    mold::core::logging::Info("Setting up the OpenGL subsystem");
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 128);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    Context = SDL_GL_CreateContext(Window);

    glEnable(GL_DEPTH_TEST);
    SDL_GL_SetSwapInterval(0);

    userCam = camera;
    events = eventSystem;

    mold::core::logging::Info("Setting up the ImGui subsystem");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(mold::core::GetWindow(), mold::core::GetGLContext());
    ImGui_ImplOpenGL2_Init();

    mold::core::logging::Info("Setting up the event system");

    eventSystem->AttachCallback(Redraw, (void *)stub);
    eventSystem->AttachCallback(Resize, (void *)stub);
    eventSystem->AttachCallback(BeforeExit, (void *)stub);

    mold::core::logging::Info("Started the engine!");
    keys = new bool[1073742000];
}

void mold::core::Init(mold::render::objects::Camera *camera, EventSystem *eventSystem)
{
    Init(camera, eventSystem, 800, 600);
}

void mold::core::Run()
{
    mold::core::logging::Info("Starting the game");
    while (1)
    {
        clock.tick();

        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            ImGui_ImplSDL2_ProcessEvent(&Event);
            if (Event.type == SDL_KEYDOWN)
            {
                keys[Event.key.keysym.sym] = true;
            }
            else if (Event.type == SDL_KEYUP)
            {
                keys[Event.key.keysym.sym] = false;
            }
            else if (Event.type == SDL_WINDOWEVENT)
            {
                if (Event.window.event == SDL_WINDOWEVENT_RESIZED)
                    CALL_EVENT(EventType::Resize);
            }
            else if (Event.type == SDL_QUIT)
                if (!((bool (*)(void))events->GetMap()[mold::core::EventType::BeforeExit])())
                    return;
        }

        if (clock.delta > 0)
        {
            char windowTitle[1024];
            sprintf(windowTitle, "mold3D : %d FPS", (int)(1.0f / clock.delta));

            SDL_SetWindowTitle(Window, windowTitle);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            userCam->Draw();

            ImGui_ImplOpenGL2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            CALL_EVENT(EventType::Redraw);

            ImGui::Render();
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

            glFlush();

            SDL_GL_SwapWindow(Window);
        }
    }
}

bool *mold::core::input::GetKeyStates()
{
    return keys;
}

float mold::core::time::GetDeltaTime()
{
    return clock.delta;
}

SDL_Window *mold::core::GetWindow()
{
    return Window;
}

SDL_GLContext mold::core::GetGLContext()
{
    return Context;
}