#pragma once 

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include "math.h" 

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОБЪЕКТА
class CGraphicObject {
private:  // Позиция и угол поворота для объекта  
	GLfloat Position[3];
	GLfloat Angle;  // Матрица модели (расположение объекта) - чтоб не вычислять каждый раз
	GLfloat ModelMatrix[16];  // Цвет модели
GLfloat Color[3]; public:  // Конструктор
	CGraphicObject(void);  // Задать позицию объекта
	void SetPosition(float x, float y, float z);  // Задать угол поворота в градусах относительно оси OY
	void SetAngle(float a);  // Задать цвет модели
	void SetСolor(float r, float g, float b);  // Вывести объект
	void Draw(void);
};