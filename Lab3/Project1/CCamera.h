#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include "math.h"
//	����� ��� ������ � �������
class CCamera
{
private:
	//����������� �������� ������
	bool	CameraLeft, CameraRight, CameraUp, CameraDown, CameraForward, CameraBackward;
	float	angle_horizon;//�������������� ox
	float	angle_vertical;//������������ oz
	float	radius;
	

	//	����������� ��������
public:
	//������� ������
	GLdouble	CameraMatrix[9];

	//	���������� � ���������� - �������� ��������� ���������� ������ �� ����� � �� ����������
	CCamera();
	~CCamera();
	
	//	��������� ��������� ������� ������
	void	SetKey(bool left, bool right, bool up, bool down, bool forward, bool backward);
	//	�������� ������ � ����� ��������� �����������
	//	sec - ���������� ������ ��������� � ������� ���������� ������
	void	Simulate(float sec);
	//	������� ��� ��������� ������� ������
	void	Apply();
	
};
