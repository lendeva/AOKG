#pragma once

#include <windows.h>
#include "GL/freeglut.h"
#include<GL/gl.h>
#include<GL/GLU.h>
#include <stdio.h>

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА
class GraphicObject
{
private:
	// Позиция и угол поворота для объекта
	float position[3];
	float angle;
	// Матрица модели (расположение объекта) ‐ чтоб не вычислять каждый раз
	float modelMatrix[16];
	// Цвет модели
	float color[3];
public:
	// Конструктор
	GraphicObject(void);
	// Задать позицию объекта
	void setPosition(float x, float y, float z);
	// Задать угол поворота в градусах относительно оси OY
	void setAngle(float a);
	// Задать цвет модели
	void setСolor(float r, float g, float b);
	// Вывести объект
	void draw(void);
};

