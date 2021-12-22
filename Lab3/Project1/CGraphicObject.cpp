#include "CGraphicObject.h" 

// �����������
CGraphicObject::CGraphicObject(void) {
	Position[0] = 0; Position[1] = 0; Position[2] = 0;
	Angle = 0;

	memset(ModelMatrix, 0, sizeof(float) * 4 * 4);
	ModelMatrix[0] = ModelMatrix[5] = ModelMatrix[10] = ModelMatrix[15] = 1;

	Color[0] = 1; Color[1] = 0; Color[2] = 0;
}

// ������ ������� �������
void CGraphicObject::SetPosition(float x, float y, float z) {
	Position[0] = x; Position[1] = y; Position[2] = z;
	ModelMatrix[12] = x;
	ModelMatrix[13] = y;
	ModelMatrix[14] = z;
}

// ������ ���� �������� � �������� ������������ ��� OY
void CGraphicObject::SetAngle(float a) {
	Angle = a;
	ModelMatrix[0] = ModelMatrix[10] = cos(a);
	ModelMatrix[2] = -sin(a);
	ModelMatrix[8] = -ModelMatrix[2];
}

// ������ ���� ������
void CGraphicObject::Set�olor(float r, float g, float b) {
	Color[0] = r; Color[1] = g; Color[2] = b;
}

// ������� ������
void CGraphicObject::Draw(void) {

	glMatrixMode(GL_MODELVIEW);
	// �������� ������� ���������� � ����� b.
	glPushMatrix();
	//�������� ������� ���������� �� ������� ������ c.
	glColor3fv(Color);
	glMultMatrixf(ModelMatrix);
	//������� ������
	glutWireTeapot(1.0);
	//������������ ������� ���������� �� �����
	glPopMatrix();
}
