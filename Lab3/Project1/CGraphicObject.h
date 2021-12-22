#pragma once 

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include "math.h" 

// ����� ��� ������������� �������
class CGraphicObject {
private:  // ������� � ���� �������� ��� �������  
	GLfloat Position[3];
	GLfloat Angle;  // ������� ������ (������������ �������) - ���� �� ��������� ������ ���
	GLfloat ModelMatrix[16];  // ���� ������
GLfloat Color[3]; public:  // �����������
	CGraphicObject(void);  // ������ ������� �������
	void SetPosition(float x, float y, float z);  // ������ ���� �������� � �������� ������������ ��� OY
	void SetAngle(float a);  // ������ ���� ������
	void Set�olor(float r, float g, float b);  // ������� ������
	void Draw(void);
};