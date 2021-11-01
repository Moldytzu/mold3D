#include <mold3D/3D.h>

mold::objects::Camera *userCam; //user camera
void (*userDraw)();             //user redraw function
bool keys[256];                 //keys pressed

void keyboardUP(unsigned char key, int x, int y)
{
    keys[key] = false;
}

void keyboard(unsigned char key, int x, int y)
{
    keys[key] = true;
}

void changeSize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(75.0f, w * 1.0 / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void redraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //update camera
    userCam->Update(keys);
    userCam->Draw();

    //draw scene
    userDraw();

    glutSwapBuffers();
}

void mold::core::Init(int argc, char **argv, objects::Camera *camera, void (*draw)(), int width, int height)
{
    glutInit(&argc, argv); //init glut
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height); // window size
    glutCreateWindow("mold3D");        // window title
    glutIgnoreKeyRepeat(1);

    //callbacks
    glutDisplayFunc(redraw);
    glutIdleFunc(redraw);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUP);
    glutReshapeFunc(changeSize);

    //functions
    glEnable(GL_DEPTH_TEST);

    //user things
    userCam = camera;
    userDraw = draw;
}

void mold::core::Init(int argc, char **argv, objects::Camera *camera, void (*draw)())
{
    Init(argc, argv, camera, draw, 800, 600);
}

void mold::core::Run()
{
    glutMainLoop(); // do the main loop
}