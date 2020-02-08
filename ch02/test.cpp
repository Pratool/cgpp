#include <GL/freeglut.h>

void renderCallback()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    // CLI args pass-through.
    glutInit(&argc, argv);

    // Set up window frame.
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Test App");

    // Add callbacks.
    glutDisplayFunc(renderCallback);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutMainLoop();
    
    return 0;
}
