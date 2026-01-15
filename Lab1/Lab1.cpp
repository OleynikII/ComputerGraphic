#include <gl/glut.h>

void init(void);
void draw(void);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1980, 1024);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Программа создания 2D изображений");
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}

void init(void)
{
    glClearColor(1.0, 1.0, 0.8, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(10, 10, 1900, 1000);

    glPointSize(8.0);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-9.0, 9.0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-8.5, 9.0);
    glEnd();

    glPointSize(12.0);
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(-8.0, 9.0);

    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(-7.5, 9.0);
    glEnd();

    glPointSize(16.0);
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(-7.0, 9.0);

    glColor3f(0.0, 1.0, 1.0);
    glVertex2f(-6.5, 9.0);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-10.0, 0.0);
    glVertex2f(10.0, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);  
    glVertex2f(-9.0, 8.0);
    glColor3f(0.0, 1.0, 0.0);  
    glVertex2f(-7.0, 8.0);
    glColor3f(0.0, 0.0, 1.0); 
    glVertex2f(-8.0, 6.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-6.0, 8.0);
    glVertex2f(-4.0, 8.0);
    glVertex2f(-4.0, 6.0);
    glVertex2f(-6.0, 6.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(-3.0, 8.0);
    glVertex2f(-1.5, 8.0);
    glVertex2f(-1.0, 7.0);
    glVertex2f(-2.0, 6.0);
    glVertex2f(-3.5, 6.0);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(1.0, 8.0);
    glVertex2f(2.0, 8.0);
    glVertex2f(1.5, 7.0);
    glVertex2f(3.0, 7.0);
    glVertex2f(2.5, 6.0);
    glEnd();

    glLineWidth(2.0);

    glBegin(GL_LINES);
    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(-9.0, -2.0);
    glVertex2f(-7.0, -2.0);
    glVertex2f(-8.0, -4.0);
    glVertex2f(-6.0, -4.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.5, 0.0, 0.5);
    glVertex2f(-5.0, -2.0);
    glVertex2f(-4.0, -4.0);
    glVertex2f(-3.0, -2.0);
    glVertex2f(-2.0, -4.0);
    glVertex2f(-1.0, -2.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.5, 0.5);
    glVertex2f(1.0, -2.0);
    glVertex2f(3.0, -2.0);
    glVertex2f(2.0, -4.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.5, 0.5, 0.0);
    glVertex2f(4.0, -2.0);
    glVertex2f(6.0, -2.0);
    glVertex2f(6.0, -4.0);
    glVertex2f(4.0, -4.0);
    glEnd();

    glFlush();
}
