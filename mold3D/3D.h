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
    typedef unsigned char Byte;
    typedef const char *Text;

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
                GameObject(Point3D point, RGB color, Float3D Size, uint32_t TextureIndex);
                void Draw();
                Point3D coords;
                RGB color;
                Float3D Size;
                uint32_t TextureIndex;
            };

            class Pyramid : public GameObject
            {
            public:
                Pyramid();
                Pyramid(Point3D point, RGB color, Float3D Size, uint32_t TextureIndex);
                virtual void Draw();
            };

            class Cube : public GameObject
            {
            public:
                Cube();
                Cube(Point3D point, RGB color, Float3D Size, uint32_t TextureIndex);
                virtual void Draw();
            };

            class Plane : public GameObject
            {
            public:
                Plane();
                Plane(Point3D point, RGB color, Float3D Size, uint32_t TextureIndex);
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

        namespace texture
        {
            struct Texture
            {
                uint32_t Size;
                uint32_t Width;
                uint32_t Height;

                Byte* PixelData;
            };

            struct BitmapImageHeader //https://en.wikipedia.org/wiki/BMP_file_format
            {
                //bmp header
                Byte Signature1; //Should be B
                Byte Signature2; //Should be M

                uint32_t Size; //bmp file size

                uint32_t Reserved;

                uint32_t DataOffset; //offset to the image data

                //BITMAPINFOHEADER
                uint32_t HeaderSize; //size of BITMAPINFOHEADER, always 0x28 (decimal 40)
                int32_t BitmapWidth; //width of the image
                int32_t BitmapHeight; //height of the image
                uint16_t Planes; //bit planes 
                uint16_t BPP; //bits per pixel
                uint32_t CompressionMethod; //the method of compression used
                uint32_t ImageSize; //size in bytes of the whole image, without headers
                int32_t HorizontalResolution; //resolution in pixel per metre
                int32_t VerticalResolution; //resolution in pixel per metre
                uint32_t Colors; //colors in the color palette
                uint32_t ImportantColors; //important colors used, generally ignored
            } __attribute__((packed));

            Texture LoadRGBBitmap(Text filename);

            uint32_t UseTexture(Texture texture);
        };

        void SetProjection(Float3D fov);

        inline objects::Camera GlobalCamera;
        inline Byte *GlobalTextures;
        inline uint32_t LastTextureIndex = 1;
    };

    namespace core
    {
        namespace input
        {
            inline bool *KeyStates;

            inline bool LockCursor = false;
        };

        namespace time
        {
            inline float DeltaTime = 0;
            inline int FPS = 0;
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
            OnCommand = 4,
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

        void Init();
        void Init(int width, int height);
        void Run();

        inline EventSystem GlobalEventSystem;
        inline SDL_GLContext GlobalGLContext;
        inline SDL_Window *GlobalWindow;

    };

    namespace gui
    {
        class Console
        {
        public:
            char InputBuf[512];
            std::vector<char *> Items;
            std::vector<const char *> Commands;
            std::vector<char *> History;
            std::map<const char *, void *> UserCommands;
            int HistoryPos;
            bool AutoScroll;
            bool ScrollToBottom;
            bool Enabled = false;
            Console();
            ~Console();
            void ClearLog();
            void AddLog(const char *fmt, ...) IM_FMTARGS(2);
            void AddHelpCommand(const char *command);
            void Draw();
            void ExecCommand(const char *command_line);
            int TextEditCallback(ImGuiInputTextCallbackData *data);
        };

        class Profiler
        {
        public:
            bool Enabled = false;
            void Draw();
        };

        inline Console GlobalConsole;
    };

    namespace core
    {
        namespace input
        {
            //wraps the sdl keys into more nice names
            typedef enum
            {
                UNKNOWN = 0,
                A = 4,
                B = 5,
                C = 6,
                D = 7,
                E = 8,
                F = 9,
                G = 10,
                H = 11,
                I = 12,
                J = 13,
                K = 14,
                L = 15,
                M = 16,
                N = 17,
                O = 18,
                P = 19,
                Q = 20,
                R = 21,
                S = 22,
                T = 23,
                U = 24,
                V = 25,
                W = 26,
                X = 27,
                Y = 28,
                Z = 29,
                _1 = 30,
                _2 = 31,
                _3 = 32,
                _4 = 33,
                _5 = 34,
                _6 = 35,
                _7 = 36,
                _8 = 37,
                _9 = 38,
                _0 = 39,
                RETURN = 40,
                ESCAPE = 41,
                BACKSPACE = 42,
                TAB = 43,
                SPACE = 44,
                MINUS = 45,
                EQUALS = 46,
                LEFTBRACKET = 47,
                RIGHTBRACKET = 48,
                BACKSLASH = 49,
                NONUSHASH = 50,
                SEMICOLON = 51,
                APOSTROPHE = 52,
                GRAVE = 53,
                COMMA = 54,
                PERIOD = 55,
                SLASH = 56,
                CAPSLOCK = 57,
                F1 = 58,
                F2 = 59,
                F3 = 60,
                F4 = 61,
                F5 = 62,
                F6 = 63,
                F7 = 64,
                F8 = 65,
                F9 = 66,
                F10 = 67,
                F11 = 68,
                F12 = 69,
                PRINTSCREEN = 70,
                SCROLLLOCK = 71,
                PAUSE = 72,
                INSERT = 73,
                HOME = 74,
                PAGEUP = 75,
                DELETE = 76,
                END = 77,
                PAGEDOWN = 78,
                RIGHT = 79,
                LEFT = 80,
                DOWN = 81,
                UP = 82,
                NUMLOCKCLEAR = 83,
                KP_DIVIDE = 84,
                KP_MULTIPLY = 85,
                KP_MINUS = 86,
                KP_PLUS = 87,
                KP_ENTER = 88,
                KP_1 = 89,
                KP_2 = 90,
                KP_3 = 91,
                KP_4 = 92,
                KP_5 = 93,
                KP_6 = 94,
                KP_7 = 95,
                KP_8 = 96,
                KP_9 = 97,
                KP_0 = 98,
                KP_PERIOD = 99,
                NONUSBACKSLASH = 100,
                APPLICATION = 101,
                POWER = 102,
                KP_EQUALS = 103,
                F13 = 104,
                F14 = 105,
                F15 = 106,
                F16 = 107,
                F17 = 108,
                F18 = 109,
                F19 = 110,
                F20 = 111,
                F21 = 112,
                F22 = 113,
                F23 = 114,
                F24 = 115,
                EXECUTE = 116,
                HELP = 117,
                MENU = 118,
                SELECT = 119,
                STOP = 120,
                AGAIN = 121,
                UNDO = 122,
                CUT = 123,
                COPY = 124,
                PASTE = 125,
                FIND = 126,
                MUTE = 127,
                VOLUMEUP = 128,
                VOLUMEDOWN = 129,
                KP_COMMA = 133,
                KP_EQUALSAS400 = 134,
                INTERNATIONAL1 = 135,
                INTERNATIONAL2 = 136,
                INTERNATIONAL3 = 137,
                INTERNATIONAL4 = 138,
                INTERNATIONAL5 = 139,
                INTERNATIONAL6 = 140,
                INTERNATIONAL7 = 141,
                INTERNATIONAL8 = 142,
                INTERNATIONAL9 = 143,
                LANG1 = 144,
                LANG2 = 145,
                LANG3 = 146,
                LANG4 = 147,
                LANG5 = 148,
                LANG6 = 149,
                LANG7 = 150,
                LANG8 = 151,
                LANG9 = 152,

                ALTERASE = 153,
                SYSREQ = 154,
                CANCEL = 155,
                CLEAR = 156,
                PRIOR = 157,
                RETURN2 = 158,
                SEPARATOR = 159,
                OUT = 160,
                OPER = 161,
                CLEARAGAIN = 162,
                CRSEL = 163,
                EXSEL = 164,
                KP_00 = 176,
                KP_000 = 177,
                THOUSANDSSEPARATOR = 178,
                DECIMALSEPARATOR = 179,
                CURRENCYUNIT = 180,
                CURRENCYSUBUNIT = 181,
                KP_LEFTPAREN = 182,
                KP_RIGHTPAREN = 183,
                KP_LEFTBRACE = 184,
                KP_RIGHTBRACE = 185,
                KP_TAB = 186,
                KP_BACKSPACE = 187,
                KP_A = 188,
                KP_B = 189,
                KP_C = 190,
                KP_D = 191,
                KP_E = 192,
                KP_F = 193,
                KP_XOR = 194,
                KP_POWER = 195,
                KP_PERCENT = 196,
                KP_LESS = 197,
                KP_GREATER = 198,
                KP_AMPERSAND = 199,
                KP_DBLAMPERSAND = 200,
                KP_VERTICALBAR = 201,
                KP_DBLVERTICALBAR = 202,
                KP_COLON = 203,
                KP_HASH = 204,
                KP_SPACE = 205,
                KP_AT = 206,
                KP_EXCLAM = 207,
                KP_MEMSTORE = 208,
                KP_MEMRECALL = 209,
                KP_MEMCLEAR = 210,
                KP_MEMADD = 211,
                KP_MEMSUBTRACT = 212,
                KP_MEMMULTIPLY = 213,
                KP_MEMDIVIDE = 214,
                KP_PLUSMINUS = 215,
                KP_CLEAR = 216,
                KP_CLEARENTRY = 217,
                KP_BINARY = 218,
                KP_OCTAL = 219,
                KP_DECIMAL = 220,
                KP_HEXADECIMAL = 221,
                LCTRL = 224,
                LSHIFT = 225,
                LALT = 226,
                LGUI = 227,
                RCTRL = 228,
                RSHIFT = 229,
                RALT = 230,
                RGUI = 231,
                MODE = 257,
                AUDIONEXT = 258,
                AUDIOPREV = 259,
                AUDIOSTOP = 260,
                AUDIOPLAY = 261,
                AUDIOMUTE = 262,
                MEDIASELECT = 263,
                WWW = 264,
                MAIL = 265,
                CALCULATOR = 266,
                COMPUTER = 267,
                AC_SEARCH = 268,
                AC_HOME = 269,
                AC_BACK = 270,
                AC_FORWARD = 271,
                AC_STOP = 272,
                AC_REFRESH = 273,
                AC_BOOKMARKS = 274,
                BRIGHTNESSDOWN = 275,
                BRIGHTNESSUP = 276,
                DISPLAYSWITCH = 277,
                KBDILLUMTOGGLE = 278,
                KBDILLUMDOWN = 279,
                KBDILLUMUP = 280,
                EJECT = 281,
                SLEEP = 282,
                APP1 = 283,
                APP2 = 284,
                AUDIOREWIND = 285,
                AUDIOFASTFORWARD = 286,
            } Key;

        };
    };

};
