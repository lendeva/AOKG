#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include "math.h"
//	КЛАСС ДЛЯ РАБОТЫ С КАМЕРОЙ
class CCamera
{
private:
	//направления движения камеры
	bool	CameraLeft, CameraRight, CameraUp, CameraDown, CameraForward, CameraBackward;
	float	angle_horizon;//горизонтальный ox
	float	angle_vertical;//вертикальный oz
	float	radius;
	

	//	необходимые свойства
public:
	//матрица камеры
	GLdouble	CameraMatrix[9];

	//	конструкор и деструктор - загрузка начальных параметров камеры из файла и их сохранение
	CCamera();
	~CCamera();
	
	//	установка признаков нажатых клавиш
	void	SetKey(bool left, bool right, bool up, bool down, bool forward, bool backward);
	//	движение камеры в ранее выбранном направлении
	//	sec - количество секунд прошедших с момента последнего вызова
	void	Simulate(float sec);
	//	функция для установки матрицы камеры
	void	Apply();
	
};
