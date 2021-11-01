#include <mold3D/3D.h>

mold::objects::Camera *userCam; //user camera
void (*userDraw)(); //user redraw function
bool keys[256];

void keyboardUP(unsigned char key, int x, int y) {
    keys[key] = false;
}

void keyboard(unsigned char key, int x, int y) {
    keys[key] = true;
}

void changeSize(int w, int h)
{
    if (h == 0)
        h = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(75.0f, w * 1.0 / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void redraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    userCam->Update(keys);
    userCam->Draw();

    userDraw();

    glutSwapBuffers();
}

void mold::core::Init(int argc, char **argv, objects::Camera *camera, void (*draw)(), int width, int height)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutCreateWindow("mold3D");
    glutDisplayFunc(redraw);
    glutIdleFunc(redraw);
    glutIgnoreKeyRepeat(1);
    userCam = camera;
    userDraw = draw;

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUP);
    glutReshapeFunc(changeSize);
    glEnable(GL_DEPTH_TEST);
}

void mold::core::Init(int argc, char **argv, objects::Camera *camera, void (*draw)())
{
    Init(argc, argv, camera, draw, 800, 600);
}

void mold::core::Run()
{
    glutMainLoop();
}