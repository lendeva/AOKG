#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h> 
#include "GL/freeglut.h" 
#include <stdio.h>
#include "CGraphicObject.h"

// МАССИВ ОБЪЕКТОВ ДЛЯ ВЫВОДА
const int graphicObjectCount = 4;
GraphicObject graphicObjects[graphicObjectCount];


int ColorKey;
int CountTimer = 0;
int Count = 0;
float Color[3];
int NumColor = 4;
float Colors[4][3] = { {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 0.0} };

const int ENTER = 13;
// функция вызывается каждые 20 мс
void Simulation(int value)
{
	if (ColorKey == ENTER) {

		if (CountTimer == 50) {
			Color[0] = Colors[Count][0];
			Color[1] = Colors[Count][1];
			Color[2] = Colors[Count][2];
			++Count;
			CountTimer = 0;
		}
		CountTimer++;

		if (Count == NumColor) {
			Count = 0;
		}
	}
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, Simulation, 0);
};
// функция, вызываемая при изменении размеров окна
void Reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (float)w / h, 0.2, 70.0);
};
// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	// отчищаем буфер цвета
	glClearColor(0.22, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//	gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);
	gluLookAt(15, 15, 7.5, 0, 0, 0, 0, 1, 0);
	// выводим объект ‐ красный (1,0,0) чайник
//	glColor3f(Color[0], Color[1], Color[2]);
//	glutWireTeapot(1.0);
//	glColor3f(1.0, 1.0, 1.0);  //
//	glutWireTeacup(1.0);

	// выводим объекты
	for (int i = 0; i < graphicObjectCount; i++) {
		graphicObjects[i].draw();
	};

	// смена переднего и заднего буферов
	glutSwapBuffers();
};
// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
	ColorKey = key;
};

int main(int argc, char* argv[]) {
	int SIZE = 600;
	int POSITION = 200;
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	// создание окна:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(POSITION, POSITION);
	// 2. устанавливаем размер окна
	glutInitWindowSize(SIZE, SIZE);
	// 3. создаем окно
	glutCreateWindow("Lab2");
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// устанавливаем функцию которая будет вызвана через 20 мс
	glutTimerFunc(20, Simulation, 0);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);

	graphicObjects[0].setPosition(-4.0, 0.0, 0.0);
	graphicObjects[0].setAngle(0);
	graphicObjects[0].setСolor(0.0, 0.0, 1.0); //синий

	graphicObjects[1].setPosition(0.0, 0.0, -4.0);
	graphicObjects[1].setAngle(270);
	graphicObjects[1].setСolor(0.0, 0.0, 0.0);  //черный

	graphicObjects[2].setPosition(4.0, 0.0, 0.0);
	graphicObjects[2].setAngle(180);
	graphicObjects[2].setСolor(1.0, 0.0, 0.0);  //красный

	graphicObjects[3].setPosition(0.0, 0.0, 4.0);
	graphicObjects[3].setAngle(90);
	graphicObjects[3].setСolor(1.0, 1.0, 1.0);  //белый

	// основной цикл обработки сообщений ОС
	glutMainLoop();

}