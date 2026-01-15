#define _CRT_SECURE_NO_WARNINGS

#include <gl/glut.h>
#include <cmath>
#include <cstdio>

// Глобальные переменные
float angle = 0;
int lightColorIndex = 0;  // Индекс текущего цвета освещения
int frameCount = 0;       // Счетчик кадров для смены цвета

// Параметры материалов для разных объектов
// Материал 1: для сплошной сферы
float mat1_dif[] = { 0.9f, 0.2f, 0.0f, 1.0f };   // Диффузный - оранжевый
float mat1_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };   // Фоновый - серый
float mat1_spec[] = { 0.6f, 0.6f, 0.6f, 1.0f };  // Зеркальный - серый
float mat1_shininess = 0.1f * 128;             // Блеск

// Материал 2: для проволочной сферы
float mat2_dif[] = { 0.0f, 0.5f, 1.0f, 1.0f };   // Диффузный - синий
float mat2_amb[] = { 0.1f, 0.1f, 0.1f, 1.0f };   // Фоновый - темно-серый
float mat2_spec[] = { 0.8f, 0.8f, 0.8f, 1.0f };  // Зеркальный - светлый
float mat2_shininess = 0.3f * 128;             // Блеск

// Материал 3: для куба
float mat3_dif[] = { 0.2f, 0.8f, 0.2f, 1.0f };   // Диффузный - зеленый
float mat3_amb[] = { 0.1f, 0.3f, 0.1f, 1.0f };   // Фоновый - темно-зеленый
float mat3_spec[] = { 0.5f, 1.0f, 0.5f, 1.0f };  // Зеркальный - светло-зеленый
float mat3_shininess = 0.5f * 128;             // Блеск

// Функции
void init(void);
void draw(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void idle(void);
void drawCoordinateAxes(void);
void changeLightColor(void);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    // GLUT_DOUBLE - двойная буферизация для плавной анимации
    // GLUT_RGB - цветовой режим RGB
    // GLUT_DEPTH - буфер глубины для 3D
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1280, 1024);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Программа анимации сферы с освещением и материалами");

    init();

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}

void init(void)
{
    // Установка цвета фона (фиолетовый с оттенком серого)
    glClearColor(0.7, 0.5, 0.7, 0.0);

    // Установка ортографической проекции
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // gluOrtho2D() заменяем на glOrtho для 3D
    glOrtho(-5, 5, -5, 5, -5, 5);

    // ============================================
    // НАСТРОЙКА ИСТОЧНИКА СВЕТА
    // ============================================

    // Начальные параметры источника света (белый свет)
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  // Диффузный свет
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };  // Фоновое освещение
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Зеркальный свет
    GLfloat light_position[] = { 1.5, 4.5, 1.5, 0.0 }; // Позиция источника света

    // Присвоение параметров источнику света GL_LIGHT0
    // glLightfv() - устанавливает параметры источника света
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // ============================================
    // ВКЛЮЧЕНИЕ ВОЗМОЖНОСТЕЙ OPENGL
    // ============================================

    // glEnable(GL_LIGHTING) - включает систему освещения
    glEnable(GL_LIGHTING);

    // glEnable(GL_LIGHT0) - включает конкретный источник света (номер 0)
    glEnable(GL_LIGHT0);

    // glEnable(GL_DEPTH_TEST) - включает буфер глубины (z-буфер)
    // Это необходимо для корректного отображения 3D объектов
    glEnable(GL_DEPTH_TEST);

    // Дополнительные настройки для лучшего отображения
    glShadeModel(GL_SMOOTH);          // Плавное затенение
    glEnable(GL_NORMALIZE);           // Автоматическая нормализация нормалей
    glEnable(GL_COLOR_MATERIAL);      // Позволяет использовать glColor с материалами
}

void reshape(int w, int h)
{
    // Установка области просмотра на все окно
    glViewport(0, 0, w, h);

    // Установка проекции
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Установка перспективной проекции
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);

    // Возврат к видовой матрице
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // ESC - выход
        exit(0);
        break;
    case 'c': // Смена цвета освещения
    case 'C':
        lightColorIndex = (lightColorIndex + 1) % 7;
        break;
    }
}

void idle(void)
{
    // Обновление угла для анимации
    angle += 0.5;
    if (angle > 360) angle = 0;

    // Увеличиваем счетчик кадров
    frameCount++;

    // Меняем цвет освещения каждые 300 кадров (примерно 5 секунд при 60 FPS)
    if (frameCount >= 300)
    {
        lightColorIndex = (lightColorIndex + 1) % 7;
        frameCount = 0;
    }

    // Запрос на перерисовку
    glutPostRedisplay();
}

void changeLightColor(void)
{
    // Массив цветов для источника света
    GLfloat lightColors[7][4] = {
        {1.0f, 1.0f, 1.0f, 1.0f},  // 0: Белый
        {0.0f, 1.0f, 0.0f, 1.0f},  // 1: Зеленый
        {1.0f, 0.0f, 0.0f, 1.0f},  // 2: Красный
        {0.0f, 0.0f, 1.0f, 1.0f},  // 3: Синий
        {1.0f, 1.0f, 0.0f, 1.0f},  // 4: Желтый
        {1.0f, 0.0f, 1.0f, 1.0f},  // 5: Фиолетовый
        {0.0f, 1.0f, 1.0f, 1.0f}   // 6: Голубой
    };

    // Меняем диффузную составляющую света
    GLfloat light_diffuse[] = {
        lightColors[lightColorIndex][0],
        lightColors[lightColorIndex][1],
        lightColors[lightColorIndex][2],
        1.0
    };

    // Применяем новый цвет к источнику света
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    // Отображаем текущий цвет в заголовке окна
    char colorNames[7][20] = {
        "Белый", "Зеленый", "Красный", "Синий",
        "Желтый", "Фиолетовый", "Голубой"
    };
    char title[100];
    sprintf(title, "Освещение: %s (C - сменить цвет)", colorNames[lightColorIndex]);
    glutSetWindowTitle(title);
}

void drawCoordinateAxes(void)
{
    // Отключаем освещение для осей координат
    glDisable(GL_LIGHTING);

    // Рисуем оси координат
    glLineWidth(2.0);

    // Ось X - красная
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    glEnd();

    // Ось Y - зеленая
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);
    glEnd();

    // Ось Z - синяя
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 2.0);
    glEnd();

    // Включаем освещение обратно
    glEnable(GL_LIGHTING);
}

void draw(void)
{
    // Очистка буфера цвета И буфера глубины
    // GL_COLOR_BUFFER_BIT - очистка цветового буфера
    // GL_DEPTH_BUFFER_BIT - очистка z-буфера (буфера глубины)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Установка видовой матрицы
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Установка камеры
    gluLookAt(0.0, 0.0, 8.0,   // Позиция камеры
        0.0, 0.0, 0.0,   // Точка, на которую смотрим
        0.0, 1.0, 0.0);  // Вектор "вверх"

    // Рисуем оси координат
    drawCoordinateAxes();

    // Меняем цвет освещения
    changeLightColor();

    // ============================================
    // ОБЪЕКТ 1: СПЛОШНАЯ СФЕРА (с материалом 1)
    // ============================================
    glPushMatrix(); // Сохраняем текущую матрицу преобразований

    // glMaterialfv() - устанавливает параметры материала для объектов
    // GL_FRONT - применяем материал к передним граням
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat1_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, mat1_shininess);

    // Сдвигаем сферу влево
    glTranslatef(-2.0, 1.5, 0.0);

    // glutSolidSphere() - рисует сплошную сферу
    // Параметры: радиус, количество сегментов по долготе, количество сегментов по широте
    glutSolidSphere(0.8, 30, 30);

    glPopMatrix(); // Восстанавливаем матрицу

    // ============================================
    // ОБЪЕКТ 2: ПРОВОЛОЧНАЯ СФЕРА (с материалом 2)
    // ============================================
    glPushMatrix();

    // Устанавливаем материал для проволочной сферы
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat2_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat2_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, mat2_shininess);

    // Сдвигаем и вращаем сферу
    glTranslatef(2.0, 1.5, 0.0);
    glRotatef(angle, 1.0, 0.0, 1.0);  // Вращение вокруг оси (1,0,1)

    // glutWireSphere() - рисует проволочную сферу
    glutWireSphere(0.8, 20, 20);

    glPopMatrix();

    // ============================================
    // ОБЪЕКТ 3: КУБ (с материалом 3)
    // ============================================
    glPushMatrix();

    // Устанавливаем материал для куба
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat3_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat3_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat3_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, mat3_shininess);

    // Сдвигаем куб вниз
    glTranslatef(0.0, -1.5, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);  // Вращение вокруг оси Y

    // glutSolidCube() - рисует сплошной куб
    glutSolidCube(1.5);

    glPopMatrix();

    // ============================================
    // ОБЪЕКТ 4: ПРОВОЛОЧНЫЙ ТОР
    // ============================================
    glPushMatrix();

    // Используем стандартный материал для тора
    GLfloat mat4_amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat mat4_dif[] = { 0.8f, 0.5f, 0.2f, 1.0f };  // Коричневый
    GLfloat mat4_spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float mat4_shininess = 0.7f * 128;

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat4_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat4_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat4_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, mat4_shininess);

    // Сдвигаем тор вниз и вправо
    glTranslatef(3.0, -1.5, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);  // Вращение вокруг оси Z

    // glutWireTorus() - рисует проволочный тор
    glutWireTorus(0.3, 0.8, 15, 30);

    glPopMatrix();

    // ============================================
    // ОБЪЕКТ 5: СПЛОШНОЙ ТОР
    // ============================================
    glPushMatrix();

    // Еще один материал
    GLfloat mat5_amb[] = { 0.2f, 0.2f, 0.4f, 1.0f };
    GLfloat mat5_dif[] = { 0.5f, 0.5f, 0.8f, 1.0f };  // Светло-синий
    GLfloat mat5_spec[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float mat5_shininess = 0.9f * 128;

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat5_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat5_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat5_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, mat5_shininess);

    // Сдвигаем тор вниз и влево
    glTranslatef(-3.0, -1.5, 0.0);
    glRotatef(angle, 1.0, 1.0, 0.0);  // Вращение

    // glutSolidTorus() - рисует сплошной тор
    glutSolidTorus(0.3, 0.8, 20, 40);

    glPopMatrix();

    // Обмен буферов (для двойной буферизации)
    glutSwapBuffers();
}