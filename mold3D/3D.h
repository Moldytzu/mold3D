#pragma once
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl.h>
#include <math.h>
#include <map>
#include <algorithm>
#include <chrono>

namespace mold
{
    typedef GLfloat Float3D;

    enum Direction
    {
        Forward,
        Backward,
        Left,
        Right,
    };

    struct Point3D
    {
        Float3D X, Y, Z;
    };

    struct RGB
    {
        Float3D R, G, B;
    };

    struct Clock
    {
        uint32_t last_tick_time = 0;
        float delta = 0;

        void tick()
        {
            uint32_t tick_time = SDL_GetTicks();
            delta = (tick_time - last_tick_time) / 1000.0f;
            last_tick_time = tick_time;
        }
    };

    namespace profiler
    {
        void TrackAllocMemory(size_t bytes);
        void TrackFreeMemory(size_t bytes);
        size_t GetTrackedMemory();
    };

    namespace render
    {
        namespace objects
        {
            class GameObject
            {
            public:
                GameObject();
                GameObject(Point3D point, RGB color, Float3D Size);
                void Draw();
                Point3D coords;
                RGB color;
                Float3D Size;
            };

            class Pyramid : public GameObject
            {
            public:
                Pyramid();
                Pyramid(Point3D point, RGB color, Float3D Size);
                virtual void Draw();
            };

            class Cube : public GameObject
            {
            public:
                Cube();
                Cube(Point3D point, RGB color, Float3D Size);
                virtual void Draw();
            };

            class Plane : public GameObject
            {
            public:
                Plane();
                Plane(Point3D point, RGB color, Float3D Size);
                virtual void Draw();
            };

            class Camera : public GameObject
            {
            public:
                Camera();
                Camera(Point3D point);
                virtual void Draw();
                void Move(Direction direction, Float3D value);
                void Rotate(Direction direction, Float3D value);
                Float3D AngleZ = -1.0f, AngleX = 0, AngleY = 0, Angle = 0, Angle2 = 0;
            };
        };

        void SetProjection(Float3D fov);
    };

    namespace core
    {
        namespace input
        {
            bool *GetKeyStates();
        };

        namespace time
        {
            float GetDeltaTime();
        };

        namespace logging
        {
            void Info(const char *text);
            void Warn(const char *text);
            void Error(const char *text);
        };

        enum EventType
        {
            Redraw = 1,
            Resize = 2,
            BeforeExit = 3,
        };

        class EventSystem
        {
        public:
            void AttachCallback(EventType type, void *callback);
            void DetachCallback(EventType type);
            std::map<EventType, void *> GetMap();

        private:
            std::map<EventType, void *> events; //type, callback
        };

        void Init(mold::render::objects::Camera *camera, EventSystem *eventSystem);
        void Init(mold::render::objects::Camera *camera, EventSystem *eventSystem, int width, int height);
        void Run();

        SDL_Window *GetWindow();
        SDL_GLContext GetGLContext();
    };

    namespace gui
    {
        class Console
        {
        public:
            char InputBuf[512];
            ImVector<char *> Items;
            ImVector<const char *> Commands;
            ImVector<char *> History;
            int HistoryPos;
            bool AutoScroll;
            bool ScrollToBottom;
            bool Enabled;
            Console();
            ~Console();
            void ClearLog();
            void AddLog(const char *fmt, ...) IM_FMTARGS(2);
            void Draw();
            void ExecCommand(const char *command_line);
            int TextEditCallback(ImGuiInputTextCallbackData *data);
        };

        Console *GetConsole();
    };

    namespace core
    {
        namespace input
        {
//wraps the sdl keys into more nice names
#define SCAN_TO_CODE(X) (X | SDLK_SCANCODE_MASK)

            typedef enum
            {
                _UNKNOWN = 0,

                _RETURN = '\r',
                _ESCAPE = '\033',
                _BACKSPACE = '\b',
                _TAB = '\t',
                _SPACE = ' ',
                _EXCLAIM = '!',
                _QUOTEDBL = '"',
                _HASH = '#',
                _PERCENT = '%',
                _DOLLAR = '$',
                _AMPERSAND = '&',
                _QUOTE = '\'',
                _LEFTPAREN = '(',
                _RIGHTPAREN = ')',
                _ASTERISK = '*',
                _PLUS = '+',
                _COMMA = ',',
                _MINUS = '-',
                _PERIOD = '.',
                _SLASH = '/',
                _0 = '0',
                _1 = '1',
                _2 = '2',
                _3 = '3',
                _4 = '4',
                _5 = '5',
                _6 = '6',
                _7 = '7',
                _8 = '8',
                _9 = '9',
                _COLON = ':',
                _SEMICOLON = ';',
                _LESS = '<',
                _EQUALS = '=',
                _GREATER = '>',
                _QUESTION = '?',
                _AT = '@',

                _LEFTBRACKET = '[',
                _BACKSLASH = '\\',
                _RIGHTBRACKET = ']',
                _CARET = '^',
                _UNDERSCORE = '_',
                _BACKQUOTE = '`',
                _a = 'a',
                _b = 'b',
                _c = 'c',
                _d = 'd',
                _e = 'e',
                _f = 'f',
                _g = 'g',
                _h = 'h',
                _i = 'i',
                _j = 'j',
                _k = 'k',
                _l = 'l',
                _m = 'm',
                _n = 'n',
                _o = 'o',
                _p = 'p',
                _q = 'q',
                _r = 'r',
                _s = 's',
                _t = 't',
                _u = 'u',
                _v = 'v',
                _w = 'w',
                _x = 'x',
                _y = 'y',
                _z = 'z',

                _CAPSLOCK = SCAN_TO_CODE(SDL_SCANCODE_CAPSLOCK),

                _F1 = SCAN_TO_CODE(SDL_SCANCODE_F1),
                _F2 = SCAN_TO_CODE(SDL_SCANCODE_F2),
                _F3 = SCAN_TO_CODE(SDL_SCANCODE_F3),
                _F4 = SCAN_TO_CODE(SDL_SCANCODE_F4),
                _F5 = SCAN_TO_CODE(SDL_SCANCODE_F5),
                _F6 = SCAN_TO_CODE(SDL_SCANCODE_F6),
                _F7 = SCAN_TO_CODE(SDL_SCANCODE_F7),
                _F8 = SCAN_TO_CODE(SDL_SCANCODE_F8),
                _F9 = SCAN_TO_CODE(SDL_SCANCODE_F9),
                _F10 = SCAN_TO_CODE(SDL_SCANCODE_F10),
                _F11 = SCAN_TO_CODE(SDL_SCANCODE_F11),
                _F12 = SCAN_TO_CODE(SDL_SCANCODE_F12),

                _PRINTSCREEN = SCAN_TO_CODE(SDL_SCANCODE_PRINTSCREEN),
                _SCROLLLOCK = SCAN_TO_CODE(SDL_SCANCODE_SCROLLLOCK),
                _PAUSE = SCAN_TO_CODE(SDL_SCANCODE_PAUSE),
                _INSERT = SCAN_TO_CODE(SDL_SCANCODE_INSERT),
                _HOME = SCAN_TO_CODE(SDL_SCANCODE_HOME),
                _PAGEUP = SCAN_TO_CODE(SDL_SCANCODE_PAGEUP),
                _DELETE = '\177',
                _END = SCAN_TO_CODE(SDL_SCANCODE_END),
                _PAGEDOWN = SCAN_TO_CODE(SDL_SCANCODE_PAGEDOWN),
                _RIGHT = SCAN_TO_CODE(SDL_SCANCODE_RIGHT),
                _LEFT = SCAN_TO_CODE(SDL_SCANCODE_LEFT),
                _DOWN = SCAN_TO_CODE(SDL_SCANCODE_DOWN),
                _UP = SCAN_TO_CODE(SDL_SCANCODE_UP),

                _NUMLOCKCLEAR = SCAN_TO_CODE(SDL_SCANCODE_NUMLOCKCLEAR),
                _KP_DIVIDE = SCAN_TO_CODE(SDL_SCANCODE_KP_DIVIDE),
                _KP_MULTIPLY = SCAN_TO_CODE(SDL_SCANCODE_KP_MULTIPLY),
                _KP_MINUS = SCAN_TO_CODE(SDL_SCANCODE_KP_MINUS),
                _KP_PLUS = SCAN_TO_CODE(SDL_SCANCODE_KP_PLUS),
                _KP_ENTER = SCAN_TO_CODE(SDL_SCANCODE_KP_ENTER),
                _KP_1 = SCAN_TO_CODE(SDL_SCANCODE_KP_1),
                _KP_2 = SCAN_TO_CODE(SDL_SCANCODE_KP_2),
                _KP_3 = SCAN_TO_CODE(SDL_SCANCODE_KP_3),
                _KP_4 = SCAN_TO_CODE(SDL_SCANCODE_KP_4),
                _KP_5 = SCAN_TO_CODE(SDL_SCANCODE_KP_5),
                _KP_6 = SCAN_TO_CODE(SDL_SCANCODE_KP_6),
                _KP_7 = SCAN_TO_CODE(SDL_SCANCODE_KP_7),
                _KP_8 = SCAN_TO_CODE(SDL_SCANCODE_KP_8),
                _KP_9 = SCAN_TO_CODE(SDL_SCANCODE_KP_9),
                _KP_0 = SCAN_TO_CODE(SDL_SCANCODE_KP_0),
                _KP_PERIOD = SCAN_TO_CODE(SDL_SCANCODE_KP_PERIOD),

                _APPLICATION = SCAN_TO_CODE(SDL_SCANCODE_APPLICATION),
                _POWER = SCAN_TO_CODE(SDL_SCANCODE_POWER),
                _KP_EQUALS = SCAN_TO_CODE(SDL_SCANCODE_KP_EQUALS),
                _F13 = SCAN_TO_CODE(SDL_SCANCODE_F13),
                _F14 = SCAN_TO_CODE(SDL_SCANCODE_F14),
                _F15 = SCAN_TO_CODE(SDL_SCANCODE_F15),
                _F16 = SCAN_TO_CODE(SDL_SCANCODE_F16),
                _F17 = SCAN_TO_CODE(SDL_SCANCODE_F17),
                _F18 = SCAN_TO_CODE(SDL_SCANCODE_F18),
                _F19 = SCAN_TO_CODE(SDL_SCANCODE_F19),
                _F20 = SCAN_TO_CODE(SDL_SCANCODE_F20),
                _F21 = SCAN_TO_CODE(SDL_SCANCODE_F21),
                _F22 = SCAN_TO_CODE(SDL_SCANCODE_F22),
                _F23 = SCAN_TO_CODE(SDL_SCANCODE_F23),
                _F24 = SCAN_TO_CODE(SDL_SCANCODE_F24),
                _EXECUTE = SCAN_TO_CODE(SDL_SCANCODE_EXECUTE),
                _HELP = SCAN_TO_CODE(SDL_SCANCODE_HELP),
                _MENU = SCAN_TO_CODE(SDL_SCANCODE_MENU),
                _SELECT = SCAN_TO_CODE(SDL_SCANCODE_SELECT),
                _STOP = SCAN_TO_CODE(SDL_SCANCODE_STOP),
                _AGAIN = SCAN_TO_CODE(SDL_SCANCODE_AGAIN),
                _UNDO = SCAN_TO_CODE(SDL_SCANCODE_UNDO),
                _CUT = SCAN_TO_CODE(SDL_SCANCODE_CUT),
                _COPY = SCAN_TO_CODE(SDL_SCANCODE_COPY),
                _PASTE = SCAN_TO_CODE(SDL_SCANCODE_PASTE),
                _FIND = SCAN_TO_CODE(SDL_SCANCODE_FIND),
                _MUTE = SCAN_TO_CODE(SDL_SCANCODE_MUTE),
                _VOLUMEUP = SCAN_TO_CODE(SDL_SCANCODE_VOLUMEUP),
                _VOLUMEDOWN = SCAN_TO_CODE(SDL_SCANCODE_VOLUMEDOWN),
                _KP_COMMA = SCAN_TO_CODE(SDL_SCANCODE_KP_COMMA),
                _KP_EQUALSAS400 =
                    SCAN_TO_CODE(SDL_SCANCODE_KP_EQUALSAS400),

                _ALTERASE = SCAN_TO_CODE(SDL_SCANCODE_ALTERASE),
                _SYSREQ = SCAN_TO_CODE(SDL_SCANCODE_SYSREQ),
                _CANCEL = SCAN_TO_CODE(SDL_SCANCODE_CANCEL),
                _CLEAR = SCAN_TO_CODE(SDL_SCANCODE_CLEAR),
                _PRIOR = SCAN_TO_CODE(SDL_SCANCODE_PRIOR),
                _RETURN2 = SCAN_TO_CODE(SDL_SCANCODE_RETURN2),
                _SEPARATOR = SCAN_TO_CODE(SDL_SCANCODE_SEPARATOR),
                _OUT = SCAN_TO_CODE(SDL_SCANCODE_OUT),
                _OPER = SCAN_TO_CODE(SDL_SCANCODE_OPER),
                _CLEARAGAIN = SCAN_TO_CODE(SDL_SCANCODE_CLEARAGAIN),
                _CRSEL = SCAN_TO_CODE(SDL_SCANCODE_CRSEL),
                _EXSEL = SCAN_TO_CODE(SDL_SCANCODE_EXSEL),

                _KP_00 = SCAN_TO_CODE(SDL_SCANCODE_KP_00),
                _KP_000 = SCAN_TO_CODE(SDL_SCANCODE_KP_000),
                _THOUSANDSSEPARATOR =
                    SCAN_TO_CODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
                _DECIMALSEPARATOR =
                    SCAN_TO_CODE(SDL_SCANCODE_DECIMALSEPARATOR),
                _CURRENCYUNIT = SCAN_TO_CODE(SDL_SCANCODE_CURRENCYUNIT),
                _CURRENCYSUBUNIT =
                    SCAN_TO_CODE(SDL_SCANCODE_CURRENCYSUBUNIT),
                _KP_LEFTPAREN = SCAN_TO_CODE(SDL_SCANCODE_KP_LEFTPAREN),
                _KP_RIGHTPAREN = SCAN_TO_CODE(SDL_SCANCODE_KP_RIGHTPAREN),
                _KP_LEFTBRACE = SCAN_TO_CODE(SDL_SCANCODE_KP_LEFTBRACE),
                _KP_RIGHTBRACE = SCAN_TO_CODE(SDL_SCANCODE_KP_RIGHTBRACE),
                _KP_TAB = SCAN_TO_CODE(SDL_SCANCODE_KP_TAB),
                _KP_BACKSPACE = SCAN_TO_CODE(SDL_SCANCODE_KP_BACKSPACE),
                _KP_A = SCAN_TO_CODE(SDL_SCANCODE_KP_A),
                _KP_B = SCAN_TO_CODE(SDL_SCANCODE_KP_B),
                _KP_C = SCAN_TO_CODE(SDL_SCANCODE_KP_C),
                _KP_D = SCAN_TO_CODE(SDL_SCANCODE_KP_D),
                _KP_E = SCAN_TO_CODE(SDL_SCANCODE_KP_E),
                _KP_F = SCAN_TO_CODE(SDL_SCANCODE_KP_F),
                _KP_XOR = SCAN_TO_CODE(SDL_SCANCODE_KP_XOR),
                _KP_POWER = SCAN_TO_CODE(SDL_SCANCODE_KP_POWER),
                _KP_PERCENT = SCAN_TO_CODE(SDL_SCANCODE_KP_PERCENT),
                _KP_LESS = SCAN_TO_CODE(SDL_SCANCODE_KP_LESS),
                _KP_GREATER = SCAN_TO_CODE(SDL_SCANCODE_KP_GREATER),
                _KP_AMPERSAND = SCAN_TO_CODE(SDL_SCANCODE_KP_AMPERSAND),
                _KP_DBLAMPERSAND =
                    SCAN_TO_CODE(SDL_SCANCODE_KP_DBLAMPERSAND),
                _KP_VERTICALBAR =
                    SCAN_TO_CODE(SDL_SCANCODE_KP_VERTICALBAR),
                _KP_DBLVERTICALBAR =
                    SCAN_TO_CODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
                _KP_COLON = SCAN_TO_CODE(SDL_SCANCODE_KP_COLON),
                _KP_HASH = SCAN_TO_CODE(SDL_SCANCODE_KP_HASH),
                _KP_SPACE = SCAN_TO_CODE(SDL_SCANCODE_KP_SPACE),
                _KP_AT = SCAN_TO_CODE(SDL_SCANCODE_KP_AT),
                _KP_EXCLAM = SCAN_TO_CODE(SDL_SCANCODE_KP_EXCLAM),
                _KP_MEMSTORE = SCAN_TO_CODE(SDL_SCANCODE_KP_MEMSTORE),
                _KP_MEMRECALL = SCAN_TO_CODE(SDL_SCANCODE_KP_MEMRECALL),
                _KP_MEMCLEAR = SCAN_TO_CODE(SDL_SCANCODE_KP_MEMCLEAR),
                _KP_MEMADD = SCAN_TO_CODE(SDL_SCANCODE_KP_MEMADD),
                _KP_MEMSUBTRACT =
                    SCAN_TO_CODE(SDL_SCANCODE_KP_MEMSUBTRACT),
                _KP_MEMMULTIPLY =
                    SCAN_TO_CODE(SDL_SCANCODE_KP_MEMMULTIPLY),
                _KP_MEMDIVIDE = SCAN_TO_CODE(SDL_SCANCODE_KP_MEMDIVIDE),
                _KP_PLUSMINUS = SCAN_TO_CODE(SDL_SCANCODE_KP_PLUSMINUS),
                _KP_CLEAR = SCAN_TO_CODE(SDL_SCANCODE_KP_CLEAR),
                _KP_CLEARENTRY = SCAN_TO_CODE(SDL_SCANCODE_KP_CLEARENTRY),
                _KP_BINARY = SCAN_TO_CODE(SDL_SCANCODE_KP_BINARY),
                _KP_OCTAL = SCAN_TO_CODE(SDL_SCANCODE_KP_OCTAL),
                _KP_DECIMAL = SCAN_TO_CODE(SDL_SCANCODE_KP_DECIMAL),
                _KP_HEXADECIMAL =
                    SCAN_TO_CODE(SDL_SCANCODE_KP_HEXADECIMAL),

                _LCTRL = SCAN_TO_CODE(SDL_SCANCODE_LCTRL),
                _LSHIFT = SCAN_TO_CODE(SDL_SCANCODE_LSHIFT),
                _LALT = SCAN_TO_CODE(SDL_SCANCODE_LALT),
                _LGUI = SCAN_TO_CODE(SDL_SCANCODE_LGUI),
                _RCTRL = SCAN_TO_CODE(SDL_SCANCODE_RCTRL),
                _RSHIFT = SCAN_TO_CODE(SDL_SCANCODE_RSHIFT),
                _RALT = SCAN_TO_CODE(SDL_SCANCODE_RALT),
                _RGUI = SCAN_TO_CODE(SDL_SCANCODE_RGUI),

                _MODE = SCAN_TO_CODE(SDL_SCANCODE_MODE),

                _AUDIONEXT = SCAN_TO_CODE(SDL_SCANCODE_AUDIONEXT),
                _AUDIOPREV = SCAN_TO_CODE(SDL_SCANCODE_AUDIOPREV),
                _AUDIOSTOP = SCAN_TO_CODE(SDL_SCANCODE_AUDIOSTOP),
                _AUDIOPLAY = SCAN_TO_CODE(SDL_SCANCODE_AUDIOPLAY),
                _AUDIOMUTE = SCAN_TO_CODE(SDL_SCANCODE_AUDIOMUTE),
                _MEDIASELECT = SCAN_TO_CODE(SDL_SCANCODE_MEDIASELECT),
                _WWW = SCAN_TO_CODE(SDL_SCANCODE_WWW),
                _MAIL = SCAN_TO_CODE(SDL_SCANCODE_MAIL),
                _CALCULATOR = SCAN_TO_CODE(SDL_SCANCODE_CALCULATOR),
                _COMPUTER = SCAN_TO_CODE(SDL_SCANCODE_COMPUTER),
                _AC_SEARCH = SCAN_TO_CODE(SDL_SCANCODE_AC_SEARCH),
                _AC_HOME = SCAN_TO_CODE(SDL_SCANCODE_AC_HOME),
                _AC_BACK = SCAN_TO_CODE(SDL_SCANCODE_AC_BACK),
                _AC_FORWARD = SCAN_TO_CODE(SDL_SCANCODE_AC_FORWARD),
                _AC_STOP = SCAN_TO_CODE(SDL_SCANCODE_AC_STOP),
                _AC_REFRESH = SCAN_TO_CODE(SDL_SCANCODE_AC_REFRESH),
                _AC_BOOKMARKS = SCAN_TO_CODE(SDL_SCANCODE_AC_BOOKMARKS),

                _BRIGHTNESSDOWN =
                    SCAN_TO_CODE(SDL_SCANCODE_BRIGHTNESSDOWN),
                _BRIGHTNESSUP = SCAN_TO_CODE(SDL_SCANCODE_BRIGHTNESSUP),
                _DISPLAYSWITCH = SCAN_TO_CODE(SDL_SCANCODE_DISPLAYSWITCH),
                _KBDILLUMTOGGLE =
                    SCAN_TO_CODE(SDL_SCANCODE_KBDILLUMTOGGLE),
                _KBDILLUMDOWN = SCAN_TO_CODE(SDL_SCANCODE_KBDILLUMDOWN),
                _KBDILLUMUP = SCAN_TO_CODE(SDL_SCANCODE_KBDILLUMUP),
                _EJECT = SCAN_TO_CODE(SDL_SCANCODE_EJECT),
                _SLEEP = SCAN_TO_CODE(SDL_SCANCODE_SLEEP),
                _APP1 = SCAN_TO_CODE(SDL_SCANCODE_APP1),
                _APP2 = SCAN_TO_CODE(SDL_SCANCODE_APP2),

                _AUDIOREWIND = SCAN_TO_CODE(SDL_SCANCODE_AUDIOREWIND),
                _AUDIOFASTFORWARD = SCAN_TO_CODE(SDL_SCANCODE_AUDIOFASTFORWARD)
            } Key;

        };
    };

};
