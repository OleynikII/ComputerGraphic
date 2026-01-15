#include <GL/glut.h>

float angle = 0;

void init(void);
void draw(void);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 1024);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D Объекты - Иванов-2");
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}

void init(void)
{
    glClearColor(0.7, 0.5, 0.7, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-6, 6, -6, 6, -6, 6);
    glEnable(GL_DEPTH_TEST); 
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1280, 1024);

    angle += 0.1;
    if (angle > 360) angle = 0;

    glPushMatrix(); 
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-3.0, 3.0, 0.0); 
    glRotatef(angle, 1.0, 1.0, 0.0); 
    glutSolidCube(1.5);
    glPopMatrix(); 

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0); 
    glTranslatef(3.0, 3.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 1.0);
    glutWireCube(1.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(-3.0, 0.0, 0.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glutSolidTorus(0.3, 1.0, 20, 20); 
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(3.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glutWireTorus(0.3, 1.0, 15, 15);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 1.0);
    glTranslatef(-3.0, -3.0, 0.0);
    glRotatef(angle, 1.0, 1.0, 1.0);
    glutSolidSphere(1.0, 30, 30); 
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 1.0, 1.0); 
    glTranslatef(3.0, -3.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glutWireSphere(1.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0.0, 0.0, 0.0);
    glutSolidCone(0.8, 1.5, 20, 20);
    glPopMatrix();

    glutPostRedisplay(); 
    glutSwapBuffers(); 
}