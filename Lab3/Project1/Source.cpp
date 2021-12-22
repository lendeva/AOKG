#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include "CGraphicObject.h"
#include "CCamera.h"
using namespace std;
//const int numberOfColors = 4; //количество цветов
//int currentColor = 0; //индекс текущего цвета

// МАССИВ ОБЪЕКТОВ ДЛЯ ВЫВОДА
const int  GraphicObjectCount = 4;
CGraphicObject GraphicObjects[GraphicObjectCount];
LARGE_INTEGER OldValue, NewValue, Time, frequency, n_v, o_v;;
float count_fps = 0.0;
CCamera Camera;
GLfloat angle = 0;

void initObjects()
{
	GraphicObjects[0].SetPosition(4, 0, 0);
	GraphicObjects[0].SetAngle(3.14f);       //Pi
	GraphicObjects[0].SetСolor(1, 0, 0);
	GraphicObjects[1].SetPosition(-4, 0, 0);  //0
	GraphicObjects[1].SetСolor(0, 1, 0);
	GraphicObjects[2].SetСolor(0, 0, 1);

	GraphicObjects[2].SetPosition(0, 0, 4);
	GraphicObjects[2].SetAngle(1.57f);       //Pi/2
	GraphicObjects[3].SetСolor(1, 1, 1);
	GraphicObjects[3].SetPosition(0, 0, -4);
	GraphicObjects[3].SetAngle(4.71f);	      //3*Pi/2

}
/*struct Color { //структура для представления цвета
	float Red, Green, Blue;
	Color(float R, float G, float B) : Red(R), Green(G), Blue(B) {}
};
Color colorArray[numberOfColors] = { // массив цветоа
	Color(0.0f, 0.0f, 0.0f), //black
	Color(1.0f, 1.0f, 1.0f), //white
	Color(0.0f, 0.0f, 1.0f), //blue
	Color(1.0f, 0.0f, 0.0f), //red
};
*/

void FPS() {
	QueryPerformanceCounter(&n_v);

	float delta = float(n_v.QuadPart - o_v.QuadPart) / frequency.QuadPart;
	string msg;

	if (delta >= 1.0) {
		msg += "FPS = ";
		msg += to_string((float)count_fps);
		char buf[255];
		strcpy(buf, msg.c_str());
		glutSetWindowTitle(buf);
		count_fps = 0;
		o_v = n_v;
	}

}
void Reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	// отчищаем буфер цвета
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	///glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(15, 10, 20, 0, 0, 0, 0, 1, 0); //5, 5, 7.5, 0, 0, 0, 0, 1, 0
		// устанавливаем камеру
	Camera.Apply();
	// выводим объект ‐ красный (1,0,0) чайник
	//glColor3f(colorArray[currentColor].Red, colorArray[currentColor].Green, colorArray[currentColor].Blue);
	//glutWireTeapot(1.0);

	for (int i = 0; i < GraphicObjectCount; i++)
	{
		GraphicObjects[i].Draw();
	};
	count_fps++;
	// смена переднего и заднего буферов
	glutSwapBuffers();
	FPS();
	count_fps++;
};
/*void nextColor() {
	currentColor++;
	if (currentColor == numberOfColors)
		currentColor = 0;
}*/
//int counter = 0;
//const int interval = 20;
// функция вызывается каждые 20 мс
void Simulation()
{
	/*if (counter == 1000) {
		nextColor();
		counter = 0;

	}
	counter += interval;
	*/
	// ОПРЕДЕЛЕНИЕ ВРЕМЕНИ ПРОШЕДШЕГО С МОМЕНТА ПОСЛЕДНЕЙ СИМУЛЯЦИИ В СЕКУНДАХ
	OldValue = NewValue;
	QueryPerformanceCounter(&NewValue);//возвращает текущее значение счетчика производительности реализуемого операционной системой	
	QueryPerformanceFrequency(&Time);//на сколько увеличивается внутренний счетчик производительности за одну секунду
	double SimulationTime = ((double)NewValue.QuadPart / Time.QuadPart) - ((double)OldValue.QuadPart / Time.QuadPart);//время между двумя моментами

	bool	CameraLeft = GetAsyncKeyState(VK_LEFT);//влево
	bool	CameraRight = GetAsyncKeyState(VK_RIGHT);//вправо
	bool	CameraUp = GetAsyncKeyState(VK_UP);//вверх
	bool	CameraDown = GetAsyncKeyState(VK_DOWN);//вниз
	bool	CameraForward = GetAsyncKeyState(VK_SPACE);//плюс
	bool	CameraBackward = GetAsyncKeyState(VK_TAB);//минус
	


	Camera.SetKey(CameraLeft, CameraRight, CameraUp, CameraDown, CameraForward, CameraBackward);
	//передвинуть камеру
	Camera.Simulate(SimulationTime);
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	//glutTimerFunc(20, Simulation, 0);


};
/*char spaceKey = 32;
// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
	if (key == spaceKey)
		nextColor();
};
*/
void main(int argc, char** argv)
{
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// создание окна:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(600, 600);
	// 3. создаем окно
	glutCreateWindow("Lab3");

	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);

	initObjects();
	// устанавливаем функцию которая вызывается всякий раз, когда процессор простаивает
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutIdleFunc(Simulation);
	QueryPerformanceCounter(&n_v);
	QueryPerformanceFrequency(&frequency);

	// устанавливаем функцию которая будет вызвана через 20 мс
	//glutTimerFunc(20, Simulation, 0);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	//glutKeyboardFunc(KeyboardFunc);

	// основной цикл обработки сообщений ОС
	glutMainLoop();
	return;
}
