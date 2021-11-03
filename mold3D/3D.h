#pragma once
#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <math.h>
#include <map>

namespace mold
{
    typedef GLfloat Float3D;

    enum Direction {
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
                int lastOP = 0;
                Float3D AngleZ = -1.0f, AngleX = 0, Angle = 0;
            };
        };
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

        enum EventType {
            Redraw = 1,
        };

        class EventSystem
        {
            public:
                void AttachCallback(EventType type, void* callback);
                void DetachCallback(EventType type);
                std::map<EventType, void*> GetMap();
            private:
                std::map<EventType, void*> events; //type, callback
        };

        void Init(mold::render::objects::Camera *camera, EventSystem* eventSystem);
        void Init(mold::render::objects::Camera *camera, EventSystem* eventSystem, int width, int height);
        void Run();
    };

};
