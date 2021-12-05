#include <mold3D/3D.h>

using namespace mold::render::objects;

Cube::Cube(Point3D point, RGB color, Float3D Size, uint32_t TextureIndex) : GameObject({point.X, point.Y, point.Z}, color, Size, TextureIndex) {}

void Cube::Draw()
{
    BoilerPlate(
        {
            // FRONT
            glBegin(GL_POLYGON);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(0.5, 0, 0.5);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(0.5, 1, 0.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-0.5, 1, 0.5);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(-0.5, 0, 0.5);
            glEnd();

            // BACK
            glBegin(GL_POLYGON);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(0.5, 0, -0.5);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(0.5, 1, -0.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-0.5, 1, -0.5);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(-0.5, 0, -0.5);
            glEnd();

            // RIGHT
            glBegin(GL_POLYGON);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(0.5, 0, -0.5);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(0.5, 1, -0.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(0.5, 1, 0.5);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(0.5, 0, 0.5);
            glEnd();

            // LEFT
            glBegin(GL_POLYGON);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(-0.5, 0, 0.5);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(-0.5, 1, 0.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-0.5, 1, -0.5);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(-0.5, 0, -0.5);
            glEnd();

            // TOP
            glBegin(GL_POLYGON);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(0.5, 1, 0.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(0.5, 1, -0.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-0.5, 1, -0.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-0.5, 1, 0.5);
            glEnd();

            // BOTTOM
            glBegin(GL_POLYGON);
            glVertex3f(0.5, 0, -0.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(0.5, 0, 0.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-0.5, 0, 0.5);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-0.5, 0, -0.5);
            glTexCoord2f(0.0, 1.0);
            glEnd();
        })
}