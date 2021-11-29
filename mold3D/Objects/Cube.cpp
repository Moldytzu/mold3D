#include <mold3D/3D.h>

using namespace mold::render::objects;

Cube::Cube() {}

Cube::Cube(Point3D point, RGB color, Float3D Size, uint32_t TextureIndex) : GameObject({point.X, point.Y, point.Z}, color, Size, TextureIndex) {}

void Cube::Draw()
{
    glPushMatrix();

    glColor3f(color.R, color.G, color.B); // set color

    if(TextureIndex > 0) {
        glBindTexture(GL_TEXTURE_2D, render::GlobalTextures[TextureIndex]);
        glEnable(GL_TEXTURE_2D);
    }

    //scale up
    glScalef(Size, Size, Size);

    //move in the world
    glTranslatef(coords.X, coords.Y, coords.Z);

    // BACK
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(0.5, 1, 0.5);
    glVertex3f(-0.5, 1, 0.5);
    glVertex3f(-0.5, 0, 0.5);
    glEnd();

    // Front
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0, 0);
    glVertex3f(0.5, 1, 0);
    glVertex3f(-0.5, 1, 0);
    glVertex3f(-0.5, 0, 0);
    glEnd();

    // RIGHT
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0, -0.5);
    glVertex3f(0.5, 1, -0.5);
    glVertex3f(0.5, 1, 0.5);
    glVertex3f(0.5, 0, 0.5);
    glEnd();

    // LEFT
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, 0, 0.5);
    glVertex3f(-0.5, 1, 0.5);
    glVertex3f(-0.5, 1, -0.5);
    glVertex3f(-0.5, 0, -0.5);
    glEnd();

    // TOP
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 1, 0.5);
    glVertex3f(0.5, 1, -0.5);
    glVertex3f(-0.5, 1, -0.5);
    glVertex3f(-0.5, 1, 0.5);
    glEnd();

    // BOTTOM
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0, -0.5);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(-0.5, 0, 0.5);
    glVertex3f(-0.5, 0, -0.5);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}