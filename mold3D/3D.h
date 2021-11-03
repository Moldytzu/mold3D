#pragma once
#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <math.h>

namespace mold
{
    #define DIRECTION_FORWARD 0
    #define DIRECTION_BACKWARD 1
    #define DIRECTION_LEFT 2
    #define DIRECTION_RIGHT 3

    typedef GLfloat Float3D;

    struct Point3D
    {
        Float3D X, Y, Z;
    };

    struct RGB
    {
        Float3D R, G, B;
    };

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

        class Camera : public GameObject
        {
        public:
            Camera();
            Camera(Point3D point);
            virtual void Draw();
            void Move(int direction, Float3D value);
            int lastOP = 0;
            Float3D AngleZ = -1.0f, AngleX = 0, Angle = 0;
        };
    };

    namespace core
    {
        namespace input {
            bool* GetKeyStates();
        };

        void Init(objects::Camera *camera, void (*draw)());
        void Init(objects::Camera *camera, void (*draw)(), int width, int height);
        void Run();
    };

};
