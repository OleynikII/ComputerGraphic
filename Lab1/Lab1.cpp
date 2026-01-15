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
    glClearColor(1.0, 1.0, 0.8, 0.0); // Более светлый желтый фон
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(10, 10, 1900, 1000);

    // 1. Рисуем разноцветные точки разного размера
    glPointSize(8.0); // Точка размером 8 пикселей
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0); // Красная точка
    glVertex2f(-9.0, 9.0);

    glColor3f(0.0, 1.0, 0.0); // Зеленая точка
    glVertex2f(-8.5, 9.0);
    glEnd();

    glPointSize(12.0); // Точка размером 12 пикселей
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 1.0); // Синяя точка
    glVertex2f(-8.0, 9.0);

    glColor3f(1.0, 0.0, 1.0); // Фиолетовая точка
    glVertex2f(-7.5, 9.0);
    glEnd();

    glPointSize(16.0); // Точка размером 16 пикселей
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 0.0); // Желтая точка
    glVertex2f(-7.0, 9.0);

    glColor3f(0.0, 1.0, 1.0); // Голубая точка
    glVertex2f(-6.5, 9.0);
    glEnd();

    // 2. Горизонтальная линия, разделяющая экран пополам
    glLineWidth(3.0); // Толщина линии 3 пикселя
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0); // Черный цвет
    glVertex2f(-10.0, 0.0);   // Начало линии
    glVertex2f(10.0, 0.0);    // Конец линии
    glEnd();

    // 3. ЗАКРАШЕННЫЕ ПРИМИТИВЫ (выше линии y=0)

    // а) Закрашенный треугольник (GL_TRIANGLES)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // Красный
    glVertex2f(-9.0, 8.0);
    glVertex2f(-7.0, 8.0);
    glVertex2f(-8.0, 6.0);
    glEnd();

    // б) Закрашенный четырехугольник (GL_QUADS)
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0); // Зеленый
    glVertex2f(-6.0, 8.0);
    glVertex2f(-4.0, 8.0);
    glVertex2f(-4.0, 6.0);
    glVertex2f(-6.0, 6.0);
    glEnd();

    // в) Закрашенный многоугольник (GL_POLYGON) - пятиугольник
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0); // Синий
    glVertex2f(-3.0, 8.0);
    glVertex2f(-1.5, 8.0);
    glVertex2f(-1.0, 7.0);
    glVertex2f(-2.0, 6.0);
    glVertex2f(-3.5, 6.0);
    glEnd();

    // г) Закрашенные треугольники в виде полосы (GL_TRIANGLE_STRIP)
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0, 0.0, 1.0); // Фиолетовый
    glVertex2f(1.0, 8.0);
    glVertex2f(2.0, 8.0);
    glVertex2f(1.5, 7.0);
    glVertex2f(3.0, 7.0);
    glVertex2f(2.5, 6.0);
    glEnd();

    // 4. ПРОВОЛОЧНЫЕ ПРИМИТИВЫ (ниже линии y=0)

    glLineWidth(2.0); // Толщина линий 2 пикселя

    // а) Отдельные линии (GL_LINES)
    glBegin(GL_LINES);
    glColor3f(1.0, 0.5, 0.0); // Оранжевый
    glVertex2f(-9.0, -2.0);
    glVertex2f(-7.0, -2.0);
    glVertex2f(-8.0, -4.0);
    glVertex2f(-6.0, -4.0);
    glEnd();

    // б) Ломаная линия (GL_LINE_STRIP)
    glBegin(GL_LINE_STRIP);
    glColor3f(0.5, 0.0, 0.5); // Пурпурный
    glVertex2f(-5.0, -2.0);
    glVertex2f(-4.0, -4.0);
    glVertex2f(-3.0, -2.0);
    glVertex2f(-2.0, -4.0);
    glVertex2f(-1.0, -2.0);
    glEnd();

    // в) Замкнутая ломаная линия (GL_LINE_LOOP) - треугольник
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.5, 0.5); // Бирюзовый
    glVertex2f(1.0, -2.0);
    glVertex2f(3.0, -2.0);
    glVertex2f(2.0, -4.0);
    glEnd();

    // г) Прямоугольник из линий (используем GL_LINE_LOOP)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.5, 0.5, 0.0); // Оливковый
    glVertex2f(4.0, -2.0);
    glVertex2f(6.0, -2.0);
    glVertex2f(6.0, -4.0);
    glVertex2f(4.0, -4.0);
    glEnd();

    glFlush();
}