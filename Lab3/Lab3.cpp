#include <GL/glut.h>

float angle = 0;
float cubeX = 0.0f;
float cubeSpeed = 0.0005f;
int cubeDirection = 1; 

void init(void);
void draw(void);
void drawCube(float x, float y, float z, float size);
void drawSphere(float x, float y, float z, float radius);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 1024);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D Объекты");

    init();
    glutDisplayFunc(draw);
    glutIdleFunc(draw); 
    glutMainLoop();
    return 0;
}

void init(void)
{
    glClearColor(0.2, 0.2, 0.3, 0.0);
    glEnable(GL_DEPTH_TEST);

    // Включаем освещение
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Чтобы glColor3f влиял на материал
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Настройка проекции
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6.0, 6.0, -6.0, 6.0, -10.0, 10.0);

    // === КРИТИЧЕСКИ ВАЖНО: переключиться на модельно-видовую матрицу и сбросить её ===
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Теперь устанавливаем позицию света — она будет в мировых координатах!
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 2.0f, 2.0f, 3.0f, 1.0f }; // точечный источник

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void drawCube(float x, float y, float z, float size)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glRotatef(angle, 1.0, 1.0, 0.0);

    glutSolidCube(size);

    glPopMatrix();
}

void drawSphere(float x, float y, float z, float radius)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glRotatef(angle, 1.0, 1.0, 0.0);

    glutSolidSphere(radius, 50, 50);

    glPopMatrix();
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1280, 1024);

    angle += 0.1;
    if (angle > 360) angle = 0;

    cubeX += cubeSpeed * cubeDirection;

    if (cubeX > 2.0f) {
        cubeX = 2.0f;
        cubeDirection = -1; 
    }
    else if (cubeX < -2.0f) {
        cubeX = -2.0f;
        cubeDirection = 1;
    }

    GLfloat mat_shininess = 50.0;

    drawSphere(-2.5, 2.5, 0.0, 0.8);

    glPushMatrix();

    glTranslatef(2.5, 2.5, 0.0);
    glRotatef(angle, 0.0, 1.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    glPushMatrix();

    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    glTranslatef(-2.5, -2.5, 0.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glutSolidTorus(0.2, 0.8, 30, 30);
    glPopMatrix();

    glPushMatrix();

    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    glTranslatef(2.5, -2.5, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glutWireTorus(0.2, 0.8, 20, 20);
    glPopMatrix();

    drawCube(cubeX, 0.0, 0.0, 1.0);

    // Визуализация положения источников света (опционально)
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f); // Желтый для источников света
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    // Первый источник света
    glVertex3f(3.0f, 5.0f, 3.0f);
    glVertex3f(-3.0f, 5.0f, -3.0f);
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-3.8f, -3.8f);

    glEnable(GL_LIGHTING);
    glPopMatrix();

    glutSwapBuffers();
}