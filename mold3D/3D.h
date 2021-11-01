#pragma once
#include <GL/glut.h>
#include <math.h>

namespace mold {
    typedef GLfloat Float3D;
    
    namespace objects {
        class GameObject {
            public:
                GameObject();
                GameObject(Float3D X,Float3D Y,Float3D Z);
                void Draw();
                Float3D X,Y,Z;
        };

        class Pyramid : public GameObject {
            public:
                Pyramid();
                Pyramid(Float3D X,Float3D Y,Float3D Z,Float3D Size);
                virtual void Draw();
                Float3D Size;
        };

        class Cube : public GameObject {
            public:
                Cube();
                Cube(Float3D X,Float3D Y,Float3D Z,Float3D Size);
                virtual void Draw();
                Float3D Size;
        };

        class Camera : public GameObject {
            public:
                Camera();
                Camera(Float3D X,Float3D Y,Float3D Z);
                virtual void Draw();
                void Update(bool* keys);
            private:
                Float3D AngleZ=-1.0f,AngleX=0,Angle=0;
        };
    };

    namespace core {
        void Init(int argc, char **argv, objects::Camera* camera, void (*draw)());
        void Init(int argc, char **argv, objects::Camera* camera, void (*draw)(), int width, int height);
        void Run();
    };

};

