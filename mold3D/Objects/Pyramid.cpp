#include <mold3D/3D.h>

using namespace mold::render::objects;

Pyramid::Pyramid() {}

Pyramid::Pyramid(Point3D point, RGB color, Float3D Size, uint32_t TextureIndex) : GameObject({point.X, point.Y + Size / 4, point.Z}, color, Size / 2, TextureIndex) {}

void Pyramid::Draw()
{
    glPushMatrix();

    glColor3f(color.R, color.G, color.B); // set color

    if (TextureIndex > 0)
    {
        glBindTexture(GL_TEXTURE_2D, render::GlobalTextures[TextureIndex]);
        glEnable(GL_TEXTURE_2D);
    }

    //move in the world
    glTranslatef(coords.X, coords.Y, coords.Z);

    //scale up
    glScalef(Size, Size, Size);

    glBegin(GL_TRIANGLES);

    // Front
    glTexCoord2f(0.5, 1.0); glVertex3f(0, 0 + 1.0f, 0); 
    glTexCoord2f(0.0, 0.0); glVertex3f(0 - 1.0f, 0 - 1.0f, 0 + 1.0f);
    glTexCoord2f(1.0, 0.0); glVertex3f(0 + 1.0f, 0 - 1.0f, 0 + 1.0f); 

    // Right
    glTexCoord2f(0.5, 1.0); glVertex3f(0, 0 + 1.0f, 0); 
    glTexCoord2f(0.0, 0.0); glVertex3f(0 + 1.0f, 0 - 1.0f, 0 + 1.0f); 
    glTexCoord2f(1.0, 0.0); glVertex3f(0 + 1.0f, 0 - 1.0f, 0 - 1.0f); 

    // Back
    glTexCoord2f(0.5, 1.0); glVertex3f(0, 0 + 1.0f, 0); 
    glTexCoord2f(0.0, 0.0); glVertex3f(0 + 1.0f, 0 - 1.0f, 0 - 1.0f); 
    glTexCoord2f(1.0, 0.0); glVertex3f(0 - 1.0f, 0 - 1.0f, 0 - 1.0f); 

    // Left
    glTexCoord2f(0.5, 1.0); glVertex3f(0, 0 + 1.0f, 0); 
    glTexCoord2f(0.0, 0.0); glVertex3f(0 - 1.0f, 0 - 1.0f, 0 - 1.0f); 
    glTexCoord2f(1.0, 0.0); glVertex3f(0 - 1.0f, 0 - 1.0f, 0 + 1.0f); 

    glEnd();

    glBegin(GL_QUADS);
    // Bottom
    glVertex3f(0 + 1.0f / 2, 0, 0 + 1.0f / 2);
    glVertex3f(0 - 1.0f / 2, 0, 0 + 1.0f / 2);
    glVertex3f(0 - 1.0f / 2, 0, 0 - 1.0f / 2);
    glVertex3f(0 + 1.0f / 2, 0, 0 - 1.0f / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}