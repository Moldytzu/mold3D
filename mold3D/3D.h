#pragma once
#include <GL/glut.h>
#include <math.h>

namespace mold
{
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
            void Update(bool *keys);

        private:
            Float3D AngleZ = -1.0f, AngleX = 0, Angle = 0;
        };
    };

    namespace core
    {
        void Init(int argc, char **argv, objects::Camera *camera, void (*draw)());
        void Init(int argc, char **argv, objects::Camera *camera, void (*draw)(), int width, int height);
        void Run();
    };

};
