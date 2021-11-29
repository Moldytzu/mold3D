#include <mold3D/3D.h>

#define CALL_EVENT(x) ((void (*)(void))GlobalEventSystem.GetMap()[x])()

mold::Clock _clock; //global clock used for delta time calculation
mold::gui::Profiler profilerWindow;

void stub() {}

void mold::core::Init(int width, int height)
{
    mold::gui::GlobalConsole = mold::gui::Console();

    mold::core::logging::Info("Starting mold3D");
    mold::core::logging::Info("Starting SDL subsystem");
    GlobalWindow = SDL_CreateWindow("mold3D", 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (GlobalWindow == NULL)
    {
        mold::core::logging::Error("Couldn't create a window!");
        exit(-1);
    }

    mold::core::logging::Info("Setting up the OpenGL subsystem");
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 128);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    GlobalGLContext = SDL_GL_CreateContext(GlobalWindow);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);

    mold::render::GlobalTextures = (mold::Byte *)malloc(0xFFFFFF); // 16 million textures should be enough
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(2, (GLuint *)render::GlobalTextures);

    mold::render::GlobalCamera = mold::render::objects::Camera({0, 0, 0});
    GlobalEventSystem = mold::core::EventSystem();

    mold::core::logging::Info("Setting up the ImGui subsystem");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.IniFilename = NULL;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(GlobalWindow, GlobalGLContext);
    ImGui_ImplOpenGL2_Init();

    mold::core::logging::Info("Setting up the event system");

    GlobalEventSystem.AttachCallback(Redraw, (void *)stub);
    GlobalEventSystem.AttachCallback(Resize, (void *)stub);
    GlobalEventSystem.AttachCallback(BeforeExit, (void *)stub);
    GlobalEventSystem.AttachCallback(OnCommand, (void *)stub);

    mold::core::logging::Info("Started the engine!");
    mold::core::input::KeyStates = new bool[512];
    memset(mold::core::input::KeyStates, 0, 512);
}

void mold::core::Init()
{
    Init(800, 600);
}

void mold::core::Run()
{
    mold::core::logging::Info("Starting the game");
    while (1)
    {
        _clock.tick();

        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            ImGui_ImplSDL2_ProcessEvent(&Event);
            if (Event.type == SDL_KEYDOWN)
            {
                mold::core::input::KeyStates[Event.key.keysym.scancode] = true;
            }
            else if (Event.type == SDL_KEYUP)
            {
                if (Event.key.keysym.scancode == (SDL_Scancode)mold::core::input::GRAVE)
                    mold::gui::GlobalConsole.Enabled = !mold::gui::GlobalConsole.Enabled;
                else if (Event.key.keysym.scancode == (SDL_Scancode)mold::core::input::INSERT)
                    profilerWindow.Enabled = !profilerWindow.Enabled;
                mold::core::input::KeyStates[Event.key.keysym.scancode] = false;
            }
            else if (Event.type == SDL_WINDOWEVENT)
            {
                if (Event.window.event == SDL_WINDOWEVENT_RESIZED)
                    CALL_EVENT(EventType::Resize);
            }
            else if (Event.type == SDL_QUIT)
                if (!((bool (*)(void))GlobalEventSystem.GetMap()[mold::core::EventType::BeforeExit])())
                    return;
        }

        if (_clock.delta > 0)
        {
            char windowTitle[1024];
            sprintf(windowTitle, "mold3D : %d FPS", (int)(1.0f / _clock.delta));

            SDL_SetWindowTitle(GlobalWindow, windowTitle);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            mold::render::GlobalCamera.Draw();

            ImGui_ImplOpenGL2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            CALL_EVENT(EventType::Redraw);
            mold::gui::GlobalConsole.Draw();
            profilerWindow.Draw();

            ImGui::Render();
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

            glFlush();

            SDL_GL_SwapWindow(GlobalWindow);
        }

        //handle GL errors
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
            printf("OPENGL ERROR %u\n", error);

        mold::core::time::DeltaTime = _clock.delta;
        mold::core::time::FPS = (int)(1.0f / _clock.delta);
        if (mold::core::input::LockCursor == true && !mold::gui::GlobalConsole.Enabled)
        {
            SDL_SetRelativeMouseMode(SDL_TRUE);
            SDL_SetWindowGrab(GlobalWindow, SDL_TRUE);
            SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
        }
        else
        {
            SDL_SetRelativeMouseMode(SDL_FALSE);
            SDL_SetWindowGrab(GlobalWindow, SDL_FALSE);
            SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
        }
    }
}